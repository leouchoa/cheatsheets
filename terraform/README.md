# Terraform Cheatsheet

## Quick Tips

- `terraform init`: **first command to run** to init the current
dir with terraform config files.
- `terraform plan`: creates a preview of the execution plan.
  - it also refreshes the state.
- `terraform apply`: apply the config plan.
- `terraform validate`: validates if the syntax is correct.
- `terraform fmt`: a linter.
- `terraform destroy`: destroys the provisioned resources.
- `terraform refresh`: queries the resource state and updates the state file.
  - **it does not modify the infrastructure resource, only the state file.**
  - automatically run by `plan` and `apply` commands.
- displaying commands:
  - `terraform show`: displays the current `terraform` state.
  - `terraform output`: displays output variables
  - `terraform providers`: list the current providers/plugins.
    - the `mirror` endpoint is very good to copy providers config
    file into another place. Example: `terraform providers mirror /new/path`
    - `terraform graph`: it creates a graph in the `.dot` file format,
    which can be used to feed a library like `graphviz` to visualize the
    plot.

Important: take notice that the `terraform.tfstate` file might have
sensitive information (e.g: aws credentials, secrets, etc.) and so you must
not version it in github.

## Concepts

### HashiCorp Configuration Language - HCL

Usual format:

```terraform
<block> <parameters> {
    key1 = value1
    key2 = value2
}
```

Attention: the `resource` type provides two types of information: provider and resource.
In the `"local_file"` provider example bellow `local` is the provider and
`file` is the resource.

```terraform
resource "local_file" "foo" {
  content  = "foo!"
  filename = "/root/asd.txt"
}
```

### Registry

Terraform works with plugins for their resources provisioners. This means that
when you want to provision a resource (a local file or an aws s3 or aws ec2),
you gotta go to the [Terraform registry](https://registry.terraform.io/) to find
a plugin to connect to the provider to provision the resource.

Example: to a create a local file on your system, use the `"local_file"` plugin
in the [terraform registry website](https://registry.terraform.io/providers/hashicorp/local/latest/docs/resources/file).
