#include "hand.h"

int spot2vH(Spot s) { // Not consider ACE
	switch(s) {
		case TWO: return 2;
		case THREE: return 3;
		case FOUR: return 4;
		case FIVE: return 5;
		case SIX: return 6;
		case SEVEN: return 7;
		case EIGHT: return 8;
		case NINE: return 9;
		default: return 10;
	}
}
// EFFECTS: returns the value according to its spot

// See hand.h file to see REQUIRE, EFFECT, and MODIFY

Hand::Hand() {

    Hand::discardAll();

}

void Hand::discardAll() {

    curValue.count = 0;
    curValue.soft = false;

}
void Hand::addCard(Card c) {

    if(c.spot == ACE) { // if the sport is ACE
        if(curValue.soft) {
            if(curValue.count + 1 <= 21) {
                curValue.count += 1;
            }
            else {
                curValue.soft = false;
                curValue.count -= 10; // Now all ACEs worth 1
                curValue.count += 1;
            }
        }
        else {
            if(curValue.count + 11 <= 21) {
                curValue.count += 11;
                curValue.soft = true;
            }
            else {
                curValue.count += 1;
            }
        }
    }
    else { // If the spot is other than ACE
        if(curValue.soft) { // if the player has a soft count
            if(curValue.count + spot2vH(c.spot) <= 21) {
                curValue.count += spot2vH(c.spot);
            }
            else {
                curValue.soft = false;
                curValue.count -= 10; // Now ACE worth 1
                curValue.count += spot2vH(c.spot);
            }
        }
        else { // if the player has a hard count
            curValue.count += spot2vH(c.spot);
        }
    }

}

HandValue Hand::handValue() const {

    return curValue;

}

