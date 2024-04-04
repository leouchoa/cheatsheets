# Concepts

[Terraform architecture consists mainly of](https://spacelift.io/blog/terraform-architecture):

1. Terraform core
2. Providers
3. [State file](https://spacelift.io/blog/terraform-state#what-is-terraform-state)

## HashiCorp Configuration Language - HCL

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

## Registry

Terraform works with plugins for their resources provisioners. This means that
when you want to provision a resource (a local file or an aws s3 or aws ec2),
you gotta go to the [Terraform registry](https://registry.terraform.io/) to find
a plugin to connect to the provider to provision the resource.

Example: to a create a local file on your system, use the `"local_file"` plugin
in the [terraform registry website](https://registry.terraform.io/providers/hashicorp/local/latest/docs/resources/file).

## Immutable Infrastructure

Means that terraform will destroy the resource and recreate it entirely, instead
of updating a part of it. This is to take full advantage of cloud Infrastructure
in order to being everything from scratch, helping to prevent deployment failures.

To learn more:

- [digital ocean blogpost](https://www.digitalocean.com/community/tutorials/what-is-immutable-infrastructure)
- [hashicorp blogpost](https://www.hashicorp.com/resources/what-is-mutable-vs-immutable-infrastructure)

## Lifecycle Rules

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

## Data Sources

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

## Version Constraints

To lock plugins version. Example of a `main.tf` file:

```terraform
terraform {
  required_providers {
    helm = {
      source = "hashicorp/helm"
      version = "2.12.1"
    }
  }
}
```

## Provisioners vs Providers

As explained by [spacelift](https://spacelift.io/blog/terraform-provisioners),
Terraform providers are plugins used to authenticate
with cloud platforms, services or other tools, allowing users to create, modify,
and delete resources declared in the Terraform configurations. Provisioners are
used only for copying files or executing local or remote operations.

**You should avoid using provisioners, consider them a last resort**,
but there three types:

- file: used for copying
- local-exec: used for local operations
- remote-exec: used for remote operations.
