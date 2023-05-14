all: tree

tree: tree.o
	g++ -o tree tree.o

tree.o: tree.cpp
	g++ -c tree.cpp

tree.cpp: tree.txt
	cp tree.txt tree.cpp

clean:
	rm -f tree *.o
