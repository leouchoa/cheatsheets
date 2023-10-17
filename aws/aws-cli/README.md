# AWS cli

## Configs

More info about how to configure aws cli profiles [here](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html#cli-configure-files-where).

- list profiles: `aws configure list-profiles`
- list profile config: `aws configure list --profile <PROFILE_NAME>`

If you wanna set a profile as default, use the `AWS_DEFAULT_PROFILE` env var. Example: `export AWS_DEFAULT_PROFILE=account1`

## Command-Line statements for Launching and EC2 Instance

Many of those commands were taken from the udacity [cloud devops engineer course](https://learn.udacity.com/nanodegrees/nd9991)

Step 1: Create Key-Pair

`aws ec2 create-key-pair --key-name --query –output text > pem`

Step 2: Create a Security Group

`aws ec2 create-security-group –group-name`

Step 3: EC2 instance

`aws ec2 run-instances --image-id ami-xxxxxxxx --count 1 --instance-type t2.micro --key-name`

## Create EBS Volume

```bash
aws ec2 create-volume 
--availability-zone < zone value goes here>
--size < value goes here>
--tag-specifications 'ResourceType=string,Tags=[{Key=string,Value=string},{Key=string,Value=string}]'
```

## Listing Volumes

```bash
aws ec2 describe-volumes \
-- filters Name=tag:Name,Values=Test* \
-- query "Volumes[*].{ID:VolumeId,Tag:Tags}"
```

## Creating a VPC

```bash
aws ec2 create-vpc \
    --cidr-block 10.0.0.0/16 \
    --tag-specification ResourceType=vpc,Tags=[{Key=Name,Value=MyVpc}]
```

To view some details of your vpcs:

```bash
aws ec2 describe-vpcs
```

## Lambda

```bash
aws lambda create-function \
    --function-name < function name> \
    --runtime nodejs14.x \
    --zip-file fileb://my-function.zip \
    --handler my-function.handler \
    --role arn:aws:iam::xxxxx:role/service-role/< function name>-role-tges6bf4
```

## Create an S3 bucket

```bash
aws s3api create-bucket  \
-- bucket < name of the bucket goes here> \
-- region < name of the region goes here>
```

## Upload files to S3

```bash
aws s3 sync < source> < target>
```

## DynamoDB table creation

```bash
aws dynamodb create-table  \
-- table-name < table name goes here> \
-- attribute-definitions AttributeName=< name goes here>,AttributeType=S  \
-- key-schema AttributeName=< name goes here>,KeyType=HASH \
-- provisioned-throughput ReadCapacityUnits=< value goes here>,WriteCapacityUnits= < value goes here> \
```
