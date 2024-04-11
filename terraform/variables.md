# Variables

## How To Define Them

You can define variables to better organize your code by putting them
inside a specific file (name for example, `variables.tf`) and define them:

```terraform
variable "your_variable" {
  default = "variable of type string"
  type = "string"
  description = "description of the variable"
}

variable "your_another_variable" {
  default = "another variable of type string"
  type = "string"
  description = "another description of the variable"
}
```

Then to use them:

```terraform
resource "local_file" "foo" {
  content  = var.your_variable
  filename = var.your_another_variable
}
```

### Alternative Ways

You can also override values in the cli:

```bash
terraform apply -var "content=your content here"  "file=/root/your_content_file"
```

or use environment variables:

```bash
export TF_VAR_content="you content here!"
export TF_VAR_filname="/root/your_content_file"
```

or use variable definition files:

```terraform
content = "your content here"
filename = "/root/your_content_file"
```

but those variable files should either end with `.tfvars` or `.tfvars.json`.
Those are automatically found and loaded by terraform, as well files ending
with `.auto.tfvars` or `.auto.tfvars.json`.

Oh attention that the loading of variables have [precedence](https://developer.hashicorp.com/terraform/language/values/variables#variable-definition-precedence).

## Types

[Types constraints](https://developer.hashicorp.com/terraform/language/expressions/type-constraints) are:

- string (primitive type)
- bool (primitive type)
- number (primitive type)
- set (collection type)
- list (collection type)
- map (collection type)
- objects (structural type)
- tuple (structural type)
- any (dynamic type)
- optional

The Terraform language will automatically convert number and bool values
to string values when needed, and vice-versa as long as the string contains
a valid representation of a number or boolean value.

## Resource Attributes

The resources you create can have attributes that are store in terraform state.
You can access them by using the interpolation sequence `${resource_type.resource_name.attribute_name}`.

In the example bellow the resouce `random_pet` creates an attribute called
`id`, which can furthermore be used:

```terraform
resource "local_file" "foo" {
  content  = "my own content prefix is ${random_pet.pet.prefix}"
  filename = var.your_another_variable
}

resource "random_pet" "pet" {
  prefix = var.prefix
  separator = var.separator
  length = var.length
}
```

## Dependencies

You make one resource explicitly depend on another by adding a `depends_on` atribute
on the resource. Example:

```terraform
resource "local_file" "foo" {
  content  = "my own content prefix is ${random_pet.pet.prefix}"
  filename = var.your_another_variable
  depends_on = [
    random_pet.pet
  ]
}

resource "random_pet" "pet" {
  prefix = var.prefix
  separator = var.separator
  length = var.length
}
```

Otherwise it would be a implicit dependency.

## Output Variables

You can add metadata about resources created attributes:

```terraform
resource "local_file" "foo" {
  content  = "my own content prefix is ${random_pet.pet.prefix}"
  filename = var.your_another_variable
  depends_on = [
    random_pet.pet
  ]
}

resource "random_pet" "pet" {
  prefix = var.prefix
  separator = var.separator
  length = var.length
}

output pet-name {
  value = random_pet.pet.id
  description = "the name of the randomly generated pet name"
}
```

This is best used to display details about a provisioned resource
or for further input into ansible playbooks.
