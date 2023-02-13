package main

import (
	"strings"
)

func LengthOfLongestSubstring(s string) int {
	start := 0
	end := 0

	for i := 0 ; i < len(s); i++ {
		ind := strings.Index(s[start:i], string(s[i]))
		if ind == -1 && (i + 1) > end {
			end = i + 1
		} else {
			start += ind + 1
			end += ind + 1
		}
		// fmt.Printf("start: %d, end: %d, i: %d\n", start, end ,i)
	}
	return end - start
}

