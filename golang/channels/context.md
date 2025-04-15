# Context

You can think of it like a time window for a function to do
work.

```go
func main() {
 ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
 defer cancel()

 go doSomething(ctx)

 time.Sleep(3 * time.Second)
 fmt.Println("Done")
}

func doSomething(ctx context.Context) {
 select {
 case <-time.After(5 * time.Second):
  fmt.Println("Finished work")
 case <-ctx.Done():
  fmt.Println("Canceled:", ctx.Err())
 }
}

```
