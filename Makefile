CC = gcc
FFLAGS = -g -o2 -lm

TARGETS = avector

.PHONY: all clean
all: $(TARGETS)

avector: avector.c
	$(CC) $(FFLAGS) $< -o $@

clean:
	-rm -f *.o $(TARGETS) *.err *.out