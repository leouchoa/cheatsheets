# Quick Tips

## Modules

- Remember to add the `pub` keyword for functions that you want to export.

| Term             | Role in Rust Modules                                 |
|------------------|------------------------------------------------------|
| `mod.rs`         | Acts like a router or entry point for a module folder |
| `mod xyz;`       | Declares submodules to include                        |
| `pub mod xyz;`   | Declares and exposes submodules                       |
| `super::`        | Lets you access parent module items                   |

Example:

```text
src/
├── main.rs
└── utils/
    ├── mod.rs <- router, declare your function imports here
    ├── my_fns.rs
    └── extra/
        ├── mod.rs
        └── helper.rs
```
