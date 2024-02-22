# Quick Tips

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
- To see how much an image layer takes up, use `docker history image_name`
- To set env vars inside containers at runtime:
`docker run -e YOUR_ENV_VAR=your_env_var image`
- To find env vars set inside a container: `docker inspect container_id`. They're
available at `Config/Env`. Example:
`docker run -e APP_COLOR=blue -p 38282:8080 --name blue-app kodekloud/simple-webapp`

