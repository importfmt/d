package main


func reverseString(arr []byte) {
	mid := len(arr) / 2

	for i := 0; i < mid; i++ {
		arr[i], arr[len(arr)-i-1] = arr[len(arr)-i-1], arr[i]
	}
}