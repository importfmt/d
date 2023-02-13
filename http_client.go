package main

import (
	"fmt"
	"net/http"
	"io/ioutil"
)

func main() {
	client := http.Client{}

	resp, err := client.Get("http://127.0.0.1:8888/ping"); if err != nil {
		fmt.Println("client.Get err:", err)
		return
	}

	contentType := resp.Header.Get("Content-Type")
	fmt.Println("content-type:", contentType)

	respBody, err := ioutil.ReadAll(resp.Body); if err != nil {
		fmt.Println("ioutil.ReadAll err:", err)
		return
	}
	fmt.Println(string(respBody))

}
