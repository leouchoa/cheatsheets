# Deploy ALB Using Helm

For more details, please check out [this](https://www.udemy.com/course/aws-eks-kubernetes-masterclass-devops-microservices/)
course.

Pre-requisites:

1. eks cluster with working control place;
2. iam oidc provider configured;
3. private node groups configured.

The new parts will be:

- aws alb controller combo:
  - deployment: the controller
  - service: controller webhook clusterIP
  - secret: aws load balancer tls (not being deployed anymore!)
- IAM policy for the alb controller service account
- alb controller service account
- alb ingressclass

## Installing the ALB

### Setup Service Account and IAM Role

First create the appropriate IAM policy:

```bash
curl -o iam_policy_latest.json https://raw.githubusercontent.com/kubernetes-sigs/aws-load-balancer-controller/main/docs/install/iam_policy.json
aws iam create-policy \
    --policy-name AWSLoadBalancerControllerIAMPolicy \
    --policy-document file://iam_policy_latest.json
# Use the following command if you already have created the policy:
#
# aws iam list-policies --query "Policies[?PolicyName=='AWSLoadBalancerControllerIAMPolicy'].Arn" --output text
```

Using `eksctl` create a role for service account of the alb, but first
check if there's one available already:

```bash
#check
kubectl get sa -n kube-system aws-load-balancer-controller
```

```bash
# create if not yet available
eksctl create iamserviceaccount \
  --cluster=eksdemo \
  --namespace=kube-system \
  --name=aws-load-balancer-controller \
  --attach-policy-arn=arn:aws:iam::000000000000:policy/AWSLoadBalancerControllerIAMPolicy \
  --override-existing-serviceaccounts \
  --approve

# Use the following command if you forgot the policy arn:
#
# aws iam list-policies \
# --query "Policies[?PolicyName=='AWSLoadBalancerControllerIAMPolicy'].Arn" \
# --output text
```

To check if everything worked as expected you can run
`eksctl get iamserviceaccount --cluster=eksdemo` and also check it in
aws cloud formation stack. Note that this stack is simply an aws role.
Then once again:

```bash
# this time it should be there
kubectl get sa -n kube-system | grep 'aws-load-balancer-controller'
```

### Install the ALB

First add the repository and update:

```bash
helm repo add eks https://aws.github.io/eks-charts
helm repo update
```

If deploying to any region other than us-west-2, then add the
`--set image.repository=account.dkr.ecr.region-code.amazonaws.com/amazon/aws-load-balancer-controller`
flag to the install command, replacing account and region-code with the values
for [your region listed](https://docs.aws.amazon.com/eks/latest/userguide/add-ons-images.html)
in Amazon EKS add-on container image addresses.

```bash
helm install aws-load-balancer-controller eks/aws-load-balancer-controller \
  -n kube-system \
  --set clusterName=eksdemo \
  --set serviceAccount.create=false \
  --set serviceAccount.name=aws-load-balancer-controller \
  --set region=us-east-1 \
  --set vpcId=vpc-XXXXXXXXXXXXXXXXX \
  --set image.repository=602401143452.dkr.ecr.us-east-1.amazonaws.com/amazon/aws-load-balancer-controller

# NOTE: here's shortcut to find the VPC of your cluster:
# aws eks describe-cluster \
# --name eksdemo \
# --region us-east-1 \
# --query "cluster.resourcesVpcConfig.vpcId" \
# --output text

# NOTE: also in case you accidentally stopped the install, run:
# helm uninstall aws-load-balancer-controller -n kube-system
# then rerun the install command.
```

Finally deploy the default `IngressClass` so we don't have to annotate our
ingress definitions every time.

```yaml
apiVersion: networking.k8s.io/v1
kind: IngressClass
metadata:
  name: my-aws-ingress-class
  annotations:
    ingressclass.kubernetes.io/is-default-class: "true"
spec:
  controller: ingress.k8s.aws/alb
```

Done.

> [!NOTE]
> If you check the `aws-load-balancer-controller,` it has no token or secret
> in it and the secret is not even created. However this seems not to
> interfere with the alb.

#### Meaning Behind `IngressClass` Deployment

When using an alb, the `IngressClass` can be used to tell k8s which ingress
controller should handle specific ingress resources, as it helps avoiding
ambiguity with other controllers (imagine you have an additional `nginx`
as a controller).

So by deploying the `IngressClass`, we're essentially setting a routing rule
for the traffic, that helps the ALB Ingress Controller manage HTTP/S requests
for services more efficiently.
