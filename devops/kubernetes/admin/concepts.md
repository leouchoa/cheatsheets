# Administering Kubernetes Basics

## Quick Commands

- Quickly check your os: `cat /etc/*release*
`
- Config files are available at: `/etc/kubernetes/manifests`

- Quickly get available resources: `k api-resources`

- Get api-server config: `k describe pod kube-apiserver-controlplane -n kube-system`

- Current context: `kubectl config --kubeconfig=/root/my-kube-config current-context`

- Set context: `k config --kubeconfig ./my-kube-config use-context research`

- Get the api group paths quickly you can curl the root of the api-server:
  - `curl http://localhost:6443 -k --key admin.key --cert admin.cert --cacert --ca.crt`
  - Alternatively start a kubectl client: `kubectl proxy`. It will forward your
  requests with credentials set in.

- Get auth modes configured in the cluster:
  `k describe pod kube-apiserver-controlplane -n kube-system | grep 'auth'`

- Check your rbac permissions in the cluster with:
  - `k auth can-i create deployments`
  - `k auth can-i create deployments --as dev-user` (impersonated)
  - `k auth can-i delete nodes`
  - `k auth can-i delete nodes --as dev-user` (impersonated)
  - `k auth can-i delete nodes --as dev-user --namespace prod` (impersonated)

In case you have your own `kubeconfig` file, like `my-kube-config.yaml` you
can simply export it to `KUBECONFIG` to your shell profile and k8s will load
it automatically.

## Types

- File-based: either static password-based or static token-based.
  - Drawbacks: files can get big and servers can go down, so not good.

- ABAC:

- RBAC:

## KubeConfig File

Exists at `$HOME/.kube/config`

## QA

- Q: Which account is the kube-proxy role assigned to?
  - A: `k describe rolebinding kube-proxy -n kube-system`

- Q: Add a new rule in the existing role developer to grant the dev-user
permissions to create deployments in the blue namespace.
  - A: edit role `kubectl edit role developer -n blue` and then append:

  ```yaml
  - apiGroups:
    - apps
      resources:
      - deployments
      verbs:
      - create
  ```

## Roles

## Cluster Roles

### Case

A new user named `leo` comes in: plug here the ckad course exercise!

### Roles Vs Cluster Roles

Roles are usually namespaced, while Cluster Roles are cluster-wide roles.

## Admission Controllers

They're used to implement enhanced security measures (like validate/reject requests)
and/or provide extra actions (auto provision `namespaces`, rate limit, etc.)
before pods are created.

- Get enabled admission controllers:
  1. Go to `/etc/kubernetes/manifests/kube-apiserver.yaml`
  2. Check the field: `- --enable-admission-plugins`

- To disable an admission controller:
  1. Go to `/etc/kubernetes/manifests/kube-apiserver.yaml`
  2. Add the field: `- --disable-admission-plugins=<you-controller-here>`
  3. Example:`- --disable-admission-plugins=DefaultStorageClass`

- Since the kube-apiserver is running as pod you can run
  `ps -ef | grep kube-apiserver | grep admission-plugins`
  check the process to see enabled and disabled plugins.

- Get admission controller is enabled, but is normally disabled:
  - `grep enable-admission-plugins /etc/kubernetes/manifests/kube-apiserver.yaml`

- Why can't you automatically create pods in a new namespace?
  - Because kubernetes have `NamespaceExists` admission controller enabled
  which rejects requests to namespaces that do not exist.
  - How to enable: edit the api-server config file `/etc/kubernetes/manifests/kube-apiserver.yaml`
    - Append the `NamespaceAutoProvision` plugin: `--enable-admission-plugins=NodeRestriction,NamespaceAutoProvision`
  - **However**: Note that the `NamespaceExists` and `NamespaceAutoProvision` admission
  controllers are deprecated and now replaced by `NamespaceLifecycle` admission controller.
    - The NamespaceLifecycle admission controller will make sure that requests
      to a non-existent namespace is rejected and that the default namespaces
      such as default, kube-system and kube-public cannot be deleted.

### Two Types of Admission Controllers: Mutating and Validating

The mutating admission controller can modify your request. For example, the
`DefaultStorageClass` controller can add the `storageClassName` field in your PVCs
requests. As for a validating controller, the `NamespaceExists` is a typical
example.

It's usually the case that mutating controllers are called before validating
controlers.

- reference [here](https://kubernetes.io/docs/reference/access-authn-authz/admission-controllers/)

### Custom Admission Controllers

To create your custom admission controller there are:

- [MutatingAdmissionWebhook](https://kubernetes.io/docs/reference/access-authn-authz/admission-controllers/#mutatingadmissionwebhook)
- [ValidatingAdmissionWebhook](https://kubernetes.io/docs/reference/access-authn-authz/admission-controllers/#validatingadmissionwebhook)
- [ValidatingAdmissionPolicy](https://kubernetes.io/docs/reference/access-authn-authz/admission-controllers/#validatingadmissionpolicy)

They are webhooks and have to point to a webserver (the Admission Webhook server)
that can be either within or outside our cluster.

This is how it happens: our request goes through the usual path
(kubectl -> authentication -> authorization -> admission controller)
up until the last built-in admission
controller. Then it hits the webhook that's configured, which in turn makes a call
to the admission webhook server by the post-processed request as a json.

How to employ this:

1. Make a web server to serve as your webhook server (simple api server)
2. Deploy that server, it can be either in your cluster as a deployment with a
service to expose it, or elsewhere on the internet.
3. Configure our cluster to reach out this webserver by making a request and
getting a response. The response is expected to be json with some specific fields.
Here's an [example](https://kubernetes.io/docs/reference/access-authn-authz/extensible-admission-controllers/#configure-admission-webhooks-on-the-fly).

## API Version

The key takeway here is that you're querying a webserver and it has paths.
Those paths are grouped. For example you can request for a `deployment`
at versions `apps/v1alpha1`, `apps/v1beta1` and `apps/v1` to see their
effects.

Also noteworthy is the `Storage Version`, which relates to what is the
preferred version to be used (default) for a resource/object and that
preference is saved/stored in the `etcd` database and hence the `Storage`.
For more info, check [this out](https://stackoverflow.com/a/69560484).
But also have in mind that it [may not always be the case](https://kubernetes.io/docs/reference/using-api/deprecation-policy/).

- `v1` means ga-stable version: generally available stable version
  - could also be `/v1alpha1` or `/v1beta1`

Quick tips:

- If you have a yaml file in an old version there's a [plugin](https://kubernetes.io/docs/tasks/tools/install-kubectl-linux/#install-kubectl-convert-plugin)
to quickly migrate to the newer version with `k convert`.

- To find the preferred version: `k api-versions`
- To find list of resources: `k api-resources`

### Example: Changing API Version

To enable the `v1alpha1` version for `rbac.authorization.k8s.io` API
group on the controlplane node, add `--runtime-config=rbac.authorization.k8s.io/v1alpha1`
to the `/etc/kubernetes/manifests/kube-apiserver.yaml` file.
After that `kubelet` will detect the changes and will recreate the `apiserver` pod,
lut it may take some time.

Example:

```yaml
 - command:
    - kube-apiserver
    - --advertise-address=10.18.17.8
    - --allow-privileged=true
    - --authorization-mode=Node,RBAC
    - --client-ca-file=/etc/kubernetes/pki/ca.crt
    - --enable-admission-plugins=NodeRestriction
    - --enable-bootstrap-token-auth=true
    - --runtime-config=rbac.authorization.k8s.io/v1alpha1 --> This one
    - --etcd-cafile=/etc/kubernetes/pki/etcd/ca.crt
```

> [!WARNING]
> If you make a mistake in the config file, it could result in the API
> server being unavailable and that can break the cluster. So before you proceed
> have a copy of your current working config:
> `cp -v /etc/kubernetes/manifests/kube-apiserver.yaml /root/kube-apiserver.yaml.backup`

### API Deprecation Policy

They're described [here](https://kubernetes.io/docs/reference/using-api/deprecation-policy/).

Example:

```ascii
API Group Version

    ┌───────────────┐
    │               │
    │  Preferred /  │
    │  Storage Ver. │
    │               │
    └───────────────┘
           │
           ▼
    +-----------------+     +-----------------+     O X + 9
    |  /v2alpha1      | --> |  /v1            |
    +-----------------+     +-----------------+     O X + 8
    |  /v1beta2       | --> |  /v1            |
    |  (Deprecated)   |     +-----------------+     O X + 7
    +-----------------+     |  /v1            |
    |  /v1beta2       | --> +-----------------+     O X + 6
    |  (Deprecated)   |     |  /v1beta2       |
    +-----------------+     |  (Deprecated)   |     O X + 5
    |  /v1beta1       | --> +-----------------+
    |  (Deprecated)   |                             O X + 4
    +-----------------+                              
    |  /v1beta1       | 
    |  (Deprecated)   |
    +-----------------+
    |  /v1           |
    +-----------------+

```

## Custom Resource Definition (CRD)

A [CRD](https://kubernetes.io/docs/tasks/extend-kubernetes/custom-resources/custom-resource-definitions/)
is the specification file that k8s looks when creating a custom
resource. So if you want to create your own resource kind:

1. Create a CRD file and then `k create -f <your-crd-file>`.
2. Create your custom resource manifest file `<my-custom-resource-file>`
3. Deploy your custom resource: `k apply -f <my-custom-resource-file>`

There's an example in the `./crd_example/` dir. So you can:

1. `k create -f ./crd_example/crd.yaml`
2. `k apply -f ./crd_example/custom_resource.yaml`

Then check it's properties with `k describe crd`.

## Controllers and the Operator Framework

What's a controller:

In case you wanna build your own: [sample](https://github.com/kubernetes/sample-controller)

Now you can package and deploy a crd and a custom resource as a single
entity with the Operator Framework. It will internally:

1. Create de crd,
2. Create the resources
3. Deploy the custom controller as a deployment.

> [!NOTE]
> Check out the [operator hub registry](https://operatorhub.io/) for many examples!
