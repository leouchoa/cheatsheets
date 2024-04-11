# Terraform State

The state file is considered to be the description of the current state of the
infrastructure. It maps the configuration file to real world infrastructure.
Some benefits:

- single source of truth
- metadata and dependency tracking
- resource creation/deletion in  correct order
- team collaboration

Important: take notice that the `terraform.tfstate` file might have
sensitive information (e.g: aws credentials, secrets, etc.) and so you **must
not version it in github**.

## Remote Backends

State locking is a solution to the problem of inconsistency between users.
But the `terraform.tfstate` contains sensitive data and must not be versioned
in github. A solution to this - called remote backend - is:

1. Store the `terraform.tfstate` file in aws S3.
2. Perform state locking and consistency checks with aws dynamoDB.

By using this solution with, for example s3/dynamoDB, running `terraform plan`
or `terraform apply` will lock the state file and pull it down from the remote backend
into memory. Then any subsequent changes to the state will be automatically uploaded
to the backend and after the operation is complete, the lock will be released.
