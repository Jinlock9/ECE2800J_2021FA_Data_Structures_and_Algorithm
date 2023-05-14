all: t

t: blackjack.o player.o hand.o deck.o card.o rand.o
	g++ -o t blackjack.o player.o hand.o deck.o card.o rand.o

blackjack.o: blackjack.cpp
	g++ -c blackjack.cpp

player.o: player.cpp
	g++ -c player.cpp

hand.o: hand.cpp
	g++ -c hand.cpp

deck.o: deck.cpp
	g++ -c deck.cpp

card.o: card.cpp
	g++ -c card.cpp

rand.o: rand.cpp
	g++ -c rand.cpp

clean:
	rm -f t *.o

tar: 
	tar cvf p4.tar deck.cpp hand.cpp player.cpp blackjack.cpp
