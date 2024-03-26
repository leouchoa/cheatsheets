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

## Summary of Networking in kubernetes

Kubernetes solves the problem of networking inside one machine, where each pod
has it's own IP address, but communication between machines is left to the user,
so it has to manage cluster Networking by itself, where usually you'll have to
use a separate provider.

## Kubernetes Services

Types of services:

- NodePort: used the manage serving the pods by mapping ports
- ClusterIP: service that creates a single interface for us to connect to it
and let the LoadBalancer work, instead or worrying IPs and stuff.
- LoadBalancer: designed to mostly work with cloud providers, for easy
integration with their load balancer. If you try to use this on a VM, for
example, it would have the same effect of using a NodePort service.

They enable communication between various components within/outside of the app,
i.e, helps us connect apps together with other apps or users. For example, if you
group your apps in front/back/db, services is who stablish connectivity between them.
Their goal is to enable loose coupling between applications.

### Routing

Services are used to deal with communication between an external user and
your pod application. For example, if your machine has an IP of 162.197.0.1
and your 10.244.0.2 then you need to map them through the node and the
pod into the service for your user to see the app.
