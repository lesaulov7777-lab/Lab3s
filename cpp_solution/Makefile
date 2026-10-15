CXX = g++
CXXFLAGS = -std=c++17 -Wall
INCLUDES = -Iinterface -Iarray -Isingly_list -Idoubly_list -Istack -Iqueue -Itree

SRCS = main.cpp \
       interface/Database.cpp \
       array/MyArray.cpp \
       singly_list/SinglyLinkedList.cpp \
       doubly_list/DoublyLinkedList.cpp \
       stack/Stack.cpp \
       queue/Queue.cpp \
       tree/CompleteBinaryTree.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = dbms

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET) --file interface/file.data --query 'PRINT'