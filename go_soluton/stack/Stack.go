// Package stack — стек на основе односвязного списка (аналог Stack.cpp).
package stack

import (
	"fmt"

	"dbms/singly_list"
)

type Stack struct {
	list *singlylist.SinglyLinkedList
}

func New() *Stack { return &Stack{list: singlylist.New()} }

func (s *Stack) Push(value string) { s.list.PushFront(value) }

func (s *Stack) IsEmpty() bool { return s.list.GetSize() == 0 }

func (s *Stack) GetSize() int { return s.list.GetSize() }

func (s *Stack) GetAt(index int) string {
	if index < 0 || index >= s.GetSize() {
		fmt.Println("Ошибка, индекс за пределами диапазона")
		return ""
	}
	return s.list.GetAt(index)
}

func (s *Stack) Pop() string {
	if s.IsEmpty() {
		return ""
	}
	val := s.list.GetAt(0)
	s.list.PopFront()
	return val
}

func (s *Stack) Top() string {
	if s.IsEmpty() {
		fmt.Println("Стэк пуст")
		return ""
	}
	return s.list.GetAt(0)
}

func (s *Stack) Print() { s.list.Print() }
