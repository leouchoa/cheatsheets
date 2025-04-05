# Generics

## Simple Generics Example

```go
package main

import "fmt"

type Number interface {
 int | int8 | int16 | int32 | int64 | uint | uint8 | uint16 | uint32 | uint64 | float32 | float64
}

func Generics[N Number](v ...N) N {
 var t N
 for _, v := range v {
  t = t + v
 }
 return t
}

func main() {
 fmt.Println("Results int: ", Generics(1, 2, 3, 4, 5))
 fmt.Println("Results float: ", Generics(1, 2, 3, 4, 5))
}
```
