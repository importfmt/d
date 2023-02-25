package test

import (
	"fmt"
	"testing"
	"context"
	"time"
)

// The provided key myst be comparable and should not be of type string or any other built-in type to avoid collisions between packages using context.
type contextKey string

func TestWithValue(t *testing.T) {
	// ctx := context.Background()
	ctx := context.TODO()

	ctxKey := contextKey("test")
	ctx = context.WithValue(ctx, ctxKey, "test val")

	go func() {
		if value := ctx.Value(contextKey("test")); value != nil {
			fmt.Printf("value is %v\n", value)
		} else {
			fmt.Printf("no value\n")
		}
	}()

	time.Sleep(time.Second * 2)
}

func TestWithCancel(t *testing.T) {
	ctx, cancel := context.WithCancel(context.Background())

	go func(cancel context.CancelFunc) {
		time.Sleep(time.Second*2)
		cancel()
	}(cancel)

	select {
	case <-ctx.Done():
		fmt.Printf("%s\n", "use cancel function.")
	}

}

func TestWithTimeout(t *testing.T) {
	for i := 0; i < 10; i++ {
		ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
		defer cancel()

		done := make(chan struct{})

		go func(done chan struct{}, sleepTime int) {
			time.Sleep(time.Duration(sleepTime) * time.Second)
			done <- struct{}{}
		}(done, i)

		go func(ctx context.Context, done chan struct{}) {
			select {
			case <-ctx.Done():
				fmt.Printf("ctx timeout\n")
			case <-done:
				fmt.Printf("work done\n")
			}
		}(ctx, done)
	}

	time.Sleep(3*time.Second)

}

func TestWithDeadline(t *testing.T) {
	deadline := time.Now().Add(5 * time.Second)
	ctx, cancel := context.WithDeadline(context.Background(), deadline)
	defer cancel()

	done := make(chan struct{})

	go func(done chan struct{}) {
		// do something
		time.Sleep(4*time.Second)
		done <- struct{}{}
	}(done)

	select {
	case <-ctx.Done():
		fmt.Printf("deadline\n")
	case <-done:
		fmt.Printf("work done\n")
	}


}
