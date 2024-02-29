# Swarm

Container orchestration system.

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
