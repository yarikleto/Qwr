CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -g3 -fsanitize=address
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)
OBJFILES := $(BINS:%=%.o)
TARGET = my_tar

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -rvf ${OBJFILES} 

re: all clean
