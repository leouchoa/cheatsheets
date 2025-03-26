# ALB Ingress Examples

The pre-requisites are:

1. `EKS` cluster setup with private node groups. Example can be found [here](https://github.com/leouchoa/cheatsheets/blob/main/devops/kubernetes/eksctl_alb/eksctl.md).
2. An `ALB` configured. Example can be found [here](https://github.com/leouchoa/cheatsheets/blob/main/devops/kubernetes/eksctl_alb/deploy_alb.md).
3. An external-dns controller configured. Example can be found [here](https://github.com/leouchoa/cheatsheets/blob/main/devops/kubernetes/eksctl_alb/deploy_external_dns.yaml).
4. Also it's a good idea to deploy an `IngressClass`(link).

The examples covered were all taken from [this course](https://www.udemy.com/course/aws-eks-kubernetes-masterclass-devops-microservices/).
They are:

- Certificate Discovery

- Internal Load Balancer

The [base](add link) of the example is a simple `nginx` deployment, exposed
through a `nodePort` service. There are 3 of those to replicate a scenario
of different applications (e.g., homepage as default back-end, a cart
micro-service and a payments micro-service) to be gathered into a single app,
each for a path.
