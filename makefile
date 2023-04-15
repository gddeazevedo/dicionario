all: src/*/*.h src/*/*.c src/main.c
	cc src/*/*.h src/*/*.c src/main.c -o run.out
