# Sobre VMs dentro do Docker

Maioria dos containers dos containers rodam em um kernel Linux, o que significa que quando você instala o desktop Docker ou algumas das formas alternativas de rodar containers, estas ferramentas normalmente gerenciarão uma VM local rodando um pequeno kernel Linux e um pequeno sistema de arquivos de containers.

Portanto, uma das grandes coisas que o Docker Desktop fará por você é gerenciar a configuração, a atualização da segurança e, em seguida, a exclusão daquela pequena VM, tudo isso para você de forma transparente em segundo plano.

# Images and Layers

- Images are made up of file system changes and metadata
- Each layer is uniquely identified and store only once on a host
- A container is a single read/write layer on top of the image
- [Copy-on-write](https://adaptive.svbtle.com/fundamentals-of-docker-storage) is the technique that employs diffs from images to optimize storage and speed


# Docker Networks

- Containers shouldnt rely on IPs for intercomunnication as the containers lifetimes are so volatile. Use DNS instead.
- DNS for friendly names in built-in if you use custom virtual Networks.

# Getting Into a Container

Without `ssh` you have some options:

- `docker container run -it ....`
- `docker container exec -it ... bash`: bash here means to execute the `bash` command. Note that some distros like `alpine` do not have it but instead have a `sh` command.
- `docker container start -ai ....`

# Docker Volumes

## Initializing Volumes

To create a named volume you can use the `-v` flag to specify the. So for example the code bellow would create a volume named "mysql-db", instead of a randomly generated id

```
docker container run -d --name mysql -e MYSQL_ALLOW_EMPTY_PASSWORD=True -v mysql-db:/var/lib/mysql mysql
```

## Anonymous vs Named Volumes in Docker-Compose

If you look into the `drupal` image in dockerhub (as of 28/10/2022) you'll see this:

```
services:

  drupal:
    image: drupal:8-apache
    ports:
      - 8080:80
    volumes:
      - /var/www/html/modules
      - /var/www/html/profiles
      - /var/www/html/themes
```

Those are anonymous volumes, which means they're not named. Remember that we can name volumes by doing this:

```
services:

  drupal:
    image: drupal:8-apache
    ports:
      - 8080:80
    volumes:
      - modules:/var/www/html/modules
      - profiles:/var/www/html/profiles
      - themes:/var/www/html/themes
```

One cool feature of docker is that a new anonymous volume will be initialized with the existing content of the image at the same location, and so there's no need in this case to name volumes.

## Bind Mount

This is what makes local development inside containers possible. Binding mounts is just mapping a host file/dir to a container file/dir, which synchronizes them (but the if the container is deleted, the host file is preserved).

There's just one catch here: is that you have to either use docker-compose or run it with `docker container run ....`, you **can't** use a Dockerfile for this. For example the command bellow synchronize (map) files from the current directory the `/usr/share/nginx/html` directory.

```
docker container run -d --name nginx -v $(pwd):/usr/share/nginx/html nginx
```

# Cleaning Up Space

You can use "prune" commands to clean up images, volumes, build cache, and containers. Examples include:

- `docker image prune` to clean up just "dangling" images

- `docker system prune` will clean up everything

- The big one is usually `docker image prune -a` which will remove all images you're not using.

# Tips

- The new `docker sbom` CLI command displays the SBOM (Software Bill Of Materials) of any Docker image. This feature outputs the SBOM in a table or can be exported into SPDX and CycloneDX formats.

- About `tags`: they're simply pointers to an image ID.

- Use `docker system df` to see space usage.

- Always pin your product image version to the patch level!!

# Geral

- Docker Engine == OCI container runtime ([OCI](https://opencontainers.org/))
