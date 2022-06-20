# Postgres

- list databases: `\l`
- describe a table `\d tablename`
- switch to the database that you want to work with: `\c database`


## Connection Strings

Connecting to localhost:

```
$ psql -Atx -U user_name -d user_name -h localhost -p 5432 -c 'select current_date'

$ psql -Atx postgresql://user_name@localhost:5432/user_name -c 'select current_date'

$ psql -Atx "host=localhost port=5432 dbname=user_name user=user_name" -c 'select current_date' 
```


[reference](https://tapoueh.org/blog/2019/09/postgres-connection-strings-and-psql/)


# Integration with Neovim

Plugins used are: 

- [vim-dadbod](https://github.com/tpope/vim-dadbod)
- [vim-dadbod-ui](https://github.com/kristijanhusak/vim-dadbod-ui)
- [vim-dadbod-completion](https://github.com/kristijanhusak/vim-dadbod-completion)


## Using just vim-dadbod

Besides using the connection string you can simply to this instead: 

```
:DB postgresql database_name < query_file.sql
```


