# `externalName` Service

The following is a valid k8s manifest file:

```yaml
apiVersion: v1
kind: Service
metadata:
  name: mysql
spec:
  type: ExternalName
  externalName: mydatabase.xxxxxxxxxxxx.us-east-1.rds.amazonaws.com
```

The goal is to specify that we have a Service is of type `ExternalName`.
This type is used to map a service to an external resource, typically outside
the cluster. Instead of directing traffic to internal Pods, it points traffic
to an external DNS name. When a request is made to the service, Kubernetes will
resolve the `externalName` to an external DNS address.

In other words: Kubernetes will resolve the DNS name `mysql` to
`mydatabase.xxxxxxxxxxx.us-east-1.rds.amazonaws.com` using the `ExternalName`
service type. You can think of this like you're aliasing your db hostname
as `mysql`.

```asci
      +---------------------+
      |  Kubernetes Cluster |
      |        (Pods)        |
      +---------------------+
               |
               |  Service: mysql
               |
               v
       +----------------------------+
       |  Kubernetes DNS Resolver   |         Resolves to:
       |     (externalName:         |  mydatabase.xxxxxxxxxxx.us-east-1.rds.amazonaws.com
       |    mydatabase.xxxx...rds)  |
       +----------------------------+
               |
               v
       +-----------------------------+
       |  External Service:          |
       |  mydatabase.xxxxxxxxxxx...  |
       |  AWS RDS MySQL Database     |
       +-----------------------------+

```
