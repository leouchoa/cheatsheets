# Common/Useful Patterns

## 1. Fan-Out / Fan-In

- **Fan-Out**: Launch multiple goroutines to process jobs in parallel.
- **Fan-In**: Merge results from multiple goroutines into a single channel.

This pattern is useful for parallel processing and increasing throughput.

```go
func worker(id int, jobs <-chan int, results chan<- int) {
    for j := range jobs {
        results <- j * 2 // simulate work
    }
}
```

## 2. Using close() to Signal Completion

- Use close(ch) to tell receivers there will be no more data.
- Receivers use for v := range ch to read until closed.

```go
go func() {
    for i := 0; i < 5; i++ {
        ch <- i
    }
    close(ch)
}()

```

## 3. Result Collection via Channels

A goroutine can send a result to a channel, and another goroutine or the
main function can receive it.

```go
func compute(x int, ch chan<- int) {
    ch <- x * x
}
```

## 4. Timeouts with `select` and `time.After`

Useful to avoid deadlocks or long waits.

```go
select {
case res := <-ch:
    fmt.Println("Got:", res)
case <-time.After(2 * time.Second):
    fmt.Println("Timeout!")
}
```

## 5. Cancellation with a Done Channel

Using a done channel to signal goroutines to exit early helps in cleaning
long-running or background goroutines when no longer needed.

```go
done := make(chan struct{})
go func() {
    for {
        select {
        case <-done:
            return // exit goroutine
        default:
            // continue doing work
        }
    }
}()
```

## 6. Pipeline Pattern

Chain goroutines where each stage passes data to the next via channels.

```go
// stage 1
nums := make(chan int)
go func() {
    for i := 1; i <= 5; i++ {
        nums <- i
    }
    close(nums)
}()

// stage 2
squares := make(chan int)
go func() {
    for n := range nums {
        squares <- n * n
    }
    close(squares)
}()
```
