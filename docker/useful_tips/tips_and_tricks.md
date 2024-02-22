# Useful Tips

## Simple Tips

- Stop all containers: `docker stop $(docker ps -a -q)`
- Delete all containers, include their volumes: `docker rm -vf $(docker ps -a -q)`
- Delete all images: `docker rmi -f $(docker images -a -q)` (**TAKE CARE**)
- Delete all `EXITED` images: `docker rm $(docker ps -q -f status=exited)`
- Use `docker system df` to see space usage.
- The new `docker sbom` CLI command displays the SBOM (Software Bill Of Materials)
of any Docker image. This feature outputs the SBOM in a table or can be exported
into SPDX and CycloneDX formats.
- To find the container IP: run `docker inspect container_id` and search for `IPAddress`
under the `Networks/Bridge` section

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

## Getting Into a Container

Without `ssh` you have some options:

- `docker container run -it ....`
- `docker container exec -it ... bash`: bash here means to execute the `bash` command.
Note that some distros like `alpine` do not have it but instead have a `sh` command.
- `docker container start -ai ....`

## Docker Volumes

## Initializing Volumes

To create a named volume you can use the `-v` flag to specify the. So for example the code bellow would create a volume named "mysql-db", instead of a randomly generated id

```bash
docker container run 
    -d \
    --name mysql \
    -e MYSQL_ALLOW_EMPTY_PASSWORD=True \
    -v mysql-db:/var/lib/mysql mysql
```

## Cleaning Up Space

You can use "prune" commands to clean up images, volumes, build cache, and containers. Examples include:

- `docker image prune` to clean up just "dangling" images

- `docker system prune` will clean up everything

- The big one is usually `docker image prune -a` which will remove all images you're not using.
