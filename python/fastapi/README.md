# Working With Databases


1. Know that when using `sql-alchemy` ORM modeling, you're gonna start with some boilerplate code. To get started with connecting a database with `fastapi` you should remember to set:

  i. database session connection.
  ii. the ORM models.
  iii. pydantic models (`schemas`).
  iv. database relationships.
  v. [optional]: crud operation functions.


2. Remember that it's very helpful to use inheritance in pydantic classes for cleaner code. Example:

```
# base class to be inherited from
class UserBase(BaseModel):
    email: str

# inherits from UserBase and adds password
class UserCreate(UserBase):
    password: str

# the response doesn't need password, one more reason why inheriting is usefull here
class User(UserBase):
    id: int
    is_active: bool
    # here the `Item` class is another pydantic-based class inhereting from a BaseItem class
    items: List[Item] = []

    class Config:
        orm_mode = True
```

3. When setting up database tables, pay attention to correctly set the relationships:

```
class Table1(Base):
    __tablename__ = "table_1"

    id = Column(Integer, primary_key=True, index=True)

    items = relationship("Table2", back_populates="owner")


class Table2(Base):
    __tablename__ = "table_2"

    id = Column(Integer, primary_key=True, index=True)
    owner_id = Column(Integer, ForeignKey("table_1.id"))

    owner = relationship("Table1", back_populates="items")
```

## Setting Up `alembic` for Database Migrations

First of all, activate the virtual environment and run:

```
alembic init alembic_dir_name
```

This will create an `alembic.ini` file in the current directory and create a new directory called `alembic_dir_name`. Then to set up `alembic` in the most basic fashion, you'll need to:

1. Configure the `sqlalchemy.url` entry in `alembic.init` ( which usually is the database connection string) or configure it dinamically in `env.py` by referencing your `session` file.
2. Go into `env.py` and set `target_metadata` to your `declarative_base.metadata` being used. Usually this can found in `database.py`, so you just need to `from path_to.database import Base`.


### Running `alembic`

Most of the time you'll be only performing revisions (kinda like database commit for diffs) and downgrades/upgrades.

**IMPORTANT!**: consider deleting your database before running the first revision, otherwise your first migration file **will be empty** because there's no change for `alembic` do detect.

Now to make a revision, run: 

```
alembic revision --autogenerate -m "your revision message"
```

The `autogenerate` flag here looks for diffs in the `declarative_base` and adds them into the revision file (that by default lives in `alembic_dir/versions`).

Now to actually upgrade you database to the current base model, run `alembic upgrade head`. And in case you want to downgrade to revision before, run: `alembic downgrade -1`.
