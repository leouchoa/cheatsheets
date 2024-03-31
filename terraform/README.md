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
    - `terraform state list`: list resources being used.
    - `terraform state show resource_type.resource_name`: shows the current
    state of the resource.

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

### Immutable Infrastructure

Means that terraform will destroy the resource and recreate it entirely, instead
of updating a part of it. This is to take full advantage of cloud Infrastructure
in order to being everything from scratch, helping to prevent deployment failures.

To learn more:

- [digital ocean blogpost](https://www.digitalocean.com/community/tutorials/what-is-immutable-infrastructure)
- [hashicorp blogpost](https://www.hashicorp.com/resources/what-is-mutable-vs-immutable-infrastructure)

### Lifecycle Rules

Even though terraform employs immatuble infrastructure, there are many cases where
don't want to destroy or alter a given resource, like a production database. In that
case we can employ some rules on how to deal with such scenarios:

- `create_before_destroy`
- `prevent_destroy`
- `ignore_changes`

They go on code like the following example:

```terraform
resource "local_file" "foo" {
  content  = "foo!"
  filename = "/root/asd.txt"
  lifecycle {
    create_before_destroy = true
  }
}
```

### Data Sources

Suppose you add another file with important data into your terraform directory
and you would like to read the data inside this file. Example:

```terraform
resource "local_file" "foo" {
  content  = "foo!"
  filename = data.local_file.dog.content
}

data "local_file" "dog" {
  filename = "/root/dog.txt"
}
```

Usually used to read data from remote resources, like ec2s and s3s data.
