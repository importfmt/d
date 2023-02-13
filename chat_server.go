package main

import (
	"fmt"
	"net"
	"strings"
	"sync"
)

type User struct {
	id   string
	name string
	msg  chan string
}

var users = make(map[string]*User)
var message = make(chan string, 10)
var mux sync.RWMutex

func main() {
	listener, err := net.Listen("tcp", ":8888")
	if err != nil {
		fmt.Println("net.Listen err:", err)
		return
	}
	defer listener.Close()

	go broadcast()

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("listener.Accept err:", err)
			return
		}

		go handler(conn)
	}

}

func handler(conn net.Conn) {
	clientAddr := conn.RemoteAddr().String()

	u := User{
		id:   clientAddr,
		name: clientAddr,
		msg:  make(chan string, 10),
	}

	mux.Lock()
	users[u.id] = &u
	mux.Unlock()
	message <- fmt.Sprintf("[%s:%s]:login.\n", u.id, u.name)

	go client2message(conn, &u)
	go msg2client(conn, &u)

}

func msg2client(conn net.Conn, u *User) {
	for {
		data := <-u.msg
		_, err := conn.Write([]byte(data)); if err != nil {
			fmt.Println("conn.Write err:", err)
			return
		}
	}
}

func client2message(conn net.Conn, u *User) {
	for {
		data := make([]byte, 1024)
		cnt, err := conn.Read(data)
		if cnt == 0 || string(data[:cnt - 1]) == "/quit" {
			quit(conn, u)
			return
		}
		if err != nil {
			fmt.Println("conn.Read err:", err)
			return
		}
		if string(data[:cnt - 1]) == "/who" {
			who(conn)
			continue
		}
		if string(data[:7]) == "/rename" {
			newName := strings.Split(string(data[:cnt - 1]), " ")[1]
			rename(conn, u, newName)
			continue
		}
		message <- fmt.Sprintf("[%s:%s]:%s\n", u.id, u.name, string(data[:cnt - 1]))
	}
}

func quit(conn net.Conn, u *User) {
	message <- fmt.Sprintf("[%s:%s]:logout.\n", u.id, u.name)
	mux.Lock()
	delete(users, u.id)
	mux.Unlock()
	conn.Close()
}

func who(conn net.Conn) {
	mux.Lock()
	for _, v := range users {
		r := fmt.Sprintf("[%s:%s]\n", v.id, v.name)
		_, err := conn.Write([]byte(r)); if err != nil {
			fmt.Println("conn.Write err:", err)
			return
		}
	}
	mux.Unlock()
}

func rename(conn net.Conn, u *User, newName string) {
	mux.Lock()
	users[u.id].name = newName
	mux.Unlock()
	_, err := conn.Write([]byte(fmt.Sprintf("[%s:%s]:change the name to %s.\n", u.id, u.name, newName)))
	if err != nil {
		fmt.Println("conn.Write err:", err)
		return
	}
}

func broadcast() {
	for {
		m := <-message
		fmt.Print(m)
		mux.Lock()
		for _, user := range users {
			user.msg <- m
		}
		mux.Unlock()
	}
}


