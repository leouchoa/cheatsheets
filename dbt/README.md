# Dbt

## Troubleshoot

Careful with the `INTO` command in postgres. Idkw, but it's not allowed.
The workaround is to use CTEs instead. For example:

This query:

```sql
{{
  config(
    materialized='table'
  )
}}

select distinct category into tmp_category from raw.products
```

Can be converted to this:

```sql
{{
  config(
    materialized='table'
  )
}}

WITH tmp_category AS (
    SELECT * FROM raw.products
)
SELECT
    distinct category
FROM
    tmp_category

```
