CC = gcc

# compiler flags:
CFLAGS = -g -Wall

TARGET = copy_images

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
	$(RM) -rf out
