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
