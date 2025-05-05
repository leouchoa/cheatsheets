# Useful Rust Data Structures

Some good refs:

- Check out the [rust-guide website](https://rust-guide.com/). It has a very good
explanation of the `std::collections` library.

- In the [official docs](https://doc.rust-lang.org/std/collections/index.html#use-the-set-variant-of-any-of-these-maps-when)
there's a very good comparison for when to use the different data structures.

1. Arrays
2. Vectors
    - Growable array
3. [VecDeques](https://play.rust-lang.org/?version=stable&mode=debug&edition=2021&gist=14ff9880722e5b6eb6a862fc75fce663)
    - Double-ended queue with fast appends/pops on both ends
4. [HashMap](https://play.rust-lang.org/?version=stable&mode=debug&edition=2021&gist=2a13f87b4f31768bb293d03c115abfd2)
    - Key-value store
5. [Linked List](https://doc.rust-lang.org/std/collections/struct.LinkedList.html)
    - List with efficient inserts/removals in middle but slower indexing
6. Sequence
    - Immutable ordered collection indexed by position
7. [HashSet](https://play.rust-lang.org/?version=stable&mode=debug&edition=2021&gist=f0e27e0624ecfb2433ab404ff25e7b8d)
    - A collection that only stores unique elements
8. [BTreeSet official doc](https://doc.rust-lang.org/std/collections/struct.BTreeSet.html) and [rust-guide](https://rust-guide.com/en/documentation/collections/BTreeSet)
    - A balanced binary tree set.
    - It is a collection that maintains its elements in sorted order and ensures
    no duplicates.
    - This makes it a suitable choice for scenarios where sorted data and fast
    lookups are required.
    - Very elegant solution for shopping cart transactions.
9. [BinaryHeap](https://rust-guide.com/en/documentation/collections/BinaryHeap)
    - It's a priority queue: provides fast access and push/pop to the highest
    priority item in a list.
    - Particularly useful in programming when you need to frequently access the
    most important items in a collection.
    - The `BinaryHeap` in Rust is a max-heap by default, meaning it will always
    give you the largest item first. If you want a min-heap (where the smallest
    item has the highest priority), you can negate the values when inserting and
    removing.

## `BinaryHeap` Examples

### `BinaryHeap` max-heap Example

```rust
use std::collections::BinaryHeap;

fn main() {
    let mut priority_queue = BinaryHeap::new();

    // Insert items with their priorities
    priority_queue.push(3);
    priority_queue.push(1);
    priority_queue.push(4);
    priority_queue.push(2);

    // Remove items in order of priority
    while let Some(item) = priority_queue.pop() {
        println!("{}", item); // This will print: 4, 3, 2, 1
    }
}
```

### `BinaryHeap` min-heap Example

```rust
use std::collections::BinaryHeap;

fn main() {
    let mut min_heap = BinaryHeap::new();

    // Insert items as negative values to simulate a min-heap
    min_heap.push(-3); // Priority 3
    min_heap.push(-1); // Priority 1
    min_heap.push(-4); // Priority 4
    min_heap.push(-2); // Priority 2

    // Remove items in order of priority (smallest first)
    while let Some(item) = min_heap.pop() {
        println!("{}", -item); // Negate to get the original value
    }
}
```

## `BTreeSet` Example

The sorting in a `BTreeSet` is based on string ordering, not the order in which
you push the items.

```rust
use std::collections::BTreeSet;

fn main() {
    let mut fruit_set = BTreeSet::new();

    fruit_set.insert("Apple");
    fruit_set.insert("Banana");
    fruit_set.insert("Cherry");
    fruit_set.insert("Date");

    // Display the fruits in sorted order
    for fruit in &fruit_set {
        println!("{}", fruit);
    }
    // Apple
    // Banana
    // Cherry
    // Date

}
```

### Implementing `BTreeSet`s for Different Data Types

Easy using enums.

```rust
use std::collections::BTreeSet;

// Derived to allow comparison between the different types stored in the enum.
#[derive(Debug, PartialEq, PartialOrd, Eq, Ord)]
enum Number {
    Int(i32),
    Float(f64),
}

fn main() {
    let mut number_set = BTreeSet::new();

    number_set.insert(Number::Int(3));
    number_set.insert(Number::Float(2.5));
    number_set.insert(Number::Int(1));
    number_set.insert(Number::Float(4.0));

    for number in &number_set {
        match number {
            Number::Int(value) => println!("Integer: {}", value),
            Number::Float(value) => println!("Float: {}", value),
        }
    }
}
```
