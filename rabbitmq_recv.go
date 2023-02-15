package main

import "github.com/streadway/amqp"
import "fmt"

func main() {
	recvMessage()
}

func recvMessage() {
	conn, _ := amqp.Dial("amqp://root:root@172.25.190.240:5672/")
	defer conn.Close()

	ch, _ := conn.Channel()
	defer ch.Close()

	exchange := "test.direct"
	routingKey := "rk"
	queueName := "test.queue"

	_ = ch.ExchangeDeclare(exchange, "direct", true, false, false, false, nil)
	q, _ := ch.QueueDeclare(queueName, false, false, true, false, nil)
	_ = ch.QueueBind(q.Name, routingKey, exchange, false, nil)

	msgs, _ := ch.Consume(q.Name, "", true, false, false, false, nil)

	waitCh := make(chan bool)

	go func() {
		for d := range msgs {
			fmt.Printf("msg: %s\n", d.Body)
		}
	}()

	<-waitCh
}
