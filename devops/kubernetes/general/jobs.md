# Jobs

The following pod is meant to carry a computation:

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: simple-calc
spec:
  containers:
  - name: math-add
    image: ubuntu
    command: ['expr','1','+','1']
  # NOTE: the default `restartPolicy` is Always and your pod
  # will be recreated every time.
  restartPolicy: Never
```

## Jobs Definition File

To convert the last pod into a batch service:

```yaml
apiVersion: batch/v1
kind: Job
metadata:
  name: simple-calc-job
spec:
  completions: 3 # recreates pods until desired number of completions
  parallelism: 3 # pods created in parallel.
  template:
    spec:
      containers:
      - name: math-add
        image: ubuntu
        command: ['expr','1','+','1']
      # NOTE: the default `restartPolicy` is Always and your pod
      # will be recreated every time.
      restartPolicy: Never
```

- The `completions`field: is useful in case your task can fail. Then k8s will
redeploy the jobs until the desired number of completions.

## CronJobs

```yaml
apiVersion: batch/v1beta1
kind: CronJob
metadata:
  name: recurrent-task
spec:
  schedule: "*/1 * * * *"
  jobTemplate:
    spec:
    completions: 3 # recreates pods until desired number of completions
    parallelism: 3 # pods created in parallel.
    template:
      spec:
        containers:
        - name: math-add
          image: ubuntu
          command: ['expr','1','+','1']
        # NOTE: the default `restartPolicy` is Always and your pod
        # will be recreated every time.
        restartPolicy: Never

```
