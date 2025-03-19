# Volume Cheatsheet

When mounting a volume into a pod this
section is the same:

```yaml
      volumeMounts:
        - mountPath: /mnt/data
          name: data-volume
```

Now for `hostPath`:

```yaml
  volumes:
    - name: data-volume
      hostPath:
        path: /mnt/data
        type: Directory
```

while for PVCs:

```yaml
  volumes:
    - name: data-volume
      persistentVolumeClaim:
        claimName: pvc-example
```
