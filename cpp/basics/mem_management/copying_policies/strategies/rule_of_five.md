# The Rule of Five

States that if you have to write one of the functions listed below then you
should consider implementing all of them with a proper resource management
policy in place. If you forget to implement one or more, the compiler will
usually generate the missing ones (**without a warning**) but the default versions
might not be suitable for the purpose you have in mind. The five functions are:

1. The destructor: Responsible for freeing the resource once the object it
belongs to goes out of scope.

2. The assignment operator: The default assignment operation performs a
member-wise shallow copy, which does not copy the content behind the resource
handle. If a deep copy is needed, it has be implemented by the programmer.

3. The copy constructor: As with the assignment operator, the default copy
constructor performs a shallow copy of the data members. If something else is
needed, the programmer has to implement it accordingly.

4. The move constructor: Because copying objects can be an expensive operation
which involves creating, copying and destroying temporary objects, `rvalue`
references are used to bind to an `rvalue`. Using this mechanism, the move
constructor transfers the ownership of a resource from a (temporary) `rvalue`
object to a permanent `lvalue` object.

5. The move assignment operator: With this operator, ownership of a resource
can be transferred from one object to another. The internal behavior is very
similar to the move constructor.
