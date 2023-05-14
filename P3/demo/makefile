all: p3

p3: p3.o
	g++ -o p3 p3.o

p3.o: p3.c
	g++ -c p3.cpp

zip:
	tar cvf p3.tar p3.cpp simulation.cpp simulation.h

copy:
	cp ss.txt simulation.cpp

clean:
	rm -f p3 *.o
