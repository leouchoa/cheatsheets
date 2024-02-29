# Quick Tips

- Stop all containers: `docker stop $(docker ps -a -q)`
- Always remember that docker stores all it's data inside `/var/lib/docker`
- Delete all containers, include their volumes: `docker rm -vf $(docker ps -a -q)`
- Delete all images: `docker rmi -f $(docker images -a -q)` (**TAKE CARE**)
- Delete all `EXITED` images: `docker rm $(docker ps -q -f status=exited)`
- Use `docker system df` to see space usage.
- The new `docker sbom` CLI command displays the SBOM (Software Bill Of Materials)
of any Docker image. This feature outputs the SBOM in a table or can be exported
into SPDX and CycloneDX formats.
- To find the container IP: run `docker inspect container_id` and search for `IPAddress`
under the `Networks/Bridge` section
- To see how much an image layer takes up, use `docker history image_name`
- To set env vars inside containers at runtime:
`docker run -e YOUR_ENV_VAR=your_env_var image`
- To find env vars set inside a container: `docker inspect container_id`. They're
available at `Config/Env`. Example:
`docker run -e APP_COLOR=blue -p 38282:8080 --name blue-app kodekloud/simple-webapp`
- To run docker on a remote host: `docker -H=remote-docker-engine:2375`. Example:
`docker -H=10.123.2.1:2375 run nginx`
- The mounts in docker:
  - bind mounts: `docker run -v`
  - volume mounts: `docker run -v /data/mysql:/var/lib/mysql mysql`
  - volume mounts newest version:
    `docker run \ --mount type=bind,source=/data/mysql,target=/var/lib/mysql \ mysql`
  - Note that docker will automatically create the volume, you don't
  need to manually create it with a `docker volume create ...`
- In the `docker ps -a` command, the `CONTAINER_ID` allows you to
find where is the container inside the `/var/lib/docker/containers` dir.
- Quick way to get data from inside a mysql container:
`docker exec mysql-db mysql -pdb_pass123 -e 'use foo; select * from myTable'`
