CC = gcc
PAPI_INC = /opt/ohpc/pub/libs/papi/6.0.0/include
PAPI_LIB = /opt/ohpc/pub/libs/papi/6.0.0/lib

CFLAGS  = -g -O2 -I$(PAPI_INC)
LDFLAGS = -L$(PAPI_LIB)
LDLIBS  = -lpapi -lm

TARGETS = avector

.PHONY: all clean
all: $(TARGETS)

avector: avector.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

clean:
	-rm -f *.o $(TARGETS) *.err *.out