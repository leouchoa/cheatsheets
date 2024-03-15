# How To Navigate the Files

- `pods.yaml`: the most basic one
- `replica_sets.yaml`: the second layer
- constructed from the `pods.yaml` by getting it's `metadata` and `spec`
 sections and adding them to `replica_sets.yaml`'s `template` section.
- `deployments.yaml`: the third layer
  - constructed from the `replica_sets.yaml` by adding `replicas`
  and `selector` sections
