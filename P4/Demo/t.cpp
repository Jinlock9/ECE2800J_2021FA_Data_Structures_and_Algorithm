#include <iostream>
#include "deck.h"

using namespace std;

Suit i2suit(int n) {
	switch(n) {
		case 0: return SPADES;
		case 1: return HEARTS;
		case 2: return CLUBS;
		default: return DIAMONDS;
	}
}

Spot i2spot(int n) {
	switch(n) {
		case 0: return TWO;
		case 1: return THREE;
		case 2: return FOUR;
		case 3: return FIVE;
		case 4: return SIX;
		case 5: return SEVEN;
		case 6: return EIGHT;
		case 7: return NINE;
		case 8: return TEN;
		case 9: return JACK;
		case 10: return QUEEN;
		case 11: return KING;
		default: return ACE;
	}
}

Deck::Deck() {
	
	Deck::reset();

}
    // EFFECTS: constructs a "newly opened" deck of cards:  first the
    // spades from 2-A, then the hearts, then the clubs, then the
    // diamonds.  The first card dealt should be the 2 of Spades.

void Deck::reset() {
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 13; j++) {
			int num = (13 * i) + j;
			deck[num].spot = i2spot(j);
			deck[num].suit = i2suit(i);
			cout<<num<<" : "<<SuitNames[i]<<" "<<SpotNames[j]<<endl;
		}
	}

	next = 0;

}
    // EFFECTS: resets the deck to the state of a "newly opened" deck
    // of cards:

void Deck::shuffle(int n) {

	Card temp[DeckSize];
	for(int i = 0; i < DeckSize; i++) {
		temp[i] = deck[i];
	}
	int left = 0;
	int right = n;
	int count = 0;

	while((left < n) || (right < DeckSize)) {

		if(right < DeckSize) {
			deck[count] = temp[right];
			right++;
			count++;
		}
		if(left < n) {
			deck[count] = temp[left];
			left++;
			count++;
		}

	}
    for(int i = 0; i < DeckSize; i++) {
		cout<<i<<" : "<<SuitNames[deck[i].suit]<<" "<<SpotNames[deck[i].spot]<<endl;
	}
}
    // REQUIRES: "n" is between 0 and 52, inclusive.

    // MODIFIES: this

    // EFFECTS: cut the deck into two segments: the first "n" cards,
    // called the "left", and the rest called the "right".  Note that
    // either right or left might be empty.  Then, rearrange the deck
    // to be the first card of the right, then the first card of the
    // left, the 2nd of right, the 2nd of left, and so on.  Once one
    // side is exhausted, fill in the remainder of the deck with the
    // cards remaining in the other side.  Finally, make the first
    // card in this shuffled deck the next card to deal.  For example,
    // shuffle(26) on a newly-reset() deck results in: 2-clubs,
    // 2-spades, 3-clubs, 3-spades ... A-diamonds, A-hearts.
    //
    // Note: if shuffle is called on a deck that has already had some
    // cards dealt, those cards should first be restored to the deck
    // in the order in which they were dealt, preserving the most
    // recent post-shuffled/post-reset state.

int main() {
	Deck d;
	cout<<endl;
	d.shuffle(26);
	d.reset();
	return 0;
}
