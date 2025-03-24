# Ingress

```bash
aws elbv2 describe-load-balancers \
  --names <your-ingress-name> \
  --query "LoadBalancers[0].State.Code" \
  --output text

```
