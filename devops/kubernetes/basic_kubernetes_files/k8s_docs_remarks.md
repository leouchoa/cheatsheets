# Remarks

[Usually you don't need to create Pods directly, even singleton Pods.
Instead, create them using workload resources such as Deployment or Job](https://kubernetes.io/docs/concepts/workloads/pods/#workload-resources-for-managing-pods)
[This is because Pods are designed as relatively ephemeral, disposable entities.](https://kubernetes.io/docs/concepts/workloads/pods/#working-with-pods)
