package main

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
	"time"

	_ "github.com/go-sql-driver/mysql"
)


type Message struct {
	Code string `json:"code"`
	Guid string `json:"guid`
}

type Row struct {
	Code string `db:"code"`
	Guid string `db:"guid"`
	Date string `db:"date`
	Who string `db:"who`
}

func initDB() *sql.DB {
	db, err := sql.Open("mysql", "root:01011010@tcp(127.0.0.1:3306)/haimas?charset=utf8")
	if err != nil {
		fmt.Println("[ERROR] sql.Open() err: err: ", err)
		return nil
	}
	return db
}

func authorize(w http.ResponseWriter, r *http.Request) {
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


	fmt.Printf("%v: code: %s\n", time.Now(),  msg.Code)
	fmt.Printf("%v: guid: %s\n", time.Now(),  msg.Guid)

	db := initDB()
	defer db.Close()

	rows, err := db.Query("SELECT guid FROM auth WHERE code = ?", msg.Code)
	if err != nil {
		fmt.Println("[ERROR] db.Query() err: ", err)
		return
	}
	defer rows.Close()

	exist := false

	for rows.Next() {
		var guid string
		rows.Scan(&guid)
		exist = true

		if guid == "" {
			_, err := db.Query("UPDATE auth SET guid = ? WHERE code = ?", msg.Guid, msg.Code)
			if err != nil {
				fmt.Println("[ERROR] db.Query() err: ", err)
				return
			}
			msg.Code = "ok"
			msg.Guid = ""
			fmt.Printf("[INFO] %s is bound to %s\n", msg.Code, msg.Guid)
		} else if guid == msg.Guid {
			msg.Code = "ok"
			msg.Guid = ""
		} else {
			msg.Code = "used"
			msg.Guid = ""
		}
	}

	if !exist {
		fmt.Printf("This : %s have not in database.\n", msg.Code)
		msg.Code = "ko"
		msg.Guid = ""
	}

	msgJson, err := json.Marshal(msg); if err != nil {
		fmt.Println("[ERROR] json.Marshal() err: ", err)
		return
	}

	fmt.Fprintf(w, string(msgJson))
}

func main() {

	http.HandleFunc("/ping", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "pong")
	})

	http.HandleFunc("/shutdown", func(w http.ResponseWriter, r *http.Request){
		os.Exit(0)
	})

	http.HandleFunc("/authorize", authorize)

	http.ListenAndServe("0.0.0.0:12356", nil)
}
