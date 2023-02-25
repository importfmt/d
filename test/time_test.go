package test

import (
	"fmt"
	"testing"
	"time"
)

func TestTime(t *testing.T) {
	now := time.Now()
	year := now.Year()
	month := now.Month()
	day := now.Day()
	hour := now.Hour()
	minute := now.Minute()
	second := now.Second()
	fmt.Printf("%d-%02d-%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second)
}

func TestTimeUnix(t *testing.T) {
	fmt.Printf("%v\n", time.Now().Unix())
}

func TestTimeUnixMilli(t *testing.T) {
	fmt.Printf("%v\n", time.Now().UnixMilli())
	fmt.Printf("%v\n", time.UnixMilli(time.Now().UnixMilli()))
}

func TestParse(t *testing.T) {
	now := time.Now()
	time, err := time.Parse("2006-01-02 15:04:05", now.Format("2006-01-02 15:04:05")); if err != nil {
		panic(err)
	}

	fmt.Printf("%v\n", time)
}

func TestLocationParse(t *testing.T) {
	loc, err := time.LoadLocation("Asia/Shanghai"); if err != nil {
		panic(err)
	}
	now := time.Now()

	timeObj, err := time.ParseInLocation("2006-01-02 15:04:05", now.Format("2006-01-02 15:04:05"), loc); if err != nil {
		panic(err)
	}

	fmt.Printf("%v\n", timeObj)
}

func TestTimeFormat(t *testing.T) {
	now := time.Now()

	fmt.Printf("%s\n", now.Format("2006-01-02 15:04:05"))
}

func TestDuration(t *testing.T) {
	now := time.Now()
	add := now.Add(5 * time.Minute)

	fmt.Printf("%v\n", add)

	sub := now.Sub(add)
	fmt.Printf("%v\n", sub)
}

func TestCompare(t *testing.T) {
	now1 := time.Now()
	now2 := time.Now()

	fmt.Printf("%v\n", now1.Equal(now2))

	add := now1.Add(1 * time.Minute)

	fmt.Printf("%v\n", now1.Before(add))
	fmt.Printf("%v\n", add.After(now1))

}


func TestTicker(t * testing.T) {

	time.Sleep(10)
	// time.AfterFunc(5 * time.Second), func() {
	// 	fmt.Printf("%s\n", "after 5 seconds.")
	// })

	tick := time.Tick(5 * time.Second)
	for t1 := range tick {
		fmt.Printf("%v\n", t1)
	}

}
