pub fn print_with_context() {
    println!("Calling from nested module!");
    super::print_number(); // `super` calls a function from parent module
}

pub fn print_custom_message(msg: &str) {
    println!("nested received: '{}'", msg);
    super::print_number();
}
