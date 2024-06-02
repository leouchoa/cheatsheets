terraform {
  required_providers {
    aws = {
      source = "hashicorp/aws"
      version = "5.11.0"
    }
  }
}

provider "aws" {
  region                      = var.region
  skip_credentials_validation = true
  skip_requesting_account_id  = true
  endpoints {
    iam = "http://aws:4566"
    ec2 = "http://aws:4566"
    s3 = "http://aws:4566"
  }
}

