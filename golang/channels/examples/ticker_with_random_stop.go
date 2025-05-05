package main

import (
	"fmt"
	"math/rand"
	"time"
)

func randomStop() bool {

	randomBool := rand.Intn(2) == 1

	return randomBool

}

func ticker(stopChan chan bool) {
	i := 0
	for {
		stopSignal := randomStop()
		if stopSignal {
			fmt.Println("Stop signal! Stopping here...")
			stopChan <- true
			return
		}
		fmt.Println(i)
		i++
		time.Sleep(time.Second)
	}
}

func main() {

	stopChan := make(chan bool)
	go ticker(stopChan)

	<-stopChan
	fmt.Println("Got stop signal, stopping here.")

}
