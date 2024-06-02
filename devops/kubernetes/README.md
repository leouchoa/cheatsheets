# Kubernetes Cheatsheet

- creating pods: `kubectl create -f definition_file.yaml`
  - take notice of the `--record` parameter, it's very important to
    catalog changes!
- list pods: `kubectl get pods`
- describe a pod: `kubectl describe pod pod-id-name`
- you can use a `dry-run` to create the manifest file:
`kubectl run redis --image=redis --dry-run=client -o yaml > redis-definition.yaml`
- suppose you want to change a config of a pod. Instead of deleting the pod, you
can edit the file and update the pod by running `kubectl apply -f your_k8s_def_file.yaml`
- the `kubectl edit ...` command will open the in-memory runtime spec file with vim.
That means: **take care when using the `kubectl edit`** command!

## Rollouts

- to check the status of the deployment rollout: `kubectl rollout status your_deployment_here`
- to check the history of the deployment rollout: `kubectl rollout history your_deployment_here`
- to undo a rollout: `kubectl undo rollout your_deployment_here`

## Replicasets

- scaling up/down the number of pods:
  - `kubectl edit -f yaml_file.yaml`, but this does
  not automatically update the replicaset
  - `kubectl scale --replicas=desired_number replicaset myapp-replicaset`
- creating Replicasets: `kubectl create -f yaml_file`
- deleting replicaset: `kubectl delete replicaset myapp-replicaset-f yaml_file.yaml`
- listing replicasets: `kubectl get replicaset`

- quick debug tip: if you manually try to add more pods than supported by the number
of replicasets, Kubernetes will automatically delete the pod.

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

## Troubleshooting

- Unmatched api version error:
  - error message: no matches for kind "Replicaset" in version "vXYZ"
  - Solution: run the command `kubectl explain replicaset`
    and check if the version output is the same of your k8s definition file

## DNS Subdomain

The name of a Pod must be a valid DNS subdomain value, but this can produce
unexpected results for the Pod hostname. For best compatibility, the name should
follow the more restrictive rules for a [DNS label](https://kubernetes.io/docs/concepts/overview/working-with-objects/names/#dns-label-names).
