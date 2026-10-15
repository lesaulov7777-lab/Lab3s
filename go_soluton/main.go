package main

import (
	"fmt"
	"os"
	"strings"

	"dbms/interface"
)

// parseQuery разбивает строку запроса на токены по пробелам.
func parseQuery(query string) []string {
	return strings.Fields(query)
}

func main() {
	filename := ""
	query := ""

	// Разбор аргументов командной строки
	args := os.Args[1:]
	for i := 0; i < len(args); i++ {
		switch args[i] {
		case "--file":
			if i+1 < len(args) {
				filename = args[i+1]
				i++
			} else {
				fmt.Println("Ошибка: отсутствует значение для --file")
				os.Exit(1)
			}
		case "--query":
			if i+1 < len(args) {
				query = args[i+1]
				i++
			} else {
				fmt.Println("Ошибка: отсутствует значение для --query")
				os.Exit(1)
			}
		}
	}

	tokens := parseQuery(query)

	db := database.New()
	db.Load(filename)
	db.Execute(tokens)
	db.Save(filename)
}
