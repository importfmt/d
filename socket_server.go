package main

import ( "fmt"
	"net"
	"strings"
)

func main() {
	ip := "127.0.0.1"
	port := 8888
	address := fmt.Sprintf("%s:%d", ip, port)

	listener, err := net.Listen("tcp", address)
	if err != nil {
		fmt.Println("net.Listen err:", err)
		return
	}
	fmt.Println("listening...")

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("listener.Accept err:", err)
			return
		}
		defer conn.Close()
		fmt.Println("connection is create successful.")

		go func(conn net.Conn) {
			for {
				buf := make([]byte, 1024)
				cnt, err := conn.Read(buf); if err != nil {
					fmt.Println("conn.Read err:", err)
					return
				}
				fmt.Println("buf length is:", cnt, ", and data is:", string(buf))

				result := strings.ToUpper(string(buf[:cnt]))
				_, err = conn.Write([]byte(result))
				if err != nil {
					fmt.Println("conn.Write err:", err)
					return
				}
			}
		}(conn)
	}
}
