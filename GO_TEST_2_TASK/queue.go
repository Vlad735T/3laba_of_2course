package main

import (
	"errors"
	"fmt"
)

type Node struct {
	data string
	next *Node
	prev *Node
}

type QUEUE struct {
	head *Node
	tail *Node
}

func new_node(data string) *Node {
	return &Node{
		data: data,
		next: nil,
		prev: nil,
	}
}

func new_queue() *QUEUE {
	return &QUEUE{
		head: nil,
		tail: nil,
	}
}

func (q *QUEUE) push(value string) {

	new_node := new_node(value)

	if q.tail == nil && q.head == nil {
		q.head = new_node
		q.tail = new_node
	} else {
		q.tail.next = new_node
		new_node.prev = q.tail
		q.tail = new_node
	}
}

func (q *QUEUE) is_empty() bool {
	return q.head == nil
}

func (q *QUEUE) size() (int, error) {

	if q.head == nil {
		return 0, errors.New("queue is empty")
	}

	temp := q.head
	count := 0

	for temp != nil {
		count++
		temp = temp.next
	}
	return count, nil
}

func (q *QUEUE) pop() string {
	if q.is_empty() {
		return ""
	}

	temp := q.head.data

	if q.head == q.tail {
		q.head = nil
		q.tail = nil
	} else {
		q.head = q.head.next
		q.head.prev = nil
	}
	return temp
}

func (q *QUEUE) print() {
	current := q.head
	for current != nil {
		fmt.Print(current.data, " ")
		current = current.next
	}
}
