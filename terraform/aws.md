# Working With AWS

First of all, you gotta have the credentials for aws. Don't put them in the
terraform script, because it will be in version control platforms. For that
the most recommended option is to use environment variables:

```bash
export AWS_ACCESS_KEY=huoe1h23ou12j312309123
export AWS_SECRET_ACCESS_KEY_ID=O!@#KP!@:S{@!!@#)!@)$%!@#!@%!#@123123iojjasdajsd}
export AWS_REGION=us-east-1
```
