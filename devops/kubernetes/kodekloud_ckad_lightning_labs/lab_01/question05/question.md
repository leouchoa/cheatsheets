# Question

Create a `redis` deployment with the following parameters:

- Name of the deployment should be `redis` using the `redis:alpine` image.
It should have exactly 1 replica.

- The container should request for `0.2 CPU`. It should use the label `app=redis`.

- It should mount exactly 2 volumes.

a. An Empty directory volume called `data` at path `/redis-master-data`.

b. A `configMap` volume called `redis-config` at path `/redis-master`.

c. The container should expose the port 6379.

The `configMap` has already been created.
