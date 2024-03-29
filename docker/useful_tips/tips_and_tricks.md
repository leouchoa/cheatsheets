# Useful Insights


## About ports

**Most important tip:** draw box, just draw the boxes. It will save you a **LOT**
of time.

Remember that:

- the left port is related to the outer box (usually host).
- the right port is related to the inner box (usually container).

Example:

To run an instance of an image with a *tag* and map port `8080` on the *container*
(inner box) to `38282` on the *host* (outer box): `docker run -p 38282:8080 image/imageeee:tag`.
Practical example: `docker run -p 38282:8080 kodekloud/simple-webapp:blue`

### Interpreting `docker ps` Ports

Consider the following output:

```bash
$ docker ps
CONTAINER ID   IMAGE          COMMAND                  CREATED         STATUS         PORTS                                           NAMES
ad288ba37cbb   nginx:alpine   "/docker-entrypoint.…"   6 seconds ago   Up 5 seconds   0.0.0.0:3456->3456/tcp, 0.0.0.0:38080->80/tcp   dazzling_mayer
```

Remember that:

- Ports on the left(before ->) are published on the host.
- Ports on the right(after ->) are exposed on the container.

This means that:

- There 2 published ports, separated by a comma.
- On the container there are 2 published ports
- **On the container** the exposed ports are: 3456 and 80.
- **On the host** the exposed ports are: 3456 and 38080.

## To Find Where is a Container Image is Stored

Docker folder is located at `/var/lib/docker`. If you want to find
where a certain container is located:

```bash
docker ps -a
```

[good ref](https://www.freecodecamp.org/news/where-are-docker-images-stored-docker-container-paths-explained/)

## `CMD` Vs `ENTRYPOINT`

Both execute commands, but:

- `CMD` **replaces** the command entirely.
- `ENTRYPOINT` **appends** the command line parameters.

So in the first `Dockerfile` bellow if you would have to run
`docker run ubuntu-sleeper sleep 10` in order to replace the
instruction, whereas in the second `Dockerfile` you would only
have to run `docker run ubuntu-sleeper 10`.

```Dockerfile
# Dockerfile 1
FROM ubuntu

CMD sleep 5
```

```Dockerfile
# Dockerfile 2
FROM ubuntu

ENTRYPOINT sleep
```

If you want to specify a default value for the parameter, then
use both `CMD` and `ENTRYPOINT`:

```Dockerfile
# Dockerfile 2
FROM ubuntu

ENTRYPOINT sleep
CMD 5
```

## Getting Into a Container

Without `ssh` you have some options:

- `docker container run -it ....`
- `docker container exec -it ... bash`: bash here means to execute the `bash` command.
Note that some distros like `alpine` do not have it but instead have a `sh` command.
- `docker container start -ai ....`

## Docker Volumes

### Initializing Volumes

To create a named volume you can use the `-v` flag to specify the volume.
So for example the code bellow would create a volume named "mysql-db",
instead of a randomly generated id.

```bash
docker container run 
    -d \
    --name mysql \
    -e MYSQL_ALLOW_EMPTY_PASSWORD=True \
    -v mysql-db:/var/lib/mysql mysql
```

### Bind Mounts vs Volume Mounts

- Volume Mount: mounts a volume from `/var/lib/docker` volumes directory.
- Bind Mount: mounts a directory from any location on the docker host.

**Note**: using the `-v` flag in `docker run -v` is the old way. The
newest and suggested way is to use the `--mount` flag. Example:

```bash
docker run \
    --mount type=bind,source=/data/mysql,target=/var/lib/mysql \
    mysql
```

## Cleaning Up Space

You can use "prune" commands to clean up images, volumes, build cache, and containers. Examples include:

- `docker image prune` to clean up just "dangling" images

- `docker system prune` will clean up everything

- The big one is usually `docker image prune -a` which will remove all images you're not using.
