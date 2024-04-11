# Quick Tips

## Renaming Resources

When renaming resources, use `terraform state mv old_name new_name`. But
also remember to rename the resource in `main.tf`, because the terraform
command will only alter the in-memory state data, not in the file.

## Enabling Logs

Can be achieved with:

- enabling logs: `export TF_LOG=desired_log_level_all_caps`
  - Log levels are:
    - `INFO`
    - `WARNING`
    - `ERROR`
    - `DEBUG`
    - `TRACE` (most verbose)
- exporting logs to a file: `export TF_LOG_PATH=/tmp/terraform.log`
  - note that you can't export logs by just setting the path, you
  also have to enable with the `TF_LOG` var.
- desabling logs: `unset TF_LOG_PATH`

## Importing Provisioned Configurations

Suppose you've configured your aws resources with the management console and
you're trying to migrate the configuration to IaC with `terraform`. In this case
you have import the existing configuration to `terraform` in order for it be able
to provision your resources.

```bash
terraform import <resource_type>.<resource_name> <attribute>
```

**Note: the import command does not update the configuration files, only the
state file. You have to manually write the configuration file.**

Steps:

1. write the `main.tf` file with the resource name in barebone
2. run the `terraform import ...` command, it will update the remote state
3. run `terraform state show` to inspect elements and write the remaining
parts of the `main.tf` file.

## Conditional Expressions

Example:

```terraform
resource "aws_instance" "mario_servers" {
     ami = var.ami
     instance_type = var.name == "tiny" ? var.small : var.large
     tags = {
          Name = var.name
     }
}
```

The `argument = var.variable == "something" ? var.another_variable : var.some_other_variable`
means `condition ? true_val : false_val`
