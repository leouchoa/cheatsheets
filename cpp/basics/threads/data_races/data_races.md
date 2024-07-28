# Data Races

Suppose you have two threads trying to update the same data, maybe through a
pointer, and sometimes it outputs 1 and other times 2. They're racing to
get it: data race.

Prevention mechanisms:

1. Avoid pointers and pass values, if possible.
2. Make deep copies (usually overriding copy operators)
3. Use unique smart pointers.
4. Mutexes/locks.
