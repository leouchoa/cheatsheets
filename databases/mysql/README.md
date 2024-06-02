# Connecting To a Remote DB with Configuration File

1. First find the locations `mysql` will search for this configuration file. You can find those places by running `mysql --help | grep "Default options" -A 1`. In my case (macos ventura 13.1) it prints:

```
Default options are read from the following files in the given order:
/etc/my.cnf /etc/mysql/my.cnf /usr/local/mysql/etc/my.cnf ~/.my.cnf
```

2. Chose the name of the file based on the previous output and create the file. For example: `~/.my.cnf`

3. Add the contents of the file. For example:

```
[clientTARGETDATABASE]
database=database_name
host=host_path
user=your_user_name
password=your_password
ssl_ca=path_to_ssl_ca_if_available
```

4. To query from the database run: `mysql --defaults-group-suffix=TARGETDATABASE -e "show databases;\q"`
