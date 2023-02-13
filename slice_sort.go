package main

import (
)

type mySlice []int32
type mySlice1 []int64

func (m mySlice) Len() int {
	return len(m)
}

func (m mySlice) Less(i, j int) bool {
	return m[i] > m[j]
}

func (m mySlice) Swap (i, j int) {
	m[i], m[j] = m[j], m[i]
}