CC = g++

CFLAGS = -Wall -g -std=c++11 -Wno-c++11-extensions

TARGET = lab2

SOURCES = main.cpp

OBJECTS = $(SOURCES:.cpp=.o)


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)



# Запуск UI
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) 


.PHONY: all run test cleanн