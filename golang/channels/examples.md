# Practical Examples

## Simple Directional channel

```go
package main

import (
 "fmt"
)

// Send-only channel as parameter
func sendData(ch chan<- int) {
 for i := 1; i <= 3; i++ {
  ch <- i
 }
 close(ch)
}

// Receive-only channel as parameter
func receiveData(ch <-chan int) {
 for v := range ch {
  fmt.Println("Received:", v)
 }
}

func main() {
 ch := make(chan int)
 go sendData(ch)
 receiveData(ch)
}

```

## Collecting Results from Multiple Goroutines

```go
package main

import (
 "fmt"
)

func square(x int, resultChan chan<- int) {
 resultChan <- x * x
}

func main() {
 nums := []int{2, 3, 4, 5}
 resultChan := make(chan int)

 for _, n := range nums {
  go square(n, resultChan)
 }

 for i := 0; i < len(nums); i++ {
  fmt.Println("Result:", <-resultChan)
 }
}
```

## Using `sync.WaitGroup` with Channels

Ensuring all results are sent before closing the channel

```go
package main

import (
 "fmt"
 "sync"
)

func square(x int, wg *sync.WaitGroup, resultChan chan<- int) {
 defer wg.Done()
 resultChan <- x * x
}

func main() {
 var wg sync.WaitGroup
 nums := []int{2, 3, 4, 5}
 resultChan := make(chan int, len(nums)) // Buffered to avoid blocking

 for _, n := range nums {
  wg.Add(1)
  go square(n, &wg, resultChan)
 }

 wg.Wait()
 close(resultChan)

 for res := range resultChan {
  fmt.Println("Result:", res)
 }
}
```

## Preserving Order of Results

```go
package main

import (
 "fmt"
)

func square(x int, resultChan chan<- int, index int, orderedResults []int) {
 resultChan <- x * x
}

func main() {
 nums := []int{2, 3, 4, 5}
 results := make([]int, len(nums))
 resultChan := make(chan struct {
  index int
  value int
 })

 for i, n := range nums {
  go func(i, n int) {
   resultChan <- struct {
    index int
    value int
   }{i, n * n}
  }(i, n)
 }

 for i := 0; i < len(nums); i++ {
  res := <-resultChan
  results[res.index] = res.value
 }

 fmt.Println("Ordered results:", results)
}
```
