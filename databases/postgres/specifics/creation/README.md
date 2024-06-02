# Database / Schema Creation

- Create schema: `CREATE SCHEMA IF NOT EXISTS schema_name AUTHORIZATION user_name;`
- Create table: `CREATE TABLE IF NOT EXISTS db_name.table_name (var_name var_type);`
- [Create a copy of a database:](http://stackoverflow.com/questions/876522/ddg#876565) `CREATE DATABASE newdb WITH TEMPLATE originaldb OWNER dbuser;`
- Rename database: `ALTER DATABASE old_name RENAME TO new_name;`
