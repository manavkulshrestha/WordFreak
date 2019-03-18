SRC := $(shell ls *.c)
OBJ := $(subst .c,.o,$(SRC))
HEADERS := $(shell ls *.h)

PROG := wordfreak

$(PROG): $(OBJ) $(HEADERS)
	gcc -Wall $(OBJ) $(HEADERS) -o $(PROG)

%.o: %.c
	gcc -Wall -c $< -o $@

clean:
	rm *.o $(PROG)