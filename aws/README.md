# AWS cli

Many of those commands were taken from the udacity [cloud devops engineer course](https://learn.udacity.com/nanodegrees/nd9991)

## Command-Line statements for Launching and EC2 Instance

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
