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
