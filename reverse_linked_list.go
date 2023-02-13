package main

type listNode struct {
	val int
	next *listNode
}

func reverseLinkedList(head *listNode) *listNode {
	curr := head
	var prev *listNode = nil

	for curr != nil {
		next := curr.next
		curr.next = prev
		prev = curr
		curr = next
	}

	return prev
}