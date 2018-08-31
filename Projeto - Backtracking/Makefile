all:
	gcc -o main -g ./src/*c -I./include -lm -std=c99
run:
	./main
valgrind:
	valgrind --tool=memcheck --leak-check=full ./main
test:
	./main < tests/1.in
