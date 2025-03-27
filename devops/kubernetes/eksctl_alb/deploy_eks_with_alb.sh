#!/bin/sh

# Deploy for
# - Region: `us-east-1`
# - To run the alb with route53, you'll need a domain from route53.
#   - Don't forget the certificate (aws Cert. Manager) to enable tls encryption.

# Files needed:
# - An ssh-public-key key-pair for EC2 machines, named: `kube-demo`.
# - A file, named: `allow_external_dns_updates.json`.
# - A file named: `ingress_class.yaml` containing the ingress class specification.

# TODO: parse cli arguments:
# - ssh-public-key filepath
# - maybe accept aws region (attention to image.repository)

# -------------- Create cluster --------------
eksctl create cluster --name=eksdemo \
                      --region=us-east-1 \
                      --zones=us-east-1a,us-east-1b \
                      --without-nodegroup

eksctl utils associate-iam-oidc-provider \
    --region us-east-1 \
    --cluster eksdemo \
    --approve

eksctl create nodegroup --cluster=eksdemo \
                        --region=us-east-1 \
                        --name=eksdemo-ng-private1 \
                        --node-type=t3.medium \
                        --nodes-min=2 \
                        --nodes-max=4 \
                        --node-volume-size=20 \
                        --ssh-access \
                        --ssh-public-key=kube-demo \
                        --managed \
                        --asg-access \
                        --external-dns-access \
                        --full-ecr-access \
                        --appmesh-access \
                        --alb-ingress-access \
                        --node-private-networking

# -------------- Deploy ALB --------------

# TODO: check if `iam_policy_latest.json` exists. Otherwise create anew [ ]
curl -o iam_policy_latest.json https://raw.githubusercontent.com/kubernetes-sigs/aws-load-balancer-controller/main/docs/install/iam_policy.json
aws iam create-policy \
    --policy-name AWSLoadBalancerControllerIAMPolicy \
    --policy-document file://iam_policy_latest.json

# TODO: check if this `export` is really needed.
ALB_CONTROLER_POLICTY_ARN=$(
aws iam list-policies \
--query "Policies[?PolicyName=='AWSLoadBalancerControllerIAMPolicy'].Arn" \
--output text
)


eksctl create iamserviceaccount \
  --cluster=eksdemo \
  --namespace=kube-system \
  --name=aws-load-balancer-controller \
  --attach-policy-arn=$ALB_CONTROLER_POLICTY_ARN \
  --override-existing-serviceaccounts \
  --approve

helm repo add eks https://aws.github.io/eks-charts
helm repo update


VPC_ID=$(
  aws eks describe-cluster \
  --name eksdemo \
  --region us-east-1 \
  --query "cluster.resourcesVpcConfig.vpcId" \
  --output text
)


helm install aws-load-balancer-controller eks/aws-load-balancer-controller \
  -n kube-system \
  --set clusterName=eksdemo \
  --set serviceAccount.create=false \
  --set serviceAccount.name=aws-load-balancer-controller \
  --set region=us-east-1 \
  --set vpcId=$VPC_ID \
  --set image.repository=602401143452.dkr.ecr.us-east-1.amazonaws.com/amazon/aws-load-balancer-controller


kubectl apply -f ./ingress_class.yaml

# -------------- External DNS with Route53 --------------

aws iam create-policy \
  --policy-name "AllowExternalDNSUpdates" \
  --policy-document file://allow_external_dns_updates.json

EXTERNAL_DNS_POLICY_ARN=$(
aws iam list-policies \
  --query "Policies[?PolicyName=='AllowExternalDNSUpdates'].Arn"\
  --output text
)

eksctl create iamserviceaccount \
    --name external-dns \
    --namespace default \
    --cluster eksdemo \
    --attach-policy-arn $EXTERNAL_DNS_POLICY_ARN \
    --approve \
    --override-existing-serviceaccounts

EXTERNAL_DNS_SA_ARN=$(
kubectl describe sa external-dns | grep -o 'arn:aws:iam::[A-Za-z0-9:/-]\+'
)

sed "s|<your-arn-role>|$EXTERNAL_DNS_SA_ARN|g" deploy_external_dns.yaml > deploy_external_dns_populated.yaml

k apply -f ./deploy_external_dns_populated.yaml

# -------------- CLEANUP --------------
rm deploy_external_dns_populated.yaml
