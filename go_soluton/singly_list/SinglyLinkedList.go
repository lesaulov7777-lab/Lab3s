// Package singlylist — односвязный список (аналог SinglyLinkedList.cpp).
package singlylist

import "fmt"

type Node struct {
	Value string
	Next  *Node
}

type SinglyLinkedList struct {
	head *Node
	size int
}

func New() *SinglyLinkedList { return &SinglyLinkedList{} }

func (l *SinglyLinkedList) GetSize() int { return l.size }

func (l *SinglyLinkedList) Print() {
	fmt.Print("[")
	for cur := l.head; cur != nil; cur = cur.Next {
		fmt.Print(cur.Value)
		if cur.Next != nil {
			fmt.Print(" -> ")
		}
	}
	fmt.Println("]")
}

func (l *SinglyLinkedList) PushFront(value string) {
	l.head = &Node{Value: value, Next: l.head}
	l.size++
}

func (l *SinglyLinkedList) PushBack(value string) {
	n := &Node{Value: value}
	if l.head == nil {
		l.head = n
	} else {
		cur := l.head
		for cur.Next != nil {
			cur = cur.Next
		}
		cur.Next = n
	}
	l.size++
}

func (l *SinglyLinkedList) PopFront() {
	if l.head == nil {
		fmt.Println("Список пуст йоу")
		return
	}
	l.head = l.head.Next
	l.size--
}

func (l *SinglyLinkedList) PopBack() {
	if l.head == nil {
		fmt.Println("Список пуст йоу")
		return
	}
	if l.head.Next == nil {
		l.head = nil
		l.size--
		return
	}
	cur := l.head
	for cur.Next.Next != nil {
		cur = cur.Next
	}
	cur.Next = nil
	l.size--
}

func (l *SinglyLinkedList) Find(value string) *Node {
	for cur := l.head; cur != nil; cur = cur.Next {
		if cur.Value == value {
			return cur
		}
	}
	return nil
}

func (l *SinglyLinkedList) InsertAfter(target, value string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	node.Next = &Node{Value: value, Next: node.Next}
	l.size++
}

func (l *SinglyLinkedList) InsertBefore(target, value string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	if node == l.head {
		l.PushFront(value)
		return
	}
	cur := l.head
	for cur != nil && cur.Next != node {
		cur = cur.Next
	}
	cur.Next = &Node{Value: value, Next: node}
	l.size++
}

func (l *SinglyLinkedList) RemoveByValue(value string) {
	l.RemoveNode(value)
}

func (l *SinglyLinkedList) RemoveNode(value string) {
	if l.head == nil {
		fmt.Println("Список пуст йоу")
		return
	}
	if l.head.Value == value {
		l.PopFront()
		return
	}
	cur := l.head
	for cur.Next != nil && cur.Next.Value != value {
		cur = cur.Next
	}
	if cur.Next == nil {
		fmt.Println("Значение не найдено")
		return
	}
	cur.Next = cur.Next.Next
	l.size--
}

func (l *SinglyLinkedList) RemoveAfter(target string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	if node.Next == nil {
		fmt.Println("После заданного узла нет узла")
		return
	}
	node.Next = node.Next.Next
	l.size--
}

func (l *SinglyLinkedList) RemoveBefore(target string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	if node == l.head {
		fmt.Println("Перед заданным узлом нет узла")
		return
	}
	prev := l.head
	for prev.Next != node {
		prev = prev.Next
	}
	if prev == l.head {
		l.PopFront()
		return
	}
	prevPrev := l.head
	for prevPrev.Next != prev {
		prevPrev = prevPrev.Next
	}
	prevPrev.Next = node
	l.size--
}

func (l *SinglyLinkedList) GetAt(index int) string {
	if index < 0 || index >= l.size {
		fmt.Println("Ошибка, индекс за пределами диапозона")
		return ""
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.Next
	}
	return cur.Value
}
