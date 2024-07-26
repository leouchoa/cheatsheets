# Rule of Three

States that if a class needs to have an overloaded copy constructor, copy
assignment operator and destructor, then it must also implement the other two
as well to ensure that memory is managed consistently.

Note that the class `SharedCopy` does not implement the assignment operator. This
is a violation of the Rule of Three and thus, if we were to use something like
`destination3 = source` instead of `SharedCopy destination3(source)`, the counter
variable would not be properly decremented.
