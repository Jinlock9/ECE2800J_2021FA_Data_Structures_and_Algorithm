#include "deck.h"

Suit i2suit(int n) {
	switch(n) {
		case 0: return SPADES;
		case 1: return HEARTS;
		case 2: return CLUBS;
		default: return DIAMONDS;
	}
}
// EFFECTS: returns the SUIT according to its value

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
// EFFECTS: returns the SPOT according to its value

// See deck.h file to see REQUIRE, EFFECT, and MODIFY

Deck::Deck() {

	Deck::reset();

}

void Deck::reset() {
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 13; j++) {
			int num = (13 * i) + j;
			deck[num].spot = i2spot(j);
			deck[num].suit = i2suit(i);
		}
	}

	next = 0;

}

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

    next = 0;

}

Card Deck::deal() {

    if(next >= DeckSize) {
        DeckEmpty e;
        throw e;
    }

    int temp = next;
    next++;

    return deck[temp];

}

int Deck::cardsLeft() {
    
    return DeckSize - next;

}
