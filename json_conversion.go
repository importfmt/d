package main

import (
	"encoding/json"
	"fmt"
)

type Student struct {
	Id     int    `json:"id"`
	Name   string `json:"name,omitempty"` // ignore, if field is empty.
	Age    int    `json:"age,string"`
	gender string `json:"-"`
}

func main() {
	jack := Student{
		Id:     1,
		Name:   "jack",
		Age:    20,
		gender: "male", // if var is private, can't marshal or unmarshal.
	}

	encodeInfo, err := json.Marshal(jack)
	if err != nil {
		fmt.Println("json.Marshal err:", err)
		return
	}
	fmt.Println(string(encodeInfo))

	// []byte 2 struct
	var jackNew Student
	if err := json.Unmarshal(encodeInfo, &jackNew); err != nil {
		fmt.Println("json.Unmarshal err:", err)
		return
	}
	fmt.Println(jackNew)

	// []byte 2 map
	studentMap := make(map[string]interface{})
	if err := json.Unmarshal(encodeInfo, &studentMap); err != nil {
		fmt.Println("json.Unmarshal err:", err)
		return
	}

	for k, v := range studentMap {
		fmt.Println("k:", k, "v:", v)
	}

}
