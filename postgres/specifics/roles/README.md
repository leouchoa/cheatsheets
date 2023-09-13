# Psql Administration

Roles are used to represent user accounts in psql. To create an user with login access and password use:

```sql
CREATE ROLE leo 
LOGIN 
PASSWORD 'securePass1';
```

Then to login: `psql -U alice -W postgres`. But you can't do anything yet, first you gotta grant privileges:

```sql
GRANT ALL
ON ALL TABLES
IN SCHEMA "public"
TO leo;
```

You also can use group roles to make it easier to admin groups. Example:

1. create the role: `create role marketing_example_group noinherit;`.
2. grant the role privileges: `grant all on table_name to marketing_example_group;`
3. grant the group privileges to user: `grant marketing_example_group to leo;`
4. login: `psql -U leo -d dbname`

## Useful Commands

- Create role: `CREATE ROLE role_name;` or `CREATE ROLE role_name WITH option;`
- Create role that can create dbs: `CREATE ROLE dba CREATEDB LOGIN PASSWORD 'Abcd1234';`
- Create role with validity period: `CREATE ROLE dev_api WITH LOGIN PASSWORD 'securePass1' VALID UNTIL '2030-01-01';`
- Revoking privileges: `REVOKE privilege | ALL ON TABLE table_name |  ALL TABLES IN SCHEMA schema_name FROM role_name;`
- Granting group roles: `GRANT group_role to user_role;`
- Alter roles: [link](https://www.postgresqltutorial.com/postgresql-administration/postgresql-alter-role/)
- [Reset forgotten password](https://www.postgresqltutorial.com/postgresql-administration/postgresql-reset-password/)
- [Reset an user's password](https://www.postgresqltutorial.com/postgresql-administration/postgresql-change-password/)
