CC = clang
FFLAGS = -g

TARGETS = avector

.PHONY: all clean
all: $(TARGETS)

avector: avector.c
	$(CC) $(FFLAGS) $< -o $@

clean:
	-rm -f *.o $(TARGETS) *.err *.out