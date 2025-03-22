# Ingress

## Deploy Basic Ingress

What will be created:

- A new namespace: `ingress-nginx`
- A new configMap for the controller: `ingress-nginx-controller`
- Two new service accounts for the controller:
  - First: `ingress-nginx`
  - First: `ingress-nginx-admission`

First create a new namespace `k create ns ingress-nginx`.

Then create a `configMap` for the `nginx` controller with
`k create configmap -n ingress-nginx ingress-nginx-controller`.

Now both service accounts:

```bash
k create serviceaccount -n ingress-nginx ingress-nginx
k create serviceaccount -n ingress-nginx ingress-nginx-admission
```
