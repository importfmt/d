package main

import "fmt"

func insertSort() {
	arr := []int{9, 4, 1, 2, 4, 5, 2, 1, 7}

	for i := 1; i < len(arr); i++ {
		for j := i; j > 0 && arr[j] < arr[j-1]; j-- {
			arr[j], arr[j-1] = arr[j-1], arr[j]
		}
	}

	fmt.Printf("sorted arr: %v\n", arr)
}