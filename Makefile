.PHONY: all clean run
all: crtFile
run:
	./cond
	./mutex
	./fctl
	./packet

crtFile:
	gcc -pthread cond.c -o cond
	gcc -pthread mutex.c -o mutex
	gcc -pthread fctl.c -o fctl
	gcc -pthread packet.c -o packet

clean:
	rm -f *.o cond mutex fctl packet