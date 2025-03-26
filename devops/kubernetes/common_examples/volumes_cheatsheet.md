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

## Common Issues

1. Mismatched Access Modes
2. Incompatible Storage Class
3. Incorrect or Missing Resource Requests/Limits
4. Volume Provisioning Failures
5. Unbound PVCs
6. StorageClass Configuration Issues
7. Permissions or Quota Issues
8. Not Using Volume Expansion for Growing Volumes
9. Stale PV/PVC Configurations
10. Wrong Volume Mode
11. Volume Attachment Issues

### Mismatched Access Modes (Usually leads to Unbound PVCs) (*)

Common access modes are `ReadWriteOnce`, `ReadOnlyMany`, and `ReadWriteMany`.
If a PVC requests an access mode that the PV cannot provide, the PVC will fail
to bind to the PV.

Solution: Ensure that the PVC’s requested access modes are compatible with
those supported by the PV.

### Incompatible Storage Class (*)

Issue: PVs are often associated with a specific StorageClass, which defines the
underlying storage provider (like EBS, NFS, etc.). If the StorageClass is
mismatched between the PVC and the PV, binding fails.

Solution: Double-check that the StorageClass specified in the PVC matches the
StorageClass on the PV. If a StorageClass is specified in the PVC and not in the
PV, the PV must have storageClassName: <class_name> or be left empty if using
the default class.

3. Incorrect or Missing Resource Requests/Limits
Issue: The resource requests and limits for the PVC might not match the available size of the Persistent Volume, causing issues with provisioning or binding.

Solution: Make sure that the size requested by the PVC matches the size of the PV. If you’re dynamically provisioning PVs, ensure that the storage class’s provisioner is set up correctly.

4. Volume Provisioning Failures
Issue: If you are using dynamic provisioning (e.g., via a StorageClass), it’s possible for provisioning to fail due to misconfigurations in the provisioner or issues with the underlying infrastructure (e.g., no available resources, permissions issues).

Solution: Review the logs of the provisioner (like the external-provisioner controller) to diagnose the issue. Ensure that the infrastructure provider is properly configured and has sufficient resources to create new volumes.

5. Unbound PVCs
Issue: Sometimes, a PVC fails to bind to a PV even though one appears to match. This can happen if the PVC is incorrectly labeled or if it was incorrectly provisioned.

Solution: Review the status of the PVC (kubectl get pvc <name>) and PV (kubectl get pv <name>) to ensure they match in terms of labels, size, and storage class. You may also need to delete and recreate the PVC to force re-binding.

6. StorageClass Configuration Issues
Issue: If you use custom storage classes and the provisioner or other parameters are not configured correctly, the dynamic provisioning might fail.

Solution: Ensure the provisioner in the StorageClass is correct and that the necessary plugins or drivers are installed and configured in your Kubernetes environment. For example, in cloud environments, the correct cloud provider drivers need to be installed.

7. Permissions or Quota Issues
Issue: Permissions can cause PVCs to not bind properly if the user or service account does not have the appropriate access rights to create or attach PVs. Additionally, resource quotas might prevent provisioning of more volumes.

Solution: Verify that the service account used by Kubernetes has the necessary permissions to create and access volumes. Check the ResourceQuotas in your namespace to ensure you have enough resources to create the required PVs.

8. Not Using Volume Expansion for Growing Volumes
Issue: If you need to increase the size of a volume, but don’t set up volume expansion properly, Kubernetes won’t automatically expand the volume, even if the storage class supports it.

Solution: Ensure that the AllowVolumeExpansion field is set to true in the StorageClass, and that the underlying storage supports volume expansion. Don’t forget to update the PVC’s size when increasing the volume size.

9. Stale PV/PVC Configurations
Issue: PV and PVC objects might get out of sync, especially after scaling or manually modifying configurations.

Solution: Use the kubectl describe command to inspect and troubleshoot any issues, and verify that the configurations are current and consistent. Deleting and recreating PVCs or PVs might resolve stale issues.

10. Wrong Volume Mode
Issue: PVs can be in two modes: Filesystem and Block. If a PVC specifies a volumeMode that doesn’t match the mode of the PV, binding won’t succeed.

Solution: Ensure that the volumeMode specified in the PVC (if set) matches the PV's volumeMode. If you're using block storage, make sure both the PV and PVC are set to Block mode.

11. Volume Attachment Issues
Issue: After a PVC is bound to a PV, sometimes the volume cannot be correctly attached to the Pod due to issues with the cloud provider or infrastructure.

Solution: Check for attachment issues using kubectl describe and look for errors in the Kubernetes controller manager or cloud provider logs. For cloud-based volumes, verify the volume's attachment status directly in the cloud console.
