# Swarm

It's a container orchestration system that consists of multiple Docker hosts
which run in Swarm mode.

When you create a swarm service, you define its optimal state - number of replicas,
network and storage resources available to it, ports the service exposes
to the outside world, and more. Docker works to maintain that desired state.

For instance, if a worker node becomes unavailable, Docker schedules
that node's tasks on other nodes.

## Concepts

1. Node: A node is a Docker engine instance that participates in the Swarm.
2. Worker: The manager node transfers tasks to the worker nodes,
who receive and execute them.
Worker nodes are not involved in task management.
3. Manager: The one responsible for cluster administration activities such as:
    - maintaining the cluster state
    - scheduling services
    - serving Swarm mode HTTP API endpoints
4. Leader: Leader means the node that is the primary manager node and makes
all swarm management and orchestration decisions for the swarm (
remember that you can have many manager nodes).

Docker recommendation: maximum of 7 manager nodes.

## Raft Consensus

It starts with the problem of having only manager node, because if this node
goes down, things go bad.

Then to solve this add managers, which creates the [problem of who makes the decision](https://www.baeldung.com/cs/consensus-algorithms-distributed-systems).

To solve this you allow only one manager to make decisions, called the **leader**,
but not to bother the other ones make them vote too so the decisions are better made.

### The Raft Database

Each manager has a raft database and it's important that they're all in sync.

### Quorum

The minimum number of managers present to make a decision:

$$
\text{ceil}(\text{number of managers}/2 + 1)
$$

### Fault Tolerance Formula

$$
\text{ceil}((\text{number of managers} -1 )/2)
$$

## Swarm Mode Setup

How it works:

1. Start the swarm on the manager node: `docker swarm init`
2. Make nodes join the swarm: `docker swarm join-token worker`

### Dealing with Cluster Failure Due to All Managers Going Down

The best solution when all your managers go down is to bring all of them back online.
But if you can bring at least one up, then run `docker swarm init --force-new-cluster`.
After that you can promote new nodes to managers by going to a worker node
and running `docker node promote`.

## Networks

**Gold tip**: always remember that all containers in docker can resolve their
names because docker has a built-in dns server! This allows you to specify
containers by their name, when using services like mysql connections, instead
of using IPs!

- The built-in DNS server runs on 127.0.0.11

### Overlay

Suppose you have some containers inside multiple hosts, for example 3 hosts
with 2 containers each, and you want those containers to share the same
internal private network. Then you can create a new network, the *overlay* network,
that achieves exactly that and attach the containers to that network.

### Ingress Networks

Suppose you have a swarm node that has one container with two replicas. Those containers
work on port 5000 and you map them to port 80 on the host. But then you've got a
problem because the mappings are not unique.
That's when the ingress network comes in.

The ingress network is automatically created by docker swarm that has a load balancer
to redirects traffic to the appropriate ports/containers, effectively creating
a routing mesh and helps in routing traffic.

Just so you know: the ingress network is a type of an overlay network, meaning it
is a single network that spans through the nodes.
