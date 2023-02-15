package main


import "github.com/streadway/amqp"

func main() {
	sendMessage()
}

func sendMessage() {
	conn, _ := amqp.Dial("amqp://root:root@172.25.190.240:5672/")
	defer conn.Close()

	ch, _ := conn.Channel()
	defer ch.Close()

	_ = ch.ExchangeDeclare("test.direct", "direct", true, false, false, false, nil, )

	body := "hello world"
	_ = ch.Publish(
		"test.direct",
		"rk",
		false,
		false,
		amqp.Publishing {
			ContentType: "text/plain",
			Body: []byte(body),
		},
	)

}
