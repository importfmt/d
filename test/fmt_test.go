package test

import (
	"fmt"
	"testing"
	"os"
	"strings"
)

func TestSprintf(t *testing.T) {
	port := 8888
	ip := "127.0.0.1"

	addr := fmt.Sprintf("%s:%d", ip, port)
	fmt.Printf("%s\n", addr)
}


func TestFprintf(t *testing.T) {
	fmt.Fprintf(os.Stdout, "%s\n", "hello")
}

func TestFscan(t *testing.T) {
	reader := strings.NewReader("hello")
	fmt.Printf("%s\n", "Please enter something:")
	var input string

	fmt.Fscan(reader, &input)
	fmt.Printf("%s\n", input)
}

func TestFscanf(t *testing.T) {
	reader := strings.NewReader("world")
	fmt.Printf("%s\n", "Please enter something:")
	var input string

	fmt.Fscanf(reader, "%s", &input)
	fmt.Printf("%s\n", input)
}
