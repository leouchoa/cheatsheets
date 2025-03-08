# Imperative Commands

Stripped and formatted from [here](https://www.udemy.com/course/certified-kubernetes-application-developer/learn/lecture/14112621#overview). Credits are not mine.

To modify and create resources as required, instead of creating the files from
scratch:

```bash
kubectl run nginx --image=nginx --dry-run=client -o yaml > nginx-pod.yaml
```

## POD

Create an NGINX Pod

```bash
kubectl run nginx --image=nginx
```

Generate pod manifest file, but don't create the pod:

```bash
kubectl run nginx --image=nginx --dry-run=client -o yaml
```

## Deployment

Create a deployment

```bash
kubectl create deployment --image=nginx nginx
```

Generate deployment manifest file, but don't create the pod:

```bash
kubectl create deployment --image=nginx nginx --dry-run -o yaml
```

Generate deployment with 4 replicas:

```bash
kubectl create deployment nginx --image=nginx --replicas=4
```

You can also scale deployment using the `kubectl` scale command:

```bash
kubectl scale deployment nginx --replicas=4
```

Another way to do this is to save the YAML definition to a file and modify it:

```bash
kubectl create deployment nginx --image=nginx--dry-run=client -o yaml > nginx-deployment.yaml
```

You can then update the yaml with the replicas or any other field before
creating the deployment.

## Service

Create a service named `redis-service` of type `ClusterIP` to expose pod `redis`
on port 6379:

```bash
kubectl expose pod redis --port=6379 --name redis-service --dry-run=client -o yaml
```

> [!NOTE]
> This will automatically use the pod's labels as selectors

Or

```bash
# This will not use the pods' labels as selectors.
# Instead it will assume selectors as app=redis.
# You cannot pass in selectors as an option.
# So it does not work well if your pod has a different label set.
# So generate the file and modify the selectors before creating the service.
kubectl create service clusterip redis --tcp=6379:6379 --dry-run=client -o yaml 
```

Create a service named `nginx` of type `NodePort` to expose pod port 80 on
port 30080 on the nodes:

```bash
kubectl expose pod nginx --port=80 --name nginx-service --type=NodePort --dry-run=client -o yaml
```

This will automatically use the pod's labels as selectors, but you cannot
specify the node port. You have to generate a definition file and then add the
node port in manually before creating the service with the pod.

Or

```bash
kubectl create service nodeport nginx --tcp=80:80 --node-port=30080 --dry-run=client -o yaml
```

However this will not use the pods' labels as selectors.

Reference [here](https://kubernetes.io/docs/reference/kubectl/conventions/)
