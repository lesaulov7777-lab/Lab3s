// Package tree — полное бинарное дерево (аналог CompleteBinaryTree.cpp).
package tree

import (
	"fmt"
	"strings"
)

type TreeNode struct {
	Value int
	Left  *TreeNode
	Right *TreeNode
}

type CompleteBinaryTree struct {
	root *TreeNode
	size int
}

func New() *CompleteBinaryTree { return &CompleteBinaryTree{} }

// Insert вставляет значение в первую свободную позицию (обход в ширину).
func (t *CompleteBinaryTree) Insert(value int) {
	newNode := &TreeNode{Value: value}
	if t.root == nil {
		t.root = newNode
		t.size++
		return
	}
	q := []*TreeNode{t.root}
	for len(q) > 0 {
		cur := q[0]
		q = q[1:]

		if cur.Left == nil {
			cur.Left = newNode
			t.size++
			return
		}
		q = append(q, cur.Left)

		if cur.Right == nil {
			cur.Right = newNode
			t.size++
			return
		}
		q = append(q, cur.Right)
	}
}

func findHelper(node *TreeNode, value int) bool {
	if node == nil {
		return false
	}
	if node.Value == value {
		return true
	}
	return findHelper(node.Left, value) || findHelper(node.Right, value)
}

func (t *CompleteBinaryTree) Find(value int) bool { return findHelper(t.root, value) }

func (t *CompleteBinaryTree) GetSize() int { return t.size }

// GetValues возвращает значения в порядке обхода в ширину.
func (t *CompleteBinaryTree) GetValues() []int {
	values := []int{}
	if t.root == nil {
		return values
	}
	q := []*TreeNode{t.root}
	for len(q) > 0 {
		cur := q[0]
		q = q[1:]
		values = append(values, cur.Value)
		if cur.Left != nil {
			q = append(q, cur.Left)
		}
		if cur.Right != nil {
			q = append(q, cur.Right)
		}
	}
	return values
}

func (t *CompleteBinaryTree) IsComplete() bool {
	if t.root == nil {
		return true
	}
	q := []*TreeNode{t.root}
	seenNil := false
	for len(q) > 0 {
		cur := q[0]
		q = q[1:]
		if cur == nil {
			seenNil = true
		} else {
			if seenNil {
				return false
			}
			q = append(q, cur.Left, cur.Right)
		}
	}
	return true
}

func heightHelper(node *TreeNode) int {
	if node == nil {
		return -1
	}
	l, r := heightHelper(node.Left), heightHelper(node.Right)
	if l > r {
		return 1 + l
	}
	return 1 + r
}

func (t *CompleteBinaryTree) Print() {
	if t.root == nil {
		fmt.Println("[]")
		return
	}

	h := heightHelper(t.root)
	q := []*TreeNode{t.root}
	level := 0

	for len(q) > 0 {
		levelSize := len(q)
		spacesBefore := (1 << uint(h-level)) - 1
		spacesBetween := (1 << uint(h-level+1)) - 1

		levelNodes := make([]*TreeNode, 0, levelSize)
		var sb strings.Builder

		// Отступ
		sb.WriteString(strings.Repeat(" ", spacesBefore))

		// Узлы
		for i := 0; i < levelSize; i++ {
			cur := q[0]
			q = q[1:]
			levelNodes = append(levelNodes, cur)

			sb.WriteString(fmt.Sprint(cur.Value))
			if i < levelSize-1 {
				sb.WriteString(strings.Repeat(" ", spacesBetween))
			}
			if cur.Left != nil {
				q = append(q, cur.Left)
			}
			if cur.Right != nil {
				q = append(q, cur.Right)
			}
		}
		fmt.Println(sb.String())

		// Линии
		if level < h {
			sb.Reset()
			lineIndent := spacesBefore - 1
			if lineIndent < 0 {
				lineIndent = 0
			}
			sb.WriteString(strings.Repeat(" ", lineIndent))

			for i, node := range levelNodes {
				if node.Left != nil {
					sb.WriteString("/")
				} else {
					sb.WriteString(" ")
				}
				sb.WriteString(" ")
				if node.Right != nil {
					sb.WriteString("\\")
				} else {
					sb.WriteString(" ")
				}
				if i < len(levelNodes)-1 {
					sb.WriteString(strings.Repeat(" ", spacesBetween-2))
				}
			}
			fmt.Println(sb.String())
		}
		level++
	}
}
