# Kubernetes Cheatsheet

- list pods: `kubectl get pods`
- describe a pod: `kubectl describe pod pod-id-name`
- you can use a `dry-run` to create the manifest file:
`kubectl run redis --image=redis --dry-run=client -o yaml > redis-definition.yaml`
- suppose you want to change a config of a pod. Instead of deleting the pod, you
can edit the file and update the pod by running `kubectl apply -f your_k8s_def_file.yaml`

Remember that the bare minimum of a k8s yaml file is:

- apiVersion
- kind
- metadata
- spec

Example:

```yaml
apiVersion: v1
kind: Pod
metadata:
    name: nginx
    labels:
        app: nginx
        tier: frontend
spec:
    containers:
    - name: nginx
      image: nginx
```
