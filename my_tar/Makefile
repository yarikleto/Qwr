CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)
OBJFILES := $(BINS:%=%.o)
TARGET = my_tar

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -rvf ${OBJFILES} ${BINS}

re: clean all
