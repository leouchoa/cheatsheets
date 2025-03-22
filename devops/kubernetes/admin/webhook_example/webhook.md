# Create your own Custom Webhook

## First Things First

Create your certificates

## Deployment

First get your certificates. Then

```bash
k create ns webhook-demo
kubectl create secret tls \
  webhook-server-tls \
  --cert=/root/keys/webhook-server-tls.crt \
  --key=/root/keys/webhook-server-tls.key \
  -n webhook-demo
```

Now deploy the webhook and expose it as a service:

```bash
k apply -f ./webhook_deployment.yaml
k apply -f ./webhook_service.yaml
```

Now create an admission controler `MutatingWebhookConfiguration`:

```bash
k apply -f ./admission_controler.yaml
```
