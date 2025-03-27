# Using `eksctl`

## Easier Setup

```bash
eksctl create cluster \
    --full-ecr-access \
    --alb-ingress-access \
    --region us-east-1
```

However then everything will be in a public subnet. If you want your worker
nodes in a private subnet then add the `--node-private-networking` flag.

## Fine-Grained Setup

### Foundations

First the control plane:

```bash
eksctl create cluster --name=eksdemo \
                      --region=us-east-1 \
                      --zones=us-east-1a,us-east-1b \
                      --without-nodegroup

```

Then associate an oidc provider for us to be able to use AWS IAM roles for
k8s service accounts in the cluster.

```bash
eksctl utils associate-iam-oidc-provider \
    --region us-east-1 \
    --cluster eksdemo \
    --approve
```

Now create an EC2 ssh key-pair to facilitate us getting into worker nodes.
If you want to create it using the `aws cli`:

```bash
aws ec2 create-key-pair \
    --key-name kube-demo \
    --query "KeyMaterial" \
    --output text > kube-demo.pem
```

Finally create the node-group with addons:

### Node Groups - Public and Self Managed

```bash
eksctl create nodegroup --cluster=eksdemo \
                        --region=us-east-1 \
                        --name=eksdemo-ng-public1 \
                        --node-type=t3.medium \
                        --nodes=2 \
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
                        --alb-ingress-access
```

Note that the last setup:

- Create the workers nodes in public subnets.
- The nodes are managed by ourselves (not Fargate Profiles)

In case you wanna get into a worker node:

```bash
ssh -i kube-demo.pem ec2-user@<Public-Worker-Node-IP>
```

> [!WARNING]
> If you want to access your applications, don't forget to allow traffic on the remote
> access security group!
> EC2 -> Security Group -> Search the one with "remoteAccess" -> Add Inbound Rule

### Node Groups - Private and Self Managed

However if you want your worker nodes in a private subnet (
mostly just adding `--node-private-networking`):

```bash
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
```

### Node Groups - Private and Serverless (Fargate Profiles)

Important points:

- Can only be deployed in private subnets.
- Each pod runs in an isolated environment:
  - The unit of work is the pod itself, not an EC2.
  - Each host can only comport one pod.
- Good for exposing billing to customers.
  - The unit of charge is the pod itself, not an EC2.
- Upon deletion of the Fargate nodegroup, your fargate resources
(pods, deploys, load balacers) will be automatically rescheduled into your
managed nodes. Also note that namespaced resources are preserved.

Also about ports:

- The pods will have random names and be private, which

```bash
eksctl create fargateprofile --cluster eksdemo \
                             --name fp-demo \
                             --namespace fp-dev
```

> [!IMPORTANT]
> This is a serverless service, set your resources well because things
> can go up very fast!

```yaml
          resources:
            requests:
              memory: "128Mi"
              cpu: "500m"
            limits:
              memory: "500Mi"
              cpu: "1000m"
```

## Credits

Those commands were all given in the following courses and I highly
suggest you take a look at them:

-
