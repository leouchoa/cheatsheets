# Common Commands and Situations

- Run a basic nginx: `k run nginx --image=nginx`
- Find the image used by the pod: `k describe pod <pod-name> | grep "Image"`
- Get the pod definition file: `kubectl get pod <pod-name> -o yaml > pod-definition.yaml`
- To modify pod properties, use `k edit pod <pod-name>`
  - **NOTE**: running pods won't be updated! You have to delete them.
- Scaling `ReplicaSets`: `k scale replicaset <new-replica-set> --replicas 10000`

## Basics

### ReplicaSet

```yaml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: replicaset-1
spec:
  replicas: 2
  selector:
    matchLabels:
      tier: frontend
  template:
    metadata:
      labels:
        tier: frontend
    spec:
      containers:
      - name: nginx
        image: nginx
```

Common issues:

- Image does not exist.
- `apiVersion` is only `v1` and not `apps/v1`
- mismatch between `spec.selector.matchLabels` and `spec.template.metadata.labels`

### Deployment

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: replicaset-1
spec:
  replicas: 2
  selector:
    matchLabels:
      tier: frontend
  template:
    metadata:
      labels:
        tier: frontend
    spec:
      containers:
      - name: nginx
        image: nginx
```

### Namespace

```yaml
apiVersion: v1
kind: Namespace
metadata:
  name: dev
```

- Switch to a namespace permanently: `k config set-context $(k config current-context) --namespace=dev`
