// Package queue — очередь (FIFO) на односвязных узлах (аналог Queue.cpp).
package queue

import "fmt"

type Node struct {
	Value string
	Next  *Node
}

type Queue struct {
	head *Node
	tail *Node
	size int
}

func New() *Queue { return &Queue{} }

func (q *Queue) Push(value string) {
	node := &Node{Value: value}
	if q.tail == nil {
		q.head = node
		q.tail = node
	} else {
		q.tail.Next = node
		q.tail = node
	}
	q.size++
}

func (q *Queue) Pop() string {
	if q.head == nil {
		return ""
	}
	node := q.head
	val := node.Value
	q.head = q.head.Next
	if q.head == nil {
		q.tail = nil
	}
	q.size--
	return val
}

func (q *Queue) GetFront() string {
	if q.head == nil {
		fmt.Println("Очередь пуста")
		return ""
	}
	return q.head.Value
}

func (q *Queue) IsEmpty() bool { return q.size == 0 }

func (q *Queue) GetSize() int { return q.size }

func (q *Queue) GetAt(index int) string {
	if index < 0 || index >= q.size {
		fmt.Println("Ошибка, индекс за пределами диапазона")
		return ""
	}
	cur := q.head
	for i := 0; i < index; i++ {
		cur = cur.Next
	}
	return cur.Value
}

func (q *Queue) Print() {
	fmt.Print("[")
	for cur := q.head; cur != nil; cur = cur.Next {
		fmt.Print(cur.Value)
		if cur.Next != nil {
			fmt.Print(" -> ")
		}
	}
	fmt.Println("]")
}
