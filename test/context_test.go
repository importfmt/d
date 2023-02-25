package main

import (
	"fmt"
	"testing"
	"context"
	"time"
)

// The provided key myst be comparable and should not be of type string or any other built-in type to avoid collisions between packages using context.
type contextKey string

func TestContext(t *testing.T) {
	ctx := context.Background()
	// ctx := context.TODO()

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
