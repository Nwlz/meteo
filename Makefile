all: main

main: main.o functions.o options.o display.o
	gcc main.o functions.o options.o display.o -o main

main.o: main.c head.h
	gcc -c main.c

functions.o: functions.c head.h
	gcc -c functions.c
    
struct.o: options.c head.h
	gcc -c options.c
    
display.o: display.c head.h
	gcc -c display.c

clean:
	rm -f main main.o functions.o options.o display.o
