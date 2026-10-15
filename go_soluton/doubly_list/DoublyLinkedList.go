// Package doublylist — двусвязный список (аналог DoublyLinkedList.cpp).
package doublylist

import "fmt"

type Node struct {
	Value string
	Next  *Node
	Prev  *Node
}

type DoublyLinkedList struct {
	head *Node
	tail *Node
	size int
}

func New() *DoublyLinkedList { return &DoublyLinkedList{} }

func (l *DoublyLinkedList) GetSize() int { return l.size }

// Print выводит список без завершающего перевода строки — как в C++.
func (l *DoublyLinkedList) Print() {
	fmt.Print("[")
	for cur := l.head; cur != nil; cur = cur.Next {
		fmt.Print(cur.Value)
		if cur.Next != nil {
			fmt.Print(" <-> ")
		}
	}
	fmt.Print("]")
}

func (l *DoublyLinkedList) PushFront(value string) {
	n := &Node{Value: value}
	if l.head == nil {
		l.head = n
		l.tail = n
	} else {
		n.Next = l.head
		l.head.Prev = n
		l.head = n
	}
	l.size++
}

func (l *DoublyLinkedList) PushBack(value string) {
	n := &Node{Value: value}
	if l.head == nil {
		l.head = n
		l.tail = n
	} else {
		n.Prev = l.tail
		l.tail.Next = n
		l.tail = n
	}
	l.size++
}

func (l *DoublyLinkedList) PopFront() {
	if l.size == 0 {
		fmt.Println("Ошибка, список пуст")
		return
	}
	if l.head == l.tail {
		l.head, l.tail = nil, nil
		l.size--
		return
	}
	l.head = l.head.Next
	l.head.Prev = nil
	l.size--
}

func (l *DoublyLinkedList) PopBack() {
	if l.head == nil {
		fmt.Println("Ошибка, список пуст")
		return
	}
	if l.head == l.tail {
		l.head, l.tail = nil, nil
		l.size--
		return
	}
	l.tail = l.tail.Prev
	l.tail.Next = nil
	l.size--
}

func (l *DoublyLinkedList) Find(value string) *Node {
	for cur := l.head; cur != nil; cur = cur.Next {
		if cur.Value == value {
			return cur
		}
	}
	return nil
}

func (l *DoublyLinkedList) InsertAfter(target, value string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	if node == l.tail {
		l.PushBack(value)
		return
	}
	n := &Node{Value: value, Next: node.Next, Prev: node}
	node.Next.Prev = n
	node.Next = n
	l.size++
}

func (l *DoublyLinkedList) InsertBefore(target, value string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	if node == l.head {
		l.PushFront(value)
		return
	}
	n := &Node{Value: value, Next: node, Prev: node.Prev}
	node.Prev.Next = n
	node.Prev = n
	l.size++
}

func (l *DoublyLinkedList) unlinkNode(node *Node) {
	if node == l.head {
		l.PopFront()
		return
	}
	if node == l.tail {
		l.PopBack()
		return
	}
	node.Prev.Next = node.Next
	node.Next.Prev = node.Prev
	l.size--
}

func (l *DoublyLinkedList) RemoveNode(value string) {
	if l.head == nil {
		fmt.Println("Ошибка, список пуст")
		return
	}
	node := l.Find(value)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	l.unlinkNode(node)
}

func (l *DoublyLinkedList) RemoveByValue(value string) {
	l.RemoveNode(value)
}

func (l *DoublyLinkedList) RemoveAfter(target string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	if node.Next == nil {
		fmt.Println("После заданного узла нет узла")
		return
	}
	l.unlinkNode(node.Next)
}

func (l *DoublyLinkedList) RemoveBefore(target string) {
	node := l.Find(target)
	if node == nil {
		fmt.Println("Узел с таким значением не найден")
		return
	}
	if node.Prev == nil {
		fmt.Println("Перед заданным узлом нет узла")
		return
	}
	l.unlinkNode(node.Prev)
}

func (l *DoublyLinkedList) GetAt(index int) string {
	if index < 0 || index >= l.size {
		fmt.Println("Ошибка, индекс за пределами даопозна")
		return ""
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.Next
	}
	return cur.Value
}
