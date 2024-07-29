# Mutex

In order to avoid data races, we need to either forego accessing shared data
or use it in read-only access without mutating the data. Mutexes are a way
to establish a stable long-term communication channel that allows for both
sharing and mutation.

Ideally, we would like to have a communication protocol, something like a
voice communication over a radio channel, where the transmitter uses the
expression "over" to indicate the end of the transmission to the receiver.
By using such a protocol, sender and receiver can take turns in transmitting
their data. In C++, this concept of taking turns can be constructed by an
entity called a "mutex" - which stands for MUtual EXclusion.

A data race requires simultaneous access from two threads. If we can guarantee
that only a single thread at a time can access a particular memory location,
data races would not occur. In order for this to work, we would need to
establish a communication protocol. It is important to note that a mutex is
not the solution to the data race problem per se but merely an enabler for a
thread-safe communication protocol that has to be implemented and adhered to
by the programmer.

The diagram below illustrates the concept of using a mutex to manage access to
a shared variable by multiple threads.

```plaintext
          +-------------------+
          |  shared variable  |
          +-------------------+
                  ▲
                  |
                  | access
                  |
             +----------+
             |  mutex   |
             +----------+
              /     \
   under the lock   is blocked
            /         \
  +-----------+     +-----------+
  |  Thread 1 |     |  Thread 2 |
  +-----------+     +-----------+
```

In this diagram:

- The `mutex` controls access to the `shared variable`.
- `Thread 1` is under the lock, has access to the shared variable *and* "locks"
the mutex.
- `Thread 2` is blocked and cannot access the shared variable or acquire the
lock until `Thread 1` releases the lock. It's also temporarily suspended by
the system.

So assuming we have a piece of memory (e.g. a shared variable) that we want to
protect from simultaneous access, we can assign a mutex to be the guardian of
this particular memory. **Note that a mutex is bound to the memory it protects**.

Once the reading or writing operation of `Thread 1` is complete, it must "unlock"
the mutex so that `thread 2` can access the memory location. **Often, the code
which is executed "under the lock" is referred to as a "critical section"**. It
is important to also note that read-only access to the shared memory has to
lock the mutex to prevent a data race - which would happen when another thread,
who might be under the lock at that time, were to modify the data.

When several threads were to try to acquire and lock the mutex, only one of
them would be successful. All other threads would automatically be put on hold.

Once the thread who has succeeded in acquiring the lock had finished its job
and unlocked the mutex, a queued thread waiting for access would be woken up
and allowed to lock the mutex to proceed with his read / write operation. If
all threads were to follow this protocol, a data race would effectively be
avoided.
