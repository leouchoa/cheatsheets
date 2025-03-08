# Configuration

## Config Maps

Used to inject general, non-sensitive environment variables into pods. Imperatively:

```bash
k create configmap <config-name> --from-literal=APP_COLOR=blue --from-literal=APP_MOD=dev
```

Or from a file `k create -f filename.yaml`, where `filename.yaml` is:

```yaml
apiVersion: apps/v1
kind: ConfigMap
metadata:
  name: webapp-config-map
data:
  APP_COLOR: blue
  APP_MOD: dev
```

And the pod is definition file is:

```yaml
---
apiVersion: v1
kind: Pod
metadata:
  labels:
    name: webapp-color
  name: webapp-color
  namespace: default
spec:
  containers:
  - env:
    - name: APP_COLOR
      valueFrom:
       configMapKeyRef:
         name: webapp-config-map
         key: APP_COLOR
    image: kodekloud/webapp-color
    name: webapp-color
```

## Secrets

Used to inject sensitive environment variables into pods. However:

- Secrets are not encrypted, only encoded.
- Secrets are not encrypted on `etcd`.
  - Also no data is encrypted on it by default.
  - Consider [encryption at rest](https://kubernetes.io/docs/tasks/administer-cluster/encrypt-data/).

Imperatively:

```bash
k create secret generic <secret-name> --from-literal=DB_USER=admin --from-literal=DB_PASS=admin
```

Or from a file `k create -f filename.yaml`, where `filename.yaml` is:

> [!WARNING]
> If you're storing base 64 through bash, remember to add an `=` sign!

```yaml
apiVersion: v1
kind: Secret
metadata:
  name: app-secret
type: Opaque
data:
  #NOTE: this is base64 encoded version of string admin
  # Not much secretive, but.....
  DB_USER: YWRtaW4=
  DB_PASS: YWRtaW4=
```

And the pod is definition file is:

```yaml
---
apiVersion: v1
kind: Pod
metadata:
  labels:
    name: webapp-color
  name: webapp-color
  namespace: default
spec:
  containers:
  - name: simple-webapp-color
    image: simple-webapp-color
    ports:
      - containerPort: 8080
    envFrom:
      - secretRef:
        name: app-secret
```

Note you can also mount the secret as a volume. In that case each attribute is
created as file. In our secret manifest file, it would be two files, named
`DB_PASS` and `DB_PASS`, both in `/opt/app-secret/`

## Security Context

This is mostly related to container sandboxing and isolation. Things to pay attention:

- User usually runs on root in containers: `kubectl exec ubuntu-sleeper -- whoami`

To change this:

```yaml
---
apiVersion: v1
kind: Pod
metadata:
  name: ubuntu-sleeper
  namespace: default
spec:
  securityContext:
    runAsUser: 1010
  containers:
  - command:
    - sleep
    - "4800"
    image: ubuntu
    name: ubuntu-sleeper
```

Or even:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: multi-pod
spec:
  securityContext:
    runAsUser: 1001
  containers:
  -  image: ubuntu
     name: web
     command: ["sleep", "5000"]
     securityContext:
      runAsUser: 1002

  -  image: ubuntu
     name: sidecar
     command: ["sleep", "5000"]
```

## Service Account

Q: At what location is the ServiceAccount credentials available within the pod?
A: Run `k describe pod` and look for `Mount`, because by defaul they're mounted there.

If you need to update the deployment to use a newly created ServiceAccount:

1. edit the deployment:

- option 01: `kubectl get deployment <deployment-name> -o yaml > deploy.yaml`
- option 02: `k edit deployment <deployment-name>`

2. add `serviceAccountName: dashboard-sa` in the pod spec field.

Or run `kubectl set serviceaccount deploy/<your-deployment> <your-svc-acc>`

## Tainting

Taint is for nodes and tolerance for pods.

```bash
kubectl taint nodes node01 spray=mortein:NoSchedule
```

For example:

```yaml
---
apiVersion: v1
kind: Pod
metadata:
  name: bee
spec:
  containers:
  - image: nginx
    name: bee
  tolerations:
  - key: spray
    value: mortein
    effect: NoSchedule
    operator: Equal
```

You can untaint nodes with:

```bash
kubectl taint nodes <node-name> node-role.kubernetes.io/control-plane:NoSchedule-
```
