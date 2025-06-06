CC=gcc
CFLAGS=-Wall
TARGET=gpio-toggle

all: $(TARGET)

$(TARGET): gpio_toggle.c
	$(CC) $(CFLAGS) -o $(TARGET) gpio_toggle.c

install:
	sudo cp $(TARGET) /usr/bin/

clean:
	rm -f $(TARGET)
