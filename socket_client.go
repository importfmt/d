package main
import (
	"fmt"
	"net"
	"time"
)

func main() {
	conn, err := net.Dial("tcp", ":8888")
	if err != nil {
		fmt.Println("net.Dial err:", err)
		return
	}
	defer conn.Close()
	fmt.Println("connection is creat successful.")

	for {
		cnt, err := conn.Write([]byte("hello"))
		if err != nil {
			fmt.Println("conn.Write err:", err)
			return
		}
		fmt.Println("client sent data count is:", cnt)

		buf := make([]byte, 1024)
		cnt, err = conn.Read(buf)
		if err != nil {
			fmt.Println("conn.Read err:", err)
			return
		}
		fmt.Println("receive data count is:", cnt, ", and data is:", string(buf[:cnt]))

		time.Sleep(2 * time.Second)
	}

}
