package main

import "fmt"

func main() {
	fibonacci := fib(5)
	fmt.Println(fibonacci)
}

func fib(n int) int {
	if n == 1 {
		return n
	}

	return n + fib(n-1)
}
