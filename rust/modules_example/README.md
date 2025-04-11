# Nested Modules Example

Simple example of how to split your `main.rs` into structured files and folders,
when you need to.

Note:

- `print_number()` is private (not pub) but still accessible to nested via `super::`.

| Scenario                           | Without `use`                            | With `use`                              |
|------------------------------------|------------------------------------------|-----------------------------------------|
| Calling a function from a module  | `utils::my_fns::say_hello_with_msg()`     | `say_hello_with_msg()`                  |
| Calling a function from a deeply nested module | `utils::nested::print_custom_message()` | `print_custom_message()`                |
| Accessing something deeply nested | `utils::extra::helper::do_extra()`       | `utils::extra::helper::do_extra()`      |
