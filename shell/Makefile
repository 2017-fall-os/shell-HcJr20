all: test

CFLAGS = -g -O2

test: main.o tokenizer.o
	cc -o test main.o tokenizer.o 
clean:
	rm -f  *.o test main.exe
demo: test
	./test
