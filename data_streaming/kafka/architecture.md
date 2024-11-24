# Kafka Architecture

## How Kafka Works - Summary

- A Kafka Broker is an individual Kafka server
- A Kafka Cluster is a group of Kafka Brokers
- Kafka uses Zookeeper to elect topic leaders and store its own configuration
- Kafka writes log files to disk on the Kafka brokers themselves
- How Kafka achieves scale and parallelism with topic partitions
- How Kafka provides resiliency and helps prevent data loss with data replication

## Architecture

- Kafka servers are referred to as brokers

- All of the brokers that work together are referred to as a cluster

- Clusters may consist of just one broker, or thousands of brokers

- Apache Zookeeper(opens in a new tab) is used by Kafka brokers to determine
which broker is the leader of a given partition and topic

- Zookeeper keeps track of which brokers are part of the Kafka cluster

- Zookeeper stores configuration for topics and permissions (Access Control
Lists - ACLs)
- ACLs are Permissions associated with an object. In Kafka, this typically
refers to a user’s permissions with respect to production and consumption, and/
or the topics themselves.

- Kafka nodes may gracefully join and leave the cluster

- Kafka runs on the Java Virtual Machine (JVM)

## Data Storage

The way that Kafka stores data is pretty simple. It has a data directory on a
disk where it stores logs of data and text files. `/var/lib/kafka/data` is a
directory where Kafka sorts data in your workspace and in many Kafka
productions systems.

- Each topic receives its own sub-directory with the associated name of the topic.
- Kafka may store more than one log file for a given topic

## Message Ordering

Message ordering is only guaranteed within a partition in Kafka. If your topic
has more than one partition, Kafka provides no guarantees that the messages
will be consumed in the order they were produced. For many applications, this
is an acceptable trade-off for increasing the parallelism and speed of
consumption. Your producer applications may still add metadata to the event
header or message body itself to indicate ordering. However, this logic would
belong to your application, and not Kafka itself. For example, you may place
an increasing ID sequence in every message (eg 1, 2, 3, and so on) or a
granular timestamp to indicate the order of a message.

## Preventing Data Loss

Based on an understanding that machines can fail, one of the core features of
Kafka is the concept of replication.

- Replication – when the data is written to many brokers
- Leader Broker – the broker responsible for sending and receiving data to
clients for a given topic partition
- Replicas – any brokers that are storing replicated data

If the leader broker were to fail, one of the replicas would be elected the
new topic partition leader by a zookeeper election.

The exact number of replicas used can be configured globally as a Kafta server
configuration item or set individually on every topic you create. But keep a
few things in mind:

- You can not have more replicas than brokers
- Data replication has overhead
- Always enable replication in a production cluster to prevent data loss

## How Kafka is secured?

Kafka is secured via mutual TLS (mTLS) or Simple Authentication and Security
Layer (SASL). Configuring these security mechanisms is outside of the scope of
this class. However, you can read more about them in this [excellent Confluent
blog post](https://www.confluent.io/blog/secure-kafka-deployment-best-practices/). For hobbyist usage, Kafka is typically run
unencrypted. However, if you are using Kafka at your job, or to transport
sensitive information, you should either invest the time to secure Kafka or
work with your company's security team to help you accomplish this.

## Refs

- [Why Does Kafka Needs Zookeeper](https://www.cloudkarafka.com/blog/2018-07-04-cloudkarafka_what_is_zookeeper.html)
