package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"unsafe"
)

func main() {
	params := make(map[string]string)
	params["email"] = "2230001619@qq.com"
	params["passwd"] = "gygfob-Vixmed-nahsy0"
	bytesData, err := json.Marshal(params)
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	reader := bytes.NewBuffer(bytesData)
	url := "https://www.liulisusu.org/auth/login"
	req, err := http.NewRequest("POST", url, reader)
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	req.Header.Set("Content-Type", "application/json;charset=utf-8")
	req.Header.Set("Connection", "Keep-Alive")

	client := http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		fmt.Println(err.Error())
		return
	}
	defer resp.Body.Close()

	respBytes, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	str := (*string)(unsafe.Pointer(&respBytes))
	fmt.Println(*str)

	url = "https://www.liulisusu.org/user/checkin"
	req, err = http.NewRequest("POST", url, nil)
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	for _, c := range resp.Cookies() {
		req.AddCookie(c)
	}

	resp, err = client.Do(req)
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	respBytes, err = ioutil.ReadAll(resp.Body)
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	str = (*string)(unsafe.Pointer(&respBytes))
	fmt.Println(*str)
}
