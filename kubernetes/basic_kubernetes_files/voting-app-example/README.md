# Considerations

This [example](https://github.com/kodekloudhub/example-voting-app/tree/master/k8s-specifications) can be found [here](https://kodekloud.com/courses/kubernetes-for-the-absolute-beginners-hands-on/)
and is highly recommended to check it out anytime you want to get a good
example on how to deploy an app with kubernetes.

Here's the [original docker compose example](https://github.com/dockersamples/example-voting-app).

## Notes

1. First each pod yaml file was created
2. Then each service was created, with attention that:
    - the `redis` and `postgres` services are backend and
    then will be a serice of type `ClusterIP`. Remember that
    `ClusterIP` is default serice and does not need to be specified.
    Attention to link them to their pods!!!
    - the `voting-app` and `result-app` services are both frontend
    services, which means they will face external users and need to be
    of type `NodePort`. Attention to link them to their pods!!!
3. The worker does not need a service because it's not accessed through
any other services!

## Spinning Up

To spin up each pod/services/deployments:

```bash
kubectl create -f target_yaml_definition_file.yaml
```

To check them:

```bash
kubectl get pod,svc
```

By the way if you're using `minikube` you can get the url of the services with:

```bash
minikube service SERVICE_NAME_HERE --url
```

In this example we have just one replica for each pod. To scale them:

```bash
kubectl scale deployment NAME_OF_THE_DEPLOYMENT --replicas XYZ
```
