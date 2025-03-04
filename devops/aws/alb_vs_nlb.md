# Application Load Balancer vs Network Load Balancer

Both **Network Load Balancer (NLB)** and **Application Load Balancer (ALB)**
are used to distribute incoming traffic to multiple targets (like EC2 instances)
in different availability zones.

## 1. Layer of Operation

- **Network Load Balancer (NLB)** operates at the **Transport Layer
    (Layer 4)** of the OSI model. It handles traffic based on IP protocol data
    (TCP/UDP).
- **Application Load Balancer (ALB)** operates at the **Application Layer
    (Layer 7)** of the OSI model. It can inspect the content of the traffic,
    such as HTTP and HTTPS headers, and make routing decisions based on URL
    paths, HTTP methods, and host headers.

## 2. Traffic Types

- **NLB** is designed for handling **TCP/UDP traffic**, often used for real-time
    applications where low latency is crucial (e.g., gaming, VoIP, or IoT).
- **ALB** is designed for handling **HTTP/HTTPS traffic**, making it ideal for
    web applications and services that require routing based on application-level
    attributes (e.g., URL path or host).

## 3. Performance

- **NLB** is optimized for high performance and can handle millions of requests
    per second with extremely low latency. It’s designed to handle volatile or
    sudden changes in traffic patterns.
- **ALB** is also highly scalable but is focused on web traffic and can
    introduce a bit more latency due to its deep packet inspection and
    content-based routing.

## 4. Routing Features

- **NLB** can route based only on **IP address and port**. It does not inspect
    the content of the request.
- **ALB** can route traffic based on **URL paths**, **hostnames**, **HTTP
headers**, and other HTTP-specific parameters. It also supports advanced
    features like **WebSocket** and **HTTP/2**.

## 6. Health Checks

- **NLB** performs health checks at the **TCP level**, ensuring the target can
    accept TCP connections.
- **ALB** performs health checks at the **HTTP/HTTPS level**, ensuring the
    application is responding as expected (e.g., HTTP 200 OK).

## 7. SSL/TLS Termination

- **NLB** does **not** handle SSL/TLS termination. It forwards the traffic
    as-is to the backend targets.
- **ALB** supports SSL/TLS termination, meaning it can offload the encryption
    and decryption work from backend servers, which can help reduce the load on
    the backend.

## 8. Support for IP Address Targets

- **NLB** allows routing traffic to **IP addresses**, which means you can route
    traffic to any resource within your VPC that has an IP address, such as EC2
    instances, on-premises servers, or even Lambda functions.
- **ALB** routes traffic to **target groups** consisting of registered EC2
    instances or IP addresses.

## 9. Scaling

- **NLB** scales automatically to handle the increasing number of connections,
    and its performance can handle millions of connections per second.
- **ALB** also automatically scales based on traffic, but because it performs
    more complex routing and content inspection, the scaling mechanism is
    optimized for HTTP/S traffic rather than raw network connections.

## Summary

| Feature                 | **Network Load Balancer (NLB)**                    | **Application Load Balancer (ALB)**              |
|-------------------------|----------------------------------------------------|--------------------------------------------------|
| **Layer**               | Layer 4 (TCP/UDP)                                  | Layer 7 (HTTP/HTTPS)                             |
| **Traffic Types**       | TCP, UDP                                           | HTTP, HTTPS                                      |
| **Routing**             | IP address and port                                | URL path, hostname, HTTP headers, etc.          |
| **Latency**             | Low latency, optimized for high-performance       | Slightly higher latency due to deep inspection   |
| **Use Cases**           | Real-time apps, databases, IoT, gaming            | Web apps, microservices, content-based routing   |
| **Health Checks**       | TCP-level health checks                            | HTTP/HTTPS-level health checks                   |
| **SSL/TLS Termination** | No SSL/TLS termination                             | SSL/TLS termination supported                    |
| **Targets**             | EC2 instances, IP addresses                       | EC2 instances, IP addresses                     |
