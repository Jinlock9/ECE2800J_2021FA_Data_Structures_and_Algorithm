all: p3

p3: error.o 
	g++ -o p3 error.o 

error.o: error.cpp
	g++ -c error.cpp

copy:
	cp error.txt error.cpp

clean:
	rm -f p3 *.o
