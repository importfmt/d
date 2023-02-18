package main

import (
	"fmt"
	"bytes"
	"testing"
)

func TestToUpper(t *testing.T) {
	b := []byte("hello")
	u := bytes.ToUpper(b)
	fmt.Printf("%s: %s\n", b, u)
}

func TestToLower(t *testing.T) {
	b := []byte("HELLO")
	u := bytes.ToLower(b)
	fmt.Printf("%s: %s\n", b, u)
}

func TestToTitle(t *testing.T) {
	var b = []byte("seafood")
	bTitle := bytes.ToTitle(b)

	fmt.Printf("%s\n", bTitle)
}

func TestBytesCompare(t * testing.T) {
	c := bytes.Compare([]byte("hello"), []byte("hello"))

	if c == 0 {
		fmt.Printf("%s\n", "equal")
	} else if c == -1 {
		fmt.Printf("%s\n", "less")
	} else {
		fmt.Printf("%s\n", "bigger")
	}

}

func TestEqual(t * testing.T) {
	c := bytes.Equal([]byte("hello"), []byte("hello"))

	fmt.Printf("%v\n", c)
}

func TestEqualFold(t *testing.T) {
	c := bytes.EqualFold([]byte("HELLO"), []byte("hello"))

	fmt.Printf("%v\n", c)
}


