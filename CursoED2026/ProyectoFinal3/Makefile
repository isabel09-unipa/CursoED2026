CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

SOURCES = main.c destinos.c pasajeros.c viajes.c estadisticas.c utils.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = terminal_buenaventura

ifdef OS
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
    TARGET_FILE = $(TARGET).exe
else
    RM = rm -f
    TARGET_FILE = $(TARGET)
endif
else
    RM = rm -f
    TARGET_FILE = $(TARGET)
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET_FILE) $(TARGET).exe
