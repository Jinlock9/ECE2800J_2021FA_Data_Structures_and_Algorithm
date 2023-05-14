all: t

t: t.o
	g++ -Wall -o t t.o

t.o: t.cpp
	g++ -c t.cpp

copy: t.txt
	cp t.txt t.cpp

clean:
	rm -f t *.o
