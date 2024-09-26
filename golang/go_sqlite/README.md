# Simple HTTP server with `sqlite3`

Boilerplate code for a simple http server using the `net/http` for routing
with `sqlite3` as the backend.

If you want live reloading of the server, check [air](https://github.com/air-verse/air).
But before running it with `air`, make sure that the `cmd` entry of your air
configuration file points to the correct direction, after updating the
`.air.toml` ( generated from `air init` ) file to:

```toml
cmd = "go build -o ./tmp/main ./cmd/web/"
```
