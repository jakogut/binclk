CC = gcc
LD = $(CC)

CFLAGS = -std=gnu11
OFLAGS = 
LFLAGS = -lc -lmraa

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: binclk

binclk: $(OBJECTS)
	$(LD) $(LFLAGS) $(OBJECTS) -o binclk

install: binclk
	cp -rf ./binclk /usr/bin/binclk
	cp -rf ./binclk.service /etc/systemd/system/binclk.service

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf binclk gmon.out *.save *.o core* vgcore*

rebuild: clean all

.PHONY : clean
.SILENT : clean
