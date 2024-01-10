# Apache Web Server

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
