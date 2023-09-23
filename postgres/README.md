# Postgres

- list databases: `\l`
- list users: `\du` or `\du+`
- list all schemas: `\dn`
- list all views: `\dv`
- list all stored procedures and fns: `\df`
- describe a table `\d tablename`
- switch to the database that you want to work with: `\c database`
- List all postgres tables in one particular schema: `\dt schemaname.*`
- Connection information: (current user, port, dtb) `\conninfo`)
- [good cheatsheet](https://www.postgresqltutorial.com/postgresql-cheat-sheet/)

## Connection Strings

Connecting to localhost:
To connect to postgres the most basic Way is with the `psql` command:
`psql -U user_name -W postgres`. Note that the `postgres` is the default
database name, otherwise it will assume that the user_name is the db name.
However you can also login with connection strings:

```bash
psql -Atx -U user_name -d user_name -h localhost -p 5432 -c 'select current_date'

psql -Atx postgresql://user_name@localhost:5432/user_name -c 'select current_date'

psql -Atx "host=localhost port=5432 dbname=user_name user=user_name" -c 'select current_date' 
```

[reference](https://tapoueh.org/blog/2019/09/postgres-connection-strings-and-psql/)

## Integration with Neovim

Plugins used are:

- [vim-dadbod](https://github.com/tpope/vim-dadbod)
- [vim-dadbod-ui](https://github.com/kristijanhusak/vim-dadbod-ui)
- [vim-dadbod-completion](https://github.com/kristijanhusak/vim-dadbod-completion)

## Using just vim-dadbod

Besides using the connection string you can simply to this instead:

```
:DB postgresql database_name < query_file.sql
```

Or you can use the `\e` command from inside psql to open you editor and after
you type the command in the editor, save it, and close the editor, psql will
execute the command and return the result.

## CTEs vs Temporary Tables vs Subqueries

[CTEs](https://www.postgresqltutorial.com/postgresql-tutorial/postgresql-cte/) is:

> A temporary result set which you can reference within another SQL statement including SELECT, INSERT, UPDATE or DELETE

Usually CTES are used to improve readability in the context of long/complex joins and [subqueries](https://www.postgresqltutorial.com/postgresql-tutorial/postgresql-subquery/), which can make code more complicated than it needs to be. CTEs, temp tables and subqueries all ahieve the same purpose of temporarily storing a query result for subsequent use. Some general tips:

- Which to use depends on code, just aim for readability;
- It may often happen that their costs are nearly the same, as shown in [this post](https://www.startdataengineering.com/post/using-common-table-expression-in-redshift/)

## Query Timing

```sql
database=\timing
database=select count(*) from film;

--> results here <--

database=\timing
```
