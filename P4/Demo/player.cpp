#include "player.h"
#include <iostream>

using namespace std;

int spot2v(Spot s) {
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

// SIMPLE PLAYER
// See player.h file to see REQUIRE, EFFECT, and MODIFY

class Simple : public Player {

 public:

    int bet(unsigned int bankroll, unsigned int minimum);

    bool draw(Card dealer, const Hand &player);

    void expose(Card c) {};

    void shuffled() {};

};

int Simple::bet(unsigned int bankroll, unsigned int minimum) {

    return minimum;

}

bool Simple::draw(Card dealer, const Hand &player) {

    if(player.handValue().soft) { // if the player has a "soft count"
        if(player.handValue().count <= 17) {
            return true;
        }
        if(player.handValue().count == 18) {
            if(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            return false;
        }
    }
    else {
        if(player.handValue().count <= 11) {
            return true;
        }
        else if(player.handValue().count == 12) {
            if(spot2v(dealer.spot) >= 4 && spot2v(dealer.spot) <= 6) {
                return false;
            }
            else {
                return true;
            }
        }
        else if(player.handValue().count >= 13 && player.handValue().count <= 16) {
            if(spot2v(dealer.spot) >= 2 && spot2v(dealer.spot) <= 6) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            return false;
        }
    }

}

// COUNTRING PLAYER
// See player.h file to see REQUIRE, EFFECT, and MODIFY

class Counting : public Simple {

    int count;

 public:

    Counting();
    // EFFECTS: constructs new counting player with 0 count

    int bet(unsigned int bankroll, unsigned int minimum);

    bool draw(Card dealer, const Hand &player);

    void expose(Card c);

    void shuffled();

};

Counting::Counting() : count(0) {};

int Counting::bet(unsigned int bankroll, unsigned int minimum) {

    if((count >= 2) && (bankroll >= (2 * minimum))) {
        return 2 * minimum;
    }
    else {
        return minimum;
    }

}

bool Counting::draw(Card dealer, const Hand &player) {

    return Simple::draw(dealer, player);

}

void Counting::expose(Card c) {

    switch(c.spot) {
		case TWO:
        case THREE:
		case FOUR:
        case FIVE:
        case SIX:
            count += 1;
            return;
		case TEN:
		case JACK:
        case QUEEN:
		case KING:
        case ACE:
            count -= 1;
            return;
		default:
            return;
	}

}

void Counting::shuffled() {

    count = 0;

}

// Player

static Simple simplePlayer;
static Counting countingPlayer;

Player *get_Simple() {

    return &simplePlayer;

}

Player *get_Counting() {

    return &countingPlayer;

}