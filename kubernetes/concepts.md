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

## Replication Controller and ReplicaSets

First things first: Replication Controller is the old technology, being replaced
by ReplicaSets. They're similar, but not the same, attention here!

Controllers are the processes that monitor Kubernetes objects to respond accordingly.
One special kind is the ReplicaSets controller, responsible for replicating the pods
to allow for high availability in case our app pod goes down.

Note: even if you have only one pod, the ReplicaSets controller will make sure that
if this pod goes down, another gets spinning up asap.

The ReplicaSets controller is also responsible for load balancing.
