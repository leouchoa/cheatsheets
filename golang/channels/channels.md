# Channels

## To Keep in Mind

Channels are by default memory addresses (reference types), so when you pass them
to a function/goroutine you're not copying the channel, just the reference.
That also means that the channel itself is the same across all goroutines that
share it.

## 1. Do not communicate by sharing memory; share memory by communicating

- Instead of using locks and mutexes to protect shared memory, use channels to
safely pass data between goroutines.

- Channels are designed to synchronize and share state between goroutines cleanly.

## 2. Channels orchestrate; goroutines execute

- Goroutines are lightweight threads — you can run many of them.

- Channels are the coordination mechanism: they tell goroutines when and
what to do.

## 3. The sender should close the channel, not the receiver

- This helps keep the control flow predictable.

- A closed channel tells receivers "this stream is done."

## 4. Don’t leak goroutines

- Make sure goroutines can finish and are not stuck waiting on a channel that
will never send/receive.

- Use cancellation (`context.Context` or `done` channels) to clean up long-running
goroutines.

## 5. Use buffered channels for decoupling

- Buffered channels let the sender continue for a bit without blocking.

- They are great for smoothing out bursts or handling variable speeds in pipelines.

## 6. Use select to multiplex

- `select` lets you wait on multiple channel operations.

- It’s the Go way to implement timeouts, cancellation, or handling multiple
input streams.

```go
select {
case msg := <-ch:
    fmt.Println("Got message:", msg)
case <-time.After(time.Second):
    fmt.Println("Timed out")
}

```

## On When To Close Channels

### When You *Should* Close Channels

- When the **receiver needs to know** that no more values will be sent.
- When using `for range` to receive from a channel.
- When implementing **pipelines**, **fan-out**, or **fan-in** patterns.
- When **you are the sender**, and no more data will be sent.

### When *Not* to Close Channels

- Don’t close a channel **just to free resources** (Go handles that).
- Don’t close a channel **from the receiver’s side**.
- Don’t close **shared or externally owned** channels unless designed that way.
- Don’t close if **receivers don’t care** about completion.
