# Boto3

## Needed Packages

Install `boto3` and `awscli`

## AWS Connection Entrypoint

The entrypoint for using the `boto3` package to control AWS are `client` and `resource`.
The table bellow depicts some differences between them:

|  Topic                 | boto3.client()     | boto3.resource() |
|------------------------|--------------------|------------------|
| aws api response type  | dict               | class            |
| thread safe?           | yes                | now              |
| Abstraction Level      | low-level          | high             |

When chosing between `client` and `resource`, use `resource` if possible because
it allows you to write more readable code as:

1. don't need to worry about pagination or memory utilization.
2. you can access everything from `client` from `resource`.

When accessing an user account from `boto3` you have keep in mind to at least have:

- `aws_access_key_id`
- `aws_secret_access_key`
- `region_name`

Example:

```python
client = boto3.client(
    'iam',
    aws_access_key_id="XXXXXXX",
    aws_secret_access_key="YYYYYYY",
    region_name="us-east-2"
)
```

Recommendation: prefer using `sessions` instead of just `clients`. That is, prefer using this:

```python
session = boto3.Session()
s3 = session.client('s3')
ddb = session.resource('dynamodb')
```

instead of this:

```python
s3 = boto3.client('s3')
ddb = boto3.resource('dynamodb')
```

Reasoning can be found [here](https://ben11kehoe.medium.com/boto3-sessions-and-why-you-should-use-them-9b094eb5ca8e),
but basically boils down to being easier to code when dealing with multi-region,
multi-account or when you need to assume roles across different AWS accounts.

## Assuming Roles

## Resources

- [hands-on cloud boto3 intro](https://hands-on.cloud/introduction-to-boto3-library/#advanced-boto3-library-topics)
