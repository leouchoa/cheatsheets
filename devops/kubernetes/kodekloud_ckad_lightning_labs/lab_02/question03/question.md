# Question

Create a pod called `my-busybox` in the `dev2406` namespace using the `busybox` image.
The container should be called secret and should sleep for 3600 seconds.

The container should mount a read-only secret volume called `secret-volume` at
the path `/etc/secret-volume`. The secret being mounted has already been
created for you and is called `dotfile-secret`.

Make sure that the pod is scheduled on `controlplane` and no other node in
the cluster.
