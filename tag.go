package main

import "fmt"
import "reflect"

type UserInfo struct {
	Name string `testtag:"testtest" abc:"abcabc"`
}

func printTag(ptr interface{}) {
	reType := reflect.TypeOf(ptr)
	if reType.Kind() != reflect.Ptr || reType.Elem().Kind() != reflect.Struct{
		panic("parameter is not pointer or struct.")
	}

	v := reflect.ValueOf(ptr).Elem()
	fmt.Printf("ptr Elem(): %v\n", v)

	for i := 0; i < v.NumField(); i++ {
		field := v.Type().Field(i)
		tag := field.Tag
		fmt.Printf("tag: %v\n", tag)
		labelTag := tag.Get("testtag")
		fmt.Println(labelTag)
		labelTag = tag.Get("abc")
		fmt.Println(labelTag)
	}
}

