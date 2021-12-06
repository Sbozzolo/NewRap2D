CC = gcc

CFLAGS = -O2 -lm

# Debug flags
CFLAGS += -Wall -Wextra -pedantic -Werror
CFLAGS += -Wmissing-declarations -g

test: test_NewRap2D
	./test_NewRap2D -v | ./greenest

*.o: NewRap2D.h greatest.h Makefile test_NewRap2D.c

%.o: %.c
	${CC} -c -o $@ ${CFLAGS} $<

%: %.o
	${CC} -o $@ ${LDFLAGS} $^

clean:
	rm -f test_NewRap2D *.o
