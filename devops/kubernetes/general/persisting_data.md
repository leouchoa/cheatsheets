# Persisting Data

## Persistent Volumes (PV) and Persistent Volume Claims (PVC)

The idea behind this topic is that if your or pod node goes down, your
data still persists. For that the cluster admin creates a PV, which is a piece
of storage and **also** a resource - just like a pod or a node. The key here is
that it's lifecycle is independent of a pod.

Now to claim a share of that independent piece of storage, you need a PVC,
which is a request for a resource.

### Types of Provisioning

They can either be:

- static: classic PV + PVC combo.
- dynamic: here the PVC must request a `storageClass`.
  - admin creates the `storageClass` resource.
  - create the PVC request - don't need PV, it's auto-created.

### Common Scenarios

#### Have a pod with log data. Mount the logs on the host

Step 01: create a volume in the host:

```yaml
  volumes:
  - name: log-volume
    hostPath:
      type: Directory # opt
```

Step 02: mount the volume into the pod:

```yaml
    volumeMounts:
    - mountPath: /log
      name: log-volume
```

#### Create PV and PVC

Check out the files in `./basics/pv_pvc/`.

#### Need to Mount a PV to a Pod

First create the PV and PVC. Then update your with something like [this](https://kubernetes.io/docs/concepts/storage/persistent-volumes/#claims-as-volumes).

### Common Mistakes

- Identify which `storageClass` does not allow dynamic storage:
  - Check for the `kubernetes.io/no-provisioner` under `Provisioner` field

- Not binding appropriate access modes

- How to delay pvc creation up until a pod attach? Set `WaitForFirstConsumer`

- PV available but PVC Pending:
  - Usually access modes differ
