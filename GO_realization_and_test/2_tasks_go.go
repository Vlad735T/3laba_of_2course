package main // говорим компилятору что данная программа является главной среди всех

import "fmt"

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

func main() {

	q1 := new_queue()
	q2 := new_queue()

	q1.push("keks")
	q1.push("VLad")
	q1.print()
	fmt.Println(": 1 queue")
	q1.pop()
	q1.print()
	fmt.Println(": 1 queue")

	q2.push("keks")
	q2.push("Igor")
	q2.print()
	fmt.Println(": 2 queue")

	q2.pop()
	q2.print()
	fmt.Println(": 2 queue")

	q2.pop()
	q2.print()
	fmt.Println(": 2 queue")

	q2.pop()
	q2.print()
	fmt.Println(": 2 queue")

	q2.pop()
	q2.print()
	fmt.Println(": 2 queue")

}
