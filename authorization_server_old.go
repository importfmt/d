package main

import (
	"fmt"
	"net/http"
	"encoding/json"
	"io/ioutil"
	"database/sql"
	"time"
	_ "github.com/go-sql-driver/mysql"
)


type Message struct {
	UUIDDIUU string `json: "UUIDDIUU"`
}

type row struct {
	UUIDDIUU string `db: "UUIDDIUU"`
}

func initDB() *sql.DB {
	db, err := sql.Open("mysql", "root:01011010@tcp(127.0.0.1:3306)/verify?charset=utf8")
	if err != nil {
		fmt.Println("[ERROR] sql.Open() err: err: ", err)
		return nil
	}
	return db
}

func verify(w http.ResponseWriter, r *http.Request) {
	defer r.Body.Close()

	var msg Message

	body, err := ioutil.ReadAll(r.Body); if err != nil {
		fmt.Println("[ERROR] ioutil.ReadAll() err: ", err)
		return
	}

	err = json.Unmarshal(body, &msg); if err != nil {
		fmt.Println("[ERROR] json.Unmarshal() err: ", err)
		return
	}


	fmt.Printf("%v: UUIDDIUU: %s\n", time.Now(),  msg.UUIDDIUU)

	db := initDB()
	defer db.Close()

	rows, err := db.Query("SELECT * FROM uuid WHERE UUIDDIUU = ?", msg.UUIDDIUU)
	if err != nil {
		fmt.Println("[ERROR] db.Query() err: ", err)
		return
	}
	defer rows.Close()

	exist := false

	for rows.Next() {
		exist = true
	}

	if exist {
		msg.UUIDDIUU = "ok" + msg.UUIDDIUU + "ko"
	} else {
		fmt.Printf("This UUID: %s have not in database.\n", msg.UUIDDIUU)
		msg.UUIDDIUU = "0k" + msg.UUIDDIUU + "k0"
	}

	msgJson, err := json.Marshal(msg); if err != nil {
		fmt.Println("[ERROR] json.Marshal() err: ", err)
		return
	}

	fmt.Fprintf(w, string(msgJson))
}

func main() {

	http.HandleFunc("/ping", func(w http.ResponseWriter, r *http.Request) {
		fmt.Println(r)
		fmt.Fprintf(w, "pong")
	})
	http.HandleFunc("/verify", verify)

	http.ListenAndServe("0.0.0.0:11111", nil)
}
