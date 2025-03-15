# Common Commands and Situations

- Run a basic nginx: `k run nginx --image=nginx`

- Find the image used by the pod: `k describe pod <pod-name> | grep "Image"`

- Get the pod definition file: `kubectl get pod <pod-name> -o yaml > pod-definition.yaml`
  - Another example: `k run nginx --image=nginx --dry-run=client -o yaml > nginx-pod.yaml`

- To modify pod properties, use `k edit pod <pod-name>`
  - **NOTE**: running pods won't be updated! You have to delete them.
  - Remember the `--record` flag in case you need.

- Scaling `ReplicaSets`: `k scale replicaset <new-replica-set> --replicas 10000`

- Find a pod throughout all namespaces: `k get pods --all-namespaces | grep 'blue'`

- Replacing a pod instead of having to delete and then apply: `k replace --force -f <filename>`

- Apply label to node: `k label nodes node01 color=blue`

- Attach to a pod current shell: `k exec -it app -- /bin/sh`

- Create stuff from the web: `k apply -f https://github.com/kubernetes-sigs/metrics-server/releases/latest/download/components.yaml`

Quickly create stuff:

- `kubectl expose pod redis --port=6379 --name redis-service`
- `k create deployment --image kodekloud/webapp-color --replicas 3 webapp`
- `k create deployment redis-deploy --image redis -n dev-ns --replicas 2`
- `k run custom-nginx --image nginx --port 8080`
- `k create ns dev-ns`

Example: "Create a pod called httpd using the image httpd:alpine in the default
namespace. Next, create a service of type ClusterIP by the same name (httpd).
The target port for the service should be 80."

```bash
k run httpd --image httpd:alpine
k expose pod httpd --port 80 --name httpd
```

Quickly check your rollouts (try them after `kubectl create deployment nginx --image=nginx`):

- `k rollout status deployment/<deployment-name>`
- `k rollout history deployment/<deployment-name>`
- `k rollout undo deployment/<deployment-name>`
  - also remember you can use the `----to-revision=N` flag.

The `--record` flag is available in the commands:

- `create`
- `edit`
- `delete`
- `rollout`
- `set`

### Grepping Across containers

```bash
k describe pod blue-7bd99994c- | grep 'Node'
```

### Quickly Create Ingress

```bash
kubectl create ingress ingress-pay -n payments-space --rule="<ADD-THIS>"
# NOTE: more options at:
# k create ingress -h
```

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

### Overriding Commands

```bash
---
apiVersion: v1
kind: Pod
metadata:
  name: ubuntu-sleeper-2
spec:
  containers:
  - name: ubuntu
    image: ubuntu
    command:
      - "sleep"
      - "5000"
```
