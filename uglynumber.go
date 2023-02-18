package main

// 2 3 5
// 1 2 3 4 5 6 8 9 10 12 

import "fmt"

func main() {
	fmt.Printf("%s: %v\n", "uglyNumber", uglyNumber(1000))
}

func uglyNumber(n int) []int {
	ans := make([]int, n, n)
	ans[0] = 1

	two := 2
	three := 3
	five := 5

	for i := 1; i < n; i++ {
		minNum := min(two, min(three, five))
		if minNum == two {
			two += 2
		} else if minNum == three {
			three += 3
		} else {
			five += 5
		}
		ans[i] = minNum
		increase(&two, ans[i], 2)
		increase(&three, ans[i], 3)
		increase(&five, ans[i], 5)
	}

	return ans
}

func min(a int,b int) int {
	if a > b {
		return b
	}
	return a
}

func increase(start *int, end int, step int) {
	for ; *start <= end; {
		*start += step
	}
}
