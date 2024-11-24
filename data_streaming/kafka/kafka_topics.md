# Kafka Topics

- Kafka uses data replication to duplicate data across multiple machines to
prevent data loss in case a broker fails

- Commonlym the desired replication factor is set at the topic level and the
value should always be specificed when creating a topic

- If a leader broker fails or is removed from a cluster, a replica broker will
be become the new leader

- To become a new leader, the broker must be an In-Sync Replica (ISR)

- Configuration in Kafka includes configured the desired number of ISRs

- If the number of ISRs is too large this can slow down processing
