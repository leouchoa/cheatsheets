# Terraform Cheatsheet

## Quick Tips

- `terraform init`: **first command to run** to init the current
dir with terraform config files.
- `terraform plan`: creates a preview of the execution plan.
- `terraform apply`: apply the config plan.
- `terraform destroy`: destroys the provisioned resources.
- `terraform show`: displays the current `terraform` state.
- `terraform output`: displays output variables

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
