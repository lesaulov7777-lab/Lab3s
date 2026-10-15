TARGET = dbms

all: $(TARGET)

$(TARGET):
	go build -o $(TARGET) .

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) --file interface/file.data --query 'PRINT'

.PHONY: all clean run $(TARGET)
