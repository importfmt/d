package main

import "fmt"

func subSets() {
	arr := []int{1, 2, 3}
	ans := [][]int{}

	for mask := 0; mask < 1<<len(arr); mask++ {
		set := make([]int, 0, 0)

		for k, v := range arr {
			if mask>>k&1 > 0 {
				set = append(set, v)
			}
		}
		ans = append(ans, set)
	}

	fmt.Printf("ans: %v\n", ans)
}