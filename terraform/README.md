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
sensitive information (e.g: aws credentials, secrets, etc.) and so you **must
not version it in github**.

More commands available at the [spacelift blogpost](https://spacelift.io/blog/terraform-commands-cheat-sheet).

## Usual Workflow

1. initialize repo: `terraform init`
2. check what changes would be made: `terraform plan`
3. apply the changes in the infrastructure: `terraform apply`
4. check state with `terraform state ...`
