GCFLAGS=-O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format -g
all: a.out
a.out: main.o lib.o 
	gcc $^
%.o: %.c lib.h
	gcc -c $(GCFLAGS) $< -o $@ -lm
clean:
	rm *.o*
rm_out:
	rm *.o
