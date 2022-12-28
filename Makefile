.PHONY: all clean run
all: crtFile
run:
	./cond
	./mutex
	./fctl
	./packet

crtFile:
	gcc cond.c -o cond
	gcc mutex.c -o mutex
	gcc fctl.c -o fctl
	gcc packet.c -o packet

clean:
	rm -f *.o cond mutex fctl packet