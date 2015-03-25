CC = gcc
CFLAGS = -Werror
LDFLAGS = -lcurl
TARGET = subscriber
OBJS += subscriber.o

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

subscriber.o:subscriber.c
	$(CC) -c subscriber.c -o $@

clean:
	rm $(TARGET) -rf
	rm $(OBJS) -rf
