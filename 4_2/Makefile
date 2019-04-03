sum:sum.o
	gcc sum.o -o sum
sum.o:sum.s
	gcc -c sum.s -o sum.o
sum.s:sum.i
	gcc -S sum.i -o sum.s
sum.i:sum.c
	gcc -E sum.c -o sum.i

.PHONY:clean
clean:
	rm -f sum.i sum.s sum.o sum
