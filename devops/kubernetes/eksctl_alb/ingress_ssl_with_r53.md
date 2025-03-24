# SSL Connections To ALB Using Route 53

## Configuring External DNS with Route53

Pre-requisites:

- Domain registered in route 53.
- Public certificate for every subdomain on your registered domain. So if your
domain is `mydomain.com`, issue a certificate for `*.mydomain.com`. Also
remember to create the CNAME DNS record on Route 53.

Now to use the domain to point to your ALB, there are mainly two options:

1. Manually setting the subdomain
2. Using external DNS provider

Usually the preferred approach is to go for the external DNS as it
frees us from having to manually update records in Route 53. For that we
have to configure:

- IAM policy for the service account

- Service account for the external DNS deployment.

- An external DNS deployment combo:
  - external DNS pod
  - external DNS deployment
  - external DNS cluster role
  - external DNS cluster role binding

Now create the [appropriate IAM policy](https://github.com/kubernetes-sigs/external-dns/blob/master/docs/tutorials/aws.md#iam-policy).

```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": [
        "route53:ChangeResourceRecordSets"
      ],
      "Resource": [
        "arn:aws:route53:::hostedzone/*"
      ]
    },
    {
      "Effect": "Allow",
      "Action": [
        "route53:ListHostedZones",
        "route53:ListResourceRecordSets"
      ],
      "Resource": [
        "*"
      ]
    }
  ]
}
```

You can do it by either going to aws website or by using the cli. If you want
the latter than save the policy into file and then run:

```bash
aws iam create-policy \
  --policy-name "AllowExternalDNSUpdates" \
  --policy-document file://allow_external_dns_updates.json

# NOTE: you check it with:
# aws iam list-policies | grep "AllowExternalDNSUpdates"
```

Then to create the external DNS service account with roles and associate
IAM policy:

```bash
eksctl create iamserviceaccount \
    --name external-dns \
    --namespace default \
    --cluster eksdemo \
    --attach-policy-arn arn:aws:iam::XXXXXXXXXXXX:policy/AllowExternalDNSUpdates \
    --approve \
    --override-existing-serviceaccounts
```

Finally save [this file](https://github.com/stacksimplify/aws-eks-kubernetes-masterclass/blob/master/08-NEW-ELB-Application-LoadBalancers/08-06-Deploy-ExternalDNS-on-EKS/kube-manifests/01-Deploy-ExternalDNS.yml)
and update the `role-arn` with "AllowExternalDNSUpdates" arn. Then external-dns
deployment with `kubectl apply -f <your-saved-file.yaml>`

Now the only thing that you need to do is to add the annotation in the alb:

```yaml
external-dns.alpha.kubernetes.io/hostname: yoursubdomain.samplemed-data-science.com
```

## Certificate Discovery
