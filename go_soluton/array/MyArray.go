// Package array — динамический массив строк (аналог MyArray.cpp).
package array

import "fmt"

type MyArray struct {
	data     []string
	capacity int
	size     int
}

// New создаёт массив с начальной ёмкостью cap (по умолчанию 2).
func New(cap int) *MyArray {
	if cap <= 0 {
		cap = 2
	}
	return &MyArray{data: make([]string, cap), capacity: cap}
}

func (a *MyArray) GetSize() int     { return a.size }
func (a *MyArray) GetCapacity() int { return a.capacity }

func (a *MyArray) grow() {
	a.capacity *= 2
	newData := make([]string, a.capacity)
	copy(newData, a.data[:a.size])
	a.data = newData
}

func (a *MyArray) PushBack(value string) {
	if a.size >= a.capacity {
		a.grow()
	}
	a.data[a.size] = value
	a.size++
}

func (a *MyArray) InsertAt(index int, value string) {
	if index < 0 || index > a.size {
		fmt.Println("Индекс вне диапазона")
		return
	}
	if a.size == a.capacity {
		a.grow()
	}
	for i := a.size; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	a.data[index] = value
	a.size++
}

func (a *MyArray) GetAt(index int) string {
	if index < 0 || index >= a.size {
		fmt.Println("Индекс вне диапазона")
		return ""
	}
	return a.data[index]
}

func (a *MyArray) SetAt(index int, value string) {
	if index < 0 || index >= a.size {
		fmt.Println("Индекс вне диапазона")
		return
	}
	a.data[index] = value
}

func (a *MyArray) RemoveAt(index int) {
	if index < 0 || index >= a.size {
		fmt.Println("Индекс вне диапазона")
		return
	}
	for i := index; i < a.size-1; i++ {
		a.data[i] = a.data[i+1]
	}
	a.size--
}

func (a *MyArray) Print() {
	fmt.Print("[")
	for i := 0; i < a.size; i++ {
		fmt.Print(a.data[i])
		if i < a.size-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}
