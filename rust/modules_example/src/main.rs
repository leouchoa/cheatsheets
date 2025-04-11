mod utils;
use utils::my_fns::say_hello_with_msg; // brings fn into scope

fn main() {
    utils::nested::print_with_context();
    utils::extra::helper::do_extra();

    say_hello_with_msg("Passing data across modules!");
}
