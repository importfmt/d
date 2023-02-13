package main

func quickSort(arr []int) []int {
	if len(arr) <= 1 {
		return arr
	}

	low := make([]int, 0, 0)
	mid := make([]int, 0, 0)
	hig := make([]int, 0, 0)

	flag := arr[0]
	mid = append(mid, flag)


	for i := 1; i < len(arr); i++ {
		if arr[i] < flag {
			low = append(low, arr[i])
		} else if arr[i] > flag {
			hig = append(hig, arr[i])
		} else {
			mid = append(mid, arr[i])
		}
	}

	low, hig = quickSort(low), quickSort(hig)
	return append(append(low, mid...), hig...)
}