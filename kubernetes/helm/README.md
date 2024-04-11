# Helm

Can be thought of as a package manager for kubernetes, helping us deal with the
immense amount of yaml configs files for k8s setups. The many helm charts can be
found at [artifacthub.io](https://artifacthub.io).

By the way: you can install more then one chart per cluster.

## Quick Commands

- find charts: `helm search hub CHART_HERE`
- add a specific repo to `kubectl` node: `helm repo add NAME_HERE URL_HERE`. Example:
  - add the wordpress repo with `helm repo add bitnami https://charts.bitnami.com/bitnami`
  - search the wordpress chart inside this new remote repo: `helm search repo wordpress`
- list helm chart repositories: `helm repo list`
- uninstall a release: `helm uninstall release name`
- remove a repo: `helm repo remove REPO_NAME`
- upgrade a release: `helm upgrade RELEASE_NAME REPO/IMAGE --version NUMBER`. Example:
  - `helm upgrade dazzling-web bitnami/nginx --version 13`
- rollback a release: `helm rollback RELEASE_NAME REVISION_NUMBER`
- create a chart template in the current dir: `heml create your-chart-name`

## Quick Examples

### Deploy Apache

Deploy the `Apache` application on the cluster using the `apache` from the `bitnami`
repository and set the release `Name` to `amaze-surf`:

```bash
helm install amaze-surf bitname/apache
```

### Upgrading a Release

```bash
helm repo add bitnami https://charts.bitnami.com/bitnami
helm install amaze-surf bitname/nginx
helm upgrade dazzling-web bitnami/nginx --version 13
```

## Notable Differences Between Helm 2 and Helm 3

- RBAC added, meaning no more `Tiller` in between Helm and the cluster in v3
- 3-way strategic merge path

## About `apiVersion` in Chart File

For working with helm v3 you gotta add `apiVersion: v2`. If you're creating
charts for helm v2, then ignore it because it can lead to unexpected results/bugs.
