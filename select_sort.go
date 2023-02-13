package main

import "fmt"

func selectSort() {
	arr := []int{9, 2, 4, 1, 4, 6, 7, 2, 3}

	for i := 0; i < len(arr)-1; i++ {
		min := i
		for j := i+1; j < len(arr); j++ {
			if arr[min] > arr[j] {
				min = j
			}
		}

		if min != i {
			arr[min], arr[i] = arr[i], arr[min]
		}
	}

	fmt.Printf("sorted arr: %v\n", arr)
}