# Meta Arguments

## Count

Avoid using it, use for-each because:

....

Example:

File named `main.tf`

```terraform
resource "local_sensitive_file" "name" {
    filename = var.users[count.index]
    content = var.content
    count = length(var.users)
}
```

The `variables.tf` file:

```terraform
variable "users" {
    type = list
}
variable "content" {
    default = "password: S3cr3tP@ssw0rd"
  
}
```

## For Each

File `main.tf`:

```terraform
resource "local_sensitive_file" "name" {
    filename = each.value
    for_each = toset(var.users)
    content = var.content
}
```

File `variables.tf`:

```terraform
variable "users" {
    type = list(string)
    default = [ "/root/user10", "/root/user11", "/root/user12", "/root/user10"]
}
variable "content" {
    default = "password: S3cr3tP@ssw0rd"
  
}
```
