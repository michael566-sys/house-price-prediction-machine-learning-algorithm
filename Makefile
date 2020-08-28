all: program
 
program: fourth.o
	gcc -o fourth fourth.o
 
clean:
	rm -rf fourth.o fourth