// Package database — исполнитель команд и сохранение/загрузка (аналог Database.cpp).
package database

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"

	"dbms/array"
	"dbms/doubly_list"
	"dbms/queue"
	"dbms/singly_list"
	"dbms/stack"
	"dbms/tree"
)

type Database struct {
	arrays      map[string]*array.MyArray
	singlyLists map[string]*singlylist.SinglyLinkedList
	doublyLists map[string]*doublylist.DoublyLinkedList
	stacks      map[string]*stack.Stack
	queues      map[string]*queue.Queue
	trees       map[string]*tree.CompleteBinaryTree
}

func New() *Database {
	db := &Database{}
	db.reset()
	return db
}

func (db *Database) reset() {
	db.arrays = map[string]*array.MyArray{}
	db.singlyLists = map[string]*singlylist.SinglyLinkedList{}
	db.doublyLists = map[string]*doublylist.DoublyLinkedList{}
	db.stacks = map[string]*stack.Stack{}
	db.queues = map[string]*queue.Queue{}
	db.trees = map[string]*tree.CompleteBinaryTree{}
}

// Как и operator[] у std::map в C++, геттеры создают структуру при первом обращении.
func (db *Database) getArray(name string) *array.MyArray {
	if v, ok := db.arrays[name]; ok {
		return v
	}
	v := array.New(2)
	db.arrays[name] = v
	return v
}

func (db *Database) getStack(name string) *stack.Stack {
	if v, ok := db.stacks[name]; ok {
		return v
	}
	v := stack.New()
	db.stacks[name] = v
	return v
}

func (db *Database) getQueue(name string) *queue.Queue {
	if v, ok := db.queues[name]; ok {
		return v
	}
	v := queue.New()
	db.queues[name] = v
	return v
}

func (db *Database) getSList(name string) *singlylist.SinglyLinkedList {
	if v, ok := db.singlyLists[name]; ok {
		return v
	}
	v := singlylist.New()
	db.singlyLists[name] = v
	return v
}

func (db *Database) getDList(name string) *doublylist.DoublyLinkedList {
	if v, ok := db.doublyLists[name]; ok {
		return v
	}
	v := doublylist.New()
	db.doublyLists[name] = v
	return v
}

func (db *Database) getTree(name string) *tree.CompleteBinaryTree {
	if v, ok := db.trees[name]; ok {
		return v
	}
	v := tree.New()
	db.trees[name] = v
	return v
}

// Минимальное число токенов (включая саму команду) для каждой команды.
var minArgs = map[string]int{
	"MPUSH": 3, "MGET": 3, "MDEL": 3, "MSET": 4, "MSIZE": 2,
	"MCAPACITY": 2, "MINSERT": 4, "MPRINT": 2,
	"SPUSH": 3, "SPOP": 2, "STOP": 2, "SEMPTY": 2, "SGET": 3, "SSIZE": 2, "SPRINT": 2,
	"QPUSH": 3, "QPOP": 2, "QFRONT": 2, "QEMPTY": 2, "QGET": 3, "QSIZE": 2, "QPRINT": 2,
	"FPUSH": 3, "FAPPEND": 3, "FDEL": 2, "FDELBACK": 2, "FREMOVE": 3,
	"FREMOVE_NODE": 3, "FREMOVE_AFTER": 3, "FREMOVE_BEFORE": 3, "FGET": 3, "FFIND": 3,
	"FINSERT_AFTER": 4, "FINSERT_BEFORE": 4, "FSIZE": 2, "FPRINT": 2,
	"LPUSH": 3, "LAPPEND": 3, "LDEL": 2, "LDELBACK": 2, "LREMOVE": 3,
	"LREMOVE_NODE": 3, "LREMOVE_AFTER": 3, "LREMOVE_BEFORE": 3, "LGET": 3, "LFIND": 3,
	"LINSERT_AFTER": 4, "LINSERT_BEFORE": 4, "LSIZE": 2, "LPRINT": 2,
	"TINSERT": 3, "TFIND": 3, "TCOMPLETE": 2, "TSIZE": 2, "TPRINT": 2, "TVALUES": 2,
	"PRINT": 1,
}

func boolStr(b bool) string {
	if b {
		return "TRUE"
	}
	return "FALSE"
}

func sortedKeys[V any](m map[string]V) []string {
	keys := make([]string, 0, len(m))
	for k := range m {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	return keys
}

func (db *Database) Execute(tokens []string) {
	if len(tokens) == 0 {
		return
	}
	cmd := tokens[0]

	if n, ok := minArgs[cmd]; ok && len(tokens) < n {
		fmt.Printf("Недостаточно аргументов для команды: %s\n", cmd)
		return
	}

	// Аргументы, которые в C++ разбирались через stoi.
	atoi := func(s string) (int, bool) {
		v, err := strconv.Atoi(s)
		if err != nil {
			fmt.Printf("Некорректное число: %s\n", s)
			return 0, false
		}
		return v, true
	}

	switch cmd {
	// ---------- Массивы ----------
	case "MPUSH":
		db.getArray(tokens[1]).PushBack(tokens[2])
		fmt.Println("OK")
	case "MGET":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		fmt.Println(db.getArray(tokens[1]).GetAt(idx))
	case "MDEL":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		db.getArray(tokens[1]).RemoveAt(idx)
		fmt.Println("OK")
	case "MSET":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		db.getArray(tokens[1]).SetAt(idx, tokens[3])
		fmt.Println("OK")
	case "MSIZE":
		fmt.Println(db.getArray(tokens[1]).GetSize())
	case "MCAPACITY":
		fmt.Println(db.getArray(tokens[1]).GetCapacity())
	case "MINSERT":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		db.getArray(tokens[1]).InsertAt(idx, tokens[3])
		fmt.Println("OK")
	case "MPRINT":
		db.getArray(tokens[1]).Print()

	// ---------- Стеки ----------
	case "SPUSH":
		db.getStack(tokens[1]).Push(tokens[2])
		fmt.Println("OK")
	case "SPOP":
		fmt.Println(db.getStack(tokens[1]).Pop())
	case "STOP":
		fmt.Println(db.getStack(tokens[1]).Top())
	case "SEMPTY":
		fmt.Println(boolStr(db.getStack(tokens[1]).IsEmpty()))
	case "SGET":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		fmt.Println(db.getStack(tokens[1]).GetAt(idx))
	case "SSIZE":
		fmt.Println(db.getStack(tokens[1]).GetSize())
	case "SPRINT":
		db.getStack(tokens[1]).Print()

	// ---------- Очереди ----------
	case "QPUSH":
		db.getQueue(tokens[1]).Push(tokens[2])
		fmt.Println("OK")
	case "QPOP":
		fmt.Println(db.getQueue(tokens[1]).Pop())
	case "QFRONT":
		fmt.Println(db.getQueue(tokens[1]).GetFront())
	case "QEMPTY":
		fmt.Println(boolStr(db.getQueue(tokens[1]).IsEmpty()))
	case "QGET":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		fmt.Println(db.getQueue(tokens[1]).GetAt(idx))
	case "QSIZE":
		fmt.Println(db.getQueue(tokens[1]).GetSize())
	case "QPRINT":
		db.getQueue(tokens[1]).Print()

	// ---------- Односвязные списки ----------
	case "FPUSH":
		db.getSList(tokens[1]).PushFront(tokens[2])
		fmt.Println("OK")
	case "FAPPEND":
		db.getSList(tokens[1]).PushBack(tokens[2])
		fmt.Println("OK")
	case "FDEL":
		db.getSList(tokens[1]).PopFront()
		fmt.Println("OK")
	case "FDELBACK":
		db.getSList(tokens[1]).PopBack()
		fmt.Println("OK")
	case "FREMOVE":
		db.getSList(tokens[1]).RemoveByValue(tokens[2])
		fmt.Println("OK")
	case "FREMOVE_NODE":
		db.getSList(tokens[1]).RemoveNode(tokens[2])
		fmt.Println("OK")
	case "FREMOVE_AFTER":
		db.getSList(tokens[1]).RemoveAfter(tokens[2])
		fmt.Println("OK")
	case "FREMOVE_BEFORE":
		db.getSList(tokens[1]).RemoveBefore(tokens[2])
		fmt.Println("OK")
	case "FGET":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		fmt.Println(db.getSList(tokens[1]).GetAt(idx))
	case "FFIND":
		fmt.Println(boolStr(db.getSList(tokens[1]).Find(tokens[2]) != nil))
	case "FINSERT_AFTER":
		db.getSList(tokens[1]).InsertAfter(tokens[2], tokens[3])
		fmt.Println("OK")
	case "FINSERT_BEFORE":
		db.getSList(tokens[1]).InsertBefore(tokens[2], tokens[3])
		fmt.Println("OK")
	case "FSIZE":
		fmt.Println(db.getSList(tokens[1]).GetSize())
	case "FPRINT":
		db.getSList(tokens[1]).Print()

	// ---------- Двусвязные списки ----------
	case "LPUSH":
		db.getDList(tokens[1]).PushFront(tokens[2])
		fmt.Println("OK")
	case "LAPPEND":
		db.getDList(tokens[1]).PushBack(tokens[2])
		fmt.Println("OK")
	case "LDEL":
		db.getDList(tokens[1]).PopFront()
		fmt.Println("OK")
	case "LDELBACK":
		db.getDList(tokens[1]).PopBack()
		fmt.Println("OK")
	case "LREMOVE":
		db.getDList(tokens[1]).RemoveByValue(tokens[2])
		fmt.Println("OK")
	case "LREMOVE_NODE":
		db.getDList(tokens[1]).RemoveNode(tokens[2])
		fmt.Println("OK")
	case "LREMOVE_AFTER":
		db.getDList(tokens[1]).RemoveAfter(tokens[2])
		fmt.Println("OK")
	case "LREMOVE_BEFORE":
		db.getDList(tokens[1]).RemoveBefore(tokens[2])
		fmt.Println("OK")
	case "LGET":
		idx, ok := atoi(tokens[2])
		if !ok {
			return
		}
		fmt.Println(db.getDList(tokens[1]).GetAt(idx))
	case "LFIND":
		fmt.Println(boolStr(db.getDList(tokens[1]).Find(tokens[2]) != nil))
	case "LINSERT_AFTER":
		db.getDList(tokens[1]).InsertAfter(tokens[2], tokens[3])
		fmt.Println("OK")
	case "LINSERT_BEFORE":
		db.getDList(tokens[1]).InsertBefore(tokens[2], tokens[3])
		fmt.Println("OK")
	case "LSIZE":
		fmt.Println(db.getDList(tokens[1]).GetSize())
	case "LPRINT":
		db.getDList(tokens[1]).Print()

	// ---------- Деревья ----------
	case "TINSERT":
		v, ok := atoi(tokens[2])
		if !ok {
			return
		}
		db.getTree(tokens[1]).Insert(v)
		fmt.Println("OK")
	case "TFIND":
		v, ok := atoi(tokens[2])
		if !ok {
			return
		}
		fmt.Println(boolStr(db.getTree(tokens[1]).Find(v)))
	case "TCOMPLETE":
		fmt.Println(boolStr(db.getTree(tokens[1]).IsComplete()))
	case "TSIZE":
		fmt.Println(db.getTree(tokens[1]).GetSize())
	case "TPRINT":
		db.getTree(tokens[1]).Print()
	case "TVALUES":
		values := db.getTree(tokens[1]).GetValues()
		for i, v := range values {
			fmt.Print(v)
			if i < len(values)-1 {
				fmt.Print(" ")
			}
		}
		fmt.Println()

	// ---------- Вывод всего ----------
	case "PRINT":
		for _, name := range sortedKeys(db.arrays) {
			fmt.Printf("ARRAY %s:\n", name)
			db.arrays[name].Print()
		}
		for _, name := range sortedKeys(db.stacks) {
			fmt.Printf("STACK %s:\n", name)
			db.stacks[name].Print()
		}
		for _, name := range sortedKeys(db.queues) {
			fmt.Printf("QUEUE %s:\n", name)
			db.queues[name].Print()
		}
		for _, name := range sortedKeys(db.singlyLists) {
			fmt.Printf("SLIST %s:\n", name)
			db.singlyLists[name].Print()
		}
		for _, name := range sortedKeys(db.doublyLists) {
			fmt.Printf("DLIST %s:\n", name)
			db.doublyLists[name].Print()
		}
		for _, name := range sortedKeys(db.trees) {
			fmt.Printf("TREE %s:\n", name)
			db.trees[name].Print()
		}

	default:
		fmt.Printf("Неизвестная команда: %s\n", cmd)
	}
}

func (db *Database) Save(filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Printf("Не удалось открыть файл для записи: %s\n", filename)
		return
	}
	defer file.Close()

	w := bufio.NewWriter(file)
	defer w.Flush()

	for _, name := range sortedKeys(db.arrays) {
		arr := db.arrays[name]
		fmt.Fprintf(w, "ARRAY %s %d", name, arr.GetSize())
		for i := 0; i < arr.GetSize(); i++ {
			fmt.Fprintf(w, " %s", arr.GetAt(i))
		}
		fmt.Fprintln(w)
	}

	for _, name := range sortedKeys(db.stacks) {
		st := db.stacks[name]
		fmt.Fprintf(w, "STACK %s %d", name, st.GetSize())
		for i := 0; i < st.GetSize(); i++ {
			fmt.Fprintf(w, " %s", st.GetAt(i))
		}
		fmt.Fprintln(w)
	}

	for _, name := range sortedKeys(db.queues) {
		q := db.queues[name]
		fmt.Fprintf(w, "QUEUE %s %d", name, q.GetSize())
		for i := 0; i < q.GetSize(); i++ {
			fmt.Fprintf(w, " %s", q.GetAt(i))
		}
		fmt.Fprintln(w)
	}

	for _, name := range sortedKeys(db.singlyLists) {
		lst := db.singlyLists[name]
		fmt.Fprintf(w, "SLIST %s %d", name, lst.GetSize())
		for i := 0; i < lst.GetSize(); i++ {
			fmt.Fprintf(w, " %s", lst.GetAt(i))
		}
		fmt.Fprintln(w)
	}

	for _, name := range sortedKeys(db.doublyLists) {
		lst := db.doublyLists[name]
		fmt.Fprintf(w, "DLIST %s %d", name, lst.GetSize())
		for i := 0; i < lst.GetSize(); i++ {
			fmt.Fprintf(w, " %s", lst.GetAt(i))
		}
		fmt.Fprintln(w)
	}

	for _, name := range sortedKeys(db.trees) {
		values := db.trees[name].GetValues()
		fmt.Fprintf(w, "TREE %s %d", name, len(values))
		for _, v := range values {
			fmt.Fprintf(w, " %d", v)
		}
		fmt.Fprintln(w)
	}
}

func (db *Database) Load(filename string) {
	db.reset()

	file, err := os.Open(filename)
	if err != nil {
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Buffer(make([]byte, 1024*1024), 64*1024*1024)

	for scanner.Scan() {
		tokens := strings.Fields(scanner.Text())
		if len(tokens) < 3 {
			continue
		}

		typ, name := tokens[0], tokens[1]
		count, err := strconv.Atoi(tokens[2])
		if err != nil || count < 0 || 3+count > len(tokens) {
			continue // повреждённая строка
		}
		vals := tokens[3 : 3+count]

		switch typ {
		case "ARRAY":
			arr := db.getArray(name)
			for _, v := range vals {
				arr.PushBack(v)
			}
		case "STACK":
			st := db.getStack(name)
			for i := count - 1; i >= 0; i-- {
				st.Push(vals[i])
			}
		case "QUEUE":
			q := db.getQueue(name)
			for _, v := range vals {
				q.Push(v)
			}
		case "SLIST":
			lst := db.getSList(name)
			for i := count - 1; i >= 0; i-- {
				lst.PushFront(vals[i])
			}
		case "DLIST":
			lst := db.getDList(name)
			for i := count - 1; i >= 0; i-- {
				lst.PushFront(vals[i])
			}
		case "TREE":
			t := db.getTree(name)
			for _, s := range vals {
				v, err := strconv.Atoi(s)
				if err != nil {
					continue
				}
				t.Insert(v)
			}
		}
	}
}
