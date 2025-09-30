#Gilma Sebastian Mihai 315CA
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = tema1
SRCS = $(wildcard *.c)
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files and output
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = tema1

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
	# Create a zip archive with all project files
pack:
	zip -r Gilma_Sebastian-Mihai_315CA.zip . -x "$(TARGET)" -x "*.o" -x "Gilma_sebastian.zip"


.PHONY: all clean