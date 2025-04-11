# AWS PrivateLink

It's basically private communication between ENIs (Elastic Network Interfaces)
for traffic routing between VPCs, which happens entirely within AWS's
private network. Example:

```text
  +---------------------+         +--------------------------+
  |                     |         |                          |
  |  Consumer VPC       |         |  Service Provider VPC    |
  |                     |         |                          |
  |  +-------------+    |         |  +--------------------+  |
  |  | Interface  |     |         |  | Interface Endpoint |  |
  |  | Endpoint (ENI)  <---> DNS Resolution ---> (ENI)    |  |
  |  +-------------+    |         |  +--------------------+  |
  |                     |         |                          |
  |                     |         |                          |
  |                     |         |   +-----------------+    |
  |                     |         |   | Network Load    |    |
  |                     |         |   | Balancer (NLB)  |    |
  |                     |         |   +-----------------+    |
  |                     |         |                          |
  |                     |         |                          |
  | +-----------------+ |         |   +-----------------+    |
  | | Backend Service | |         |   | Backend Service |    |
  | +-----------------+ |         |   +-----------------+    |
  |                     |         |                          |
  +---------------------+         +--------------------------+
       |                             |
       |                             |
       v                             v
  Consumer VPC ---> Provider ENI ---> NLB ---> Backend Service

```

Note that some services like Lambda Functions are, by default, not attached to
any VPC. When you create a Lambda function without specifying a VPC, it runs
in the default VPC but is not connected to any specific subnet or ENI
within that VPC. However you absolutely can specify them to run from within
a VPC. When Lambda is connected to a VPC it:

- Uses ENIs of the selected subnets, so it can access other resources within
that VPC (e.g., EC2, RDS).

- Will not be publicly accessible by default.

- Will need to pass through an NAT Instance/GW or IGW to be able to access
internet.

However you can alternatively create a VPC Endpoint/PrivateLink inside the VPC to
access your Lambda function as a private service. This way the Lambda function
can be accessed from the VPC without traversing the public internet and you
won't need to go through creating/attaching them to VPCs.
Note that your lambda will still be public available (default behavior) but
the routing happens entirely within AWS's private network. This means the
traffic stays private between the consumer VPC and provider VPC, over the AWS
backbone.

## Integrating With Api Gateway

If you want to allow private, secure access to the Lambda function
from within your VPC or other VPCs, API Gateway can be used as a middle
layer. In that case you can configure the API Gateway to integrate privately
with Lambda, ensuring that the function is not exposed to the public internet,
being only accessible through the private API endpoint.

Example:

1. Create a Private API in API Gateway.

2. Set the API Gateway endpoint to be private, restricting access to a specific
VPC or set of VPCs.

3. Create a VPC Endpoint in your VPC for API Gateway to ensure private
communication between your Lambda function and your VPC.

4. The Lambda function can then be triggered via the Private API Gateway
endpoint from resources within your VPC.
