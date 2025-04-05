# General Reminders

- `fmt.Errorf` VS `errors.New`:
  - The later won't allow you to format the string, while the first allows
    format with dynamic injection of values.
  - [reference](https://siongui.github.io/2018/10/20/go-create-error-using-fmt.Errorf-or-errors.New/)

- Generics is [not that complicated](https://go.dev/doc/tutorial/generics).
