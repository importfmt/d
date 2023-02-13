package main

import (
	"fmt"
	"net/http"
	"io"
)

func main() {

	http.HandleFunc("/ping", func(writer http.ResponseWriter, request *http.Request) {
		io.WriteString(writer, "pong")
	})

	err := http.ListenAndServe(":8888", nil); if err != nil {
		fmt.Println("http.ListenAndServe err:", err)
		return
	}
}
