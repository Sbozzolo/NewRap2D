CC = gcc

# Warning flags for C and C++:
CFLAGS = -O2

# Debug flags
CFLAGS += -Wall -Wextra -pedantic -Werror
CFLAGS += -Wmissing-declarations -g

test: test_NewRap2D
	./test_NewRap2D

*.o: NewRap2D.h greatest.h Makefile test_NewRap2D.c

%.o: %.c
	${CC} -c -o $@ ${CFLAGS} $<

%: %.o
	${CC} -o $@ ${LDFLAGS} $^

clean:
	rm -f test_NewRap2D *.o
