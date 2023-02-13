package main

import (
	"fmt"
)
type ss struct {
	Age int
}

func test() {
	s := new(ss)

	defer s.aa().aa()

	defer fmt.Printf("%s\n", "hhhhhhh")

}

func (s *ss) aa() *ss {
	fmt.Printf("%d\n", s.Age)
	return s
}

