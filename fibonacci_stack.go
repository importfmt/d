package main

import (
	"container/list"
	"fmt"
)

var (
	stack *list.List
)


func fibonacciWithStack(n int) int {
	if n == 1 || n == 2 {
		return n - 1
	}

	stack.PushBack(0)
	stack.PushBack(1)

	for i := 2; i < n; i++ {
		a := stack.Back()
		stack.Remove(a)
		b := stack.Back()
		stack.Remove(b)

		stack.PushBack(a.Value.(int))
		stack.PushBack(a.Value.(int) + b.Value.(int))
	}
	a := stack.Back()
	result := stack.Remove(a)
	return result.(int)
}

func main() {
	stack = list.New()

	fibResult := fibonacciWithStack(2000)
	fmt.Printf("fibonacci result: %d\n", fibResult)
}
