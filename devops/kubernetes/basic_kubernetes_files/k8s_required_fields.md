# Required Fields

[Source](https://kubernetes.io/docs/concepts/overview/working-with-objects/#required-fields)

In the manifest (YAML or JSON file) for the Kubernetes object you want to create,
you'll need to set values for the following fields:

- `apiVersion` - Which version of the Kubernetes API you're using to create this object.
- `kind` - What kind of object you want to create.
- `metadata` - Data that helps uniquely identify the object, including a name
string, UID, and optional namespace.
- `spec` - What state you desire for the object.
