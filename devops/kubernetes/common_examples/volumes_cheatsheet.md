# Volume Cheatsheet

When mounting a volume into a pod the `spec.containers.volumeMounts`
field is the same:

```yaml
spec:
  containers:
    - name: ____
      image: ____
      volumeMounts:
        - mountPath: /mnt/data
          name: data-volume
```

Now what changes is the `spec.volumes`, depending on the type. So for `hostPath`:

```yaml
spec:
  # containers field here
  volumes:
    - name: data-volume
      hostPath:
        path: /mnt/data
        type: Directory
```

And for `emptyDir: {}`

```yaml
spec:
  # containers field here
  volumes:
    - name: temp-storage
      emptyDir: {}
```

While for PVCs:

```yaml
spec:
  # containers field here
  volumes:
    - name: data-volume
      persistentVolumeClaim:
        claimName: pvc-example
```
