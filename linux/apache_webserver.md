# Just Enough Apache Web Server

Attention, in the docker image `httpd-2.4`, those informations are
at a different place.

## Concepts

### VirtualHost

It's a logical division of the apache web server. Each can be configured with
it's own server name and doc root. You can configure it in the `httpd.conf` file.
The example bellow shows one that sets a domain name and the [DocumentRoot](https://support.reclaimhosting.com/hc/en-us/articles/4416677995799-Understanding-Document-Roots).

```bash
<VirtualHost *:80>
    ServerName www.houses.com
    DocumentRoot /var/www/houses
</VirtualHost>
```

### Hosting Many Websites

A single apache server can host multiple websites. You can do this by defining
multiple virtual hosts in the apache config file. Example in `httpd.confg`:

```bash
<VirtualHost *:80>
    ServerName www.houses.com
    DocumentRoot /var/www/houses
</VirtualHost>

<VirtualHost *:80>
    ServerName www.oranges.com
    DocumentRoot /var/www/oranges
</VirtualHost>
```

Note: remember to add the entries to `/etc/hosts`:

```bash
# Host Database
127.0.0.1 localhost
127.0.0.1 www.houses.com
127.0.0.1 www.oranges.com
```

and to restart the service with `service httpd restart`

#### Better Organization of Multiple Websites

You can separate websites config files into, e.g `/etc/httpd/conf/houses.conf`
and `/etc/httpd/conf/oranges.conf` by adding a file per website and including
them in the `httpd.config` configuration file. In that case:

Houses `/etc/httpd/conf/houses.conf` contains:

```bash
<VirtualHost *:80>
    ServerName www.houses.com
    DocumentRoot /var/www/houses
</VirtualHost>

```

Oranges `/etc/httpd/conf/oranges.conf` contains:

```bash
<VirtualHost *:80>
    ServerName www.oranges.com
    DocumentRoot /var/www/oranges
</VirtualHost>

```

and `httpd.conf` contains:

```bash
# ServerName www.example.com:80
ServerName www.houses.com:80

Include conf/houses.conf
Include conf/oranges.conf
```

## Instalation

```bash
yum install httpd
service httpd start
service httpd status
```

## How to View the logs

```bash
cat /var/log/httpd/access_log
cat /var/log/httpd/error_log
```

## Config Files

```bash
cat /etc/httpd/conf/httpd.conf
```
