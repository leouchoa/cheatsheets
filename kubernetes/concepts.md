# Concepts

## Pods

Kubernetes does deploy containers directly on worker nodes.
The containers are encapsulated on pods.

A pod a single instance of a an application, the smallest object that
you can create in kubernetes.

Pods usually have a one-to-one relationship with the containers, which means
that usually you deploy a pod per container. So to scale up/down,
you add/delete a pod. But of course you can work with multi-containers in
a pod, though you still gotta have in mind that a pod is the smallest app
object.

Attention: As of version 1.18, kubectl run
(without any arguments such as --generator ) will create a pod instead of a deployment.
