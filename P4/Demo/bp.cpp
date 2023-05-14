#include <iostream>
#include <string>
#include "deck.h"
#include "player.h"
#include "rand.h"

using namespace std;

int main(int argc, char *argv[]) {

	/***************************************/
	/******** Initializing Process *********/
	/***************************************/

    int minimum = 5;
    int bankroll = stoi(argv[1]);
    int hands = stoi(argv[2]);
    string in(argv[3]);
    bool counting = false;
    if(in.compare("counting") == 0) {
        counting = true;
    }

    Deck d; // Initialize Deck
    // Initialize Player
    Player *p;
    if(counting) { // Player is a counting player
        p = get_Counting();
    }
    else {
        p = get_Simple();
    }
    Hand hp; // Initialize Player's Hand
    Hand hd; // Initialize Dealer's Hand

    // Shuffles the deck
    cout << "Shuffling the deck" << endl;
    int cut;
    for(int i = 0; i < 7; i++) {
        cut = get_cut();
        d.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
    if(counting) { // tell counting player that the deck is shuffled
        p->shuffled();
    }

    /***************************************/
	/*************  Simulation *************/
	/***************************************/

    int thishand = 0;
    if(bankroll < minimum) {
        cout << "Player has " << bankroll << " after " << thishand << " hands" << endl;
    }
    else {
        while(thishand < hands) { // There will be maximum [hands] rounds

            thishand++;

            Card temp; // Most current Player's card
            Card open; // Dealer's face-up card
            Card hole; // Dealer's hole card

            // Announce the hand
            cout << "Hand " << thishand << " bankroll " << bankroll << endl;

            // if there is less than 20 cards remaining in the deck, reshuffle
            if(d.cardsLeft() < 20) {
                cout << "Shuffling the deck" << endl;
                for(int i = 0; i < 7; i++) {
                    cut = get_cut();
                    d.shuffle(cut);
                    cout << "cut at " << cut << endl;
                }
                if(counting) { // tell counting player that the deck is shuffled
                    p->shuffled();
                }
            }

            // Player bets
            int wager = p->bet(bankroll, minimum);
            cout << "Player bets " << wager << endl;

            // Deal four cards

            // one face-up card to Player
            temp = d.deal();
            hp.addCard(temp);
            cout << "Player dealt " << SpotNames[temp.spot] << " of " << SuitNames[temp.suit] << endl;
            if(counting) { // expose the card to counting player
                p->expose(temp);
            }
            // one face-up card to Dealer
            open = d.deal();
            hd.addCard(open);
            cout << "Dealer dealt " << SpotNames[open.spot] << " of " << SuitNames[open.suit] << endl;
            if(counting) { // expose the card to counting player
                p->expose(open);
            }
            // one face-up card to Player
            temp = d.deal();
            hp.addCard(temp);
            cout << "Player dealt " << SpotNames[temp.spot] << " of " << SuitNames[temp.suit] << endl;
            if(counting) { // expose the card to counting player
                p->expose(temp);
            }
            // one face-down card to Dealer
            hole = d.deal();
            hd.addCard(hole);

            // If the player is dealt a natural 21
            if(hp.handValue().count == 21) {
                cout << "Player dealt natural 21" << endl;
                bankroll = (3 * wager) / 2;
            }
            else {
                bool bust = false;

                // if player wants to hit one more
                while(p->draw(open, hp)) {
                    temp = d.deal();
                    hp.addCard(temp);
                    cout << "Player dealt " << SpotNames[temp.spot] << " of " << SuitNames[temp.suit] << endl;
                    if(counting) { // expose the card to counting player
                        p->expose(temp);
                    }
                }
                cout << "Player's total is " << hp.handValue().count << endl;
                if(hp.handValue().count > 21) { // Player busts!
                    cout << "Player busts" << endl;
                    bankroll -= wager;
                    bust = true;
                }

                // If the player hasn't busted
                if(!bust) {
                    cout << "Dealer's hole card is " << SpotNames[hole.spot] << " of " << SuitNames[hole.suit] << endl;
                    if(counting) { // expose the card to counting player
                        p->expose(hole);
                    }

                    // Dealer plays
                    while(hd.handValue().count < 17) {
                        temp = d.deal();
                        hd.addCard(temp);
                        cout << "Dealer dealt " << SpotNames[temp.spot] << " of " << SuitNames[temp.suit] << endl;
                        if(counting) { // expose the card to counting player
                            p->expose(temp);
                        }
                    }
                    cout << "Dealer's total is " << hd.handValue().count << endl;

                    // Result
                    if(hd.handValue().count > 21) { // If dealer busts
                        cout << "Dealer busts" << endl;
                        bankroll += wager;
                    }
                    else {
                        if(hp.handValue().count > hd.handValue().count) {
                            cout << "Player wins" << endl;
                            bankroll += wager;
                        }
                        else if(hp.handValue().count < hd.handValue().count) {
                            cout << "Dealer wins" << endl;
                            bankroll -= wager;
                        }
                        else {
                            cout << "Push" << endl;
                        }
                    }
                }
            }

            if(bankroll < minimum) { // if there is too little money remaining
                break;
            }

            // Prepare for the next hand
            hp.discardAll();
            hd.discardAll();
        }

        cout << "Player has " << bankroll << " after " << thishand << " hands" << endl;
    }
    return 0;
}
