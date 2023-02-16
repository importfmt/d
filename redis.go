package main

import (
	"fmt"
	"context"
	"time"
	"github.com/redis/go-redis"
	"errors"
)

var rdb *redis.Client

func main() {
	// TLS connection.
	// rdb := redis.NewClient(&redis.Options{
	// 	TLSConfig: &tls.Config{
	// 		MinVersion: tls.VersionTLS12,
	// 	},
	// })

	// cluster connection.
	// rdb:= redis.NewClusterClient(&redis.ClusterOptions{
	// 	Addrs: []string{":1111", ":2222"},
	// })

	// failover connection
	// rdb := redis.NewFailoverClient(&redis.FailoverOptions{
	// 	MasterName: "master_name",
	// 	SentinelAddrs: []string{":1111", ":2222"},
	// })

	rdb = redis.NewClient(&redis.Options{
		Addr: "localhost:6379",
		Password: "000000",
		DB: 0,
	})

	ctx, cancel := context.WithTimeout(context.Background(), 500*time.Millisecond)
	defer cancel()

	// val, err := stringDemo(ctx, "s", "")
	// fmt.Printf("key: %s, val: %s, err: %v\n", "s", val, err)

	// zsetDemo(ctx)
	// scanDemo(ctx)
	// pipelineDemo(ctx)
	// TxPipelineDemo(ctx)
	err := watchDemo(ctx, "aaa"); if err != nil {
		fmt.Printf("watchDemo err: %v\n", err)
		return
	}
}

func stringDemo(ctx context.Context, key string, defaultValue string) (string, error) {

	val, err := rdb.Get(ctx, key).Result(); if err != nil {
		if errors.Is(err, redis.Nil) {
			return defaultValue, nil
		} else {
			return "", err
		}
	}
	return val, nil

	// _ = rdb.Set(ctx, "s", "test", 0).Err()
	// cmder := rdb.Get(ctx, "s")
	// fmt.Printf("val :%s, err: %v\n", cmder.Val(), cmder.Err())

}

func zsetDemo(ctx context.Context) {
	zsetKey := "z"
	languages := []redis.Z{
		{Score: 90.0, Member: "golang"},
		{Score: 80.0, Member: "python"},
		{Score: 95.0, Member: "c"},
	}

	err := rdb.ZAdd(ctx, zsetKey, languages...).Err(); if err != nil {
		fmt.Printf("zdd failed, err: %v\n", err)
		return
	}

	newScore, err := rdb.ZIncrBy(ctx, zsetKey, 10.0, "golang").Result(); if err != nil {
		fmt.Printf("zincrby failed, err: %v\n", err)
		return
	}
	fmt.Printf("golang's score is %f now.\n", newScore)

	ret := rdb.ZRevRangeWithScores(ctx, zsetKey, 0, 2).Val()
	for _, z := range ret {
		fmt.Printf("z.member: %s, z.score: %f\n", z.Member, z.Score)
	}

	op := &redis.ZRangeBy{
		Min: "95",
		Max: "100",
	}

	ret, err = rdb.ZRangeByScoreWithScores(ctx, zsetKey, op).Result(); if err != nil {
		fmt.Printf("zrangebyscore failed, err: %v\n", err)
		return
	}

	for _, z := range ret {
		fmt.Printf("z.member: %s, z.score: %f\n", z.Member, z.Score)
	}

}


func scanDemo(ctx context.Context) {
	// iter := rdb.SScan(ctx, "set-key", 0, "*", 0).Iterator()
	// iter := rdb.HScan(ctx, "hash-key", 0, "*", 0).Iterator()
	// iter := rdb.ZScan(ctx, "sorted-hash-key", 0, "*", 0).Iterator()
	iter := rdb.Scan(ctx, 0, "*", 0).Iterator()

	for iter.Next(ctx) {
		fmt.Printf("keys: %v\n", iter.Val())
	}

	if err := iter.Err(); err != nil {
		fmt.Printf("iter err: %v\n", err)
		return
	}
}


func pipelineDemo(ctx context.Context) {
	// pipe :=  rdb.Pipeline()

	// incr := pipe.Incr(ctx, "pipeline_counter")
	// pipe.Expire(ctx, "pipeline_counter", time.Hour)

	// cmds, err := pipe.Exec(ctx); if err != nil {
	// 	fmt.Printf("cmds: %v, err: %v\n", cmds, err)
	// 	return
	// }
	// fmt.Printf("incr val: %v\n", incr.Val())


	var incr *redis.IntCmd

	cmds, err := rdb.Pipelined(ctx, func(pipe redis.Pipeliner) error {
		incr = pipe.Incr(ctx, "pipelined_counter")
		pipe.Expire(ctx, "pipelined_counter", time.Hour)
		return nil
	})
	if err != nil {
		fmt.Printf("cmds: %v, err: %v\n", cmds, err)
		return
	}

	fmt.Printf("incr val: %v\n", incr.Val())
}

func TxPipelineDemo(ctx context.Context) {
	// pipe :=  rdb.TxPipeline()

	// incr := pipe.Incr(ctx, "pipeline_counter")
	// pipe.Expire(ctx, "pipeline_counter", time.Hour)

	// cmds, err := pipe.Exec(ctx); if err != nil {
	// 	fmt.Printf("cmds: %v, err: %v\n", cmds, err)
	// 	return
	// }
	// fmt.Printf("incr val: %v\n", incr.Val())


	var incr *redis.IntCmd

	cmds, err := rdb.TxPipelined(ctx, func(pipe redis.Pipeliner) error {
		incr = pipe.Incr(ctx, "pipelined_counter")
		pipe.Expire(ctx, "pipelined_counter", time.Hour)
		return nil
	})
	if err != nil {
		fmt.Printf("cmds: %v, err: %v\n", cmds, err)
		return
	}

	fmt.Printf("incr val: %v\n", incr.Val())
}

func watchDemo(ctx context.Context, key string) error {
	return rdb.Watch(ctx, func(tx *redis.Tx) error {
		n, err := tx.Get(ctx, key).Int(); if err != nil && err != redis.Nil {
			return err
		}

		time.Sleep(5 * time.Second)

		_, err = tx.TxPipelined(ctx, func(pipe redis.Pipeliner) error {
			pipe.Set(ctx, key, n + 1, 0)
			return nil
		})
		return err
	}, key)
}
