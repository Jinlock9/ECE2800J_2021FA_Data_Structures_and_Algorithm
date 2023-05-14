#include <iostream>
#include <string>
#include "dlist.h"

using namespace std;

struct Caller { // caller's information
    int timestamp;
    string name;
    string status;
    int duration;
};

int main() {

    Dlist<Caller> *list = new Dlist<Caller>; // list of every calls
    Dlist<Caller> *waitingP = new Dlist<Caller>; // list of platinum callers now waiting
    Dlist<Caller> *waitingG = new Dlist<Caller>; // list of gold callers now waiting
    Dlist<Caller> *waitingS = new Dlist<Caller>; // list of silver callers now waiting
    Dlist<Caller> *waitingR = new Dlist<Caller>; // list of regular callers now waiting
    int numCaller; // number of callers for initializing

    cin >> numCaller;

    for(int i = 0; i < numCaller; i++) { // intialize the list of every calls
        Caller *temp = new Caller;
        cin >> temp->timestamp >> temp->name >> temp->status >> temp->duration; // intialize the caller's information
        list->insertBack(temp);
    }

    int tick = 0;
    int progression = 0;

    while(true) {

        cout << "Starting tick #" << tick << endl; // beginning of each tick

        int flag = 0;

        while(flag == 0 && !(list->isEmpty())) { // find the callers of certain tick

            Caller *temp = list->removeFront();

            if(temp->timestamp == tick) {

                cout << "Call from " << temp->name << " a " << temp->status << " member" << endl;

                // put callers to corresponding waiting list
                if(temp->status == "platinum") waitingP->insertBack(temp);
                else if(temp->status == "gold") waitingG->insertBack(temp);
                else if(temp->status == "silver") waitingS->insertBack(temp);
                else waitingR->insertBack(temp);
            }
            else {
                list->insertFront(temp);
                flag = 1; // now there is no callers for this tick
            }
        }

        tick++;

        if(progression == 0) { // if the agent is servicing no one

            // priority of answering calls : platinum > gold > silver > regular
            if(!waitingP->isEmpty()) {

                Caller *answered = waitingP->removeFront();
                progression = answered->duration - 1;

                cout << "Answering call from " << answered->name << endl;

                delete answered;

            }
            else if(!waitingG->isEmpty()) {

                Caller *answered = waitingG->removeFront();
                progression = answered->duration - 1;

                cout << "Answering call from " << answered->name << endl;

                delete answered;

            }
            else if(!waitingS->isEmpty()) {

                Caller *answered = waitingS->removeFront();
                progression = answered->duration - 1;

                cout << "Answering call from " << answered->name << endl;

                delete answered;

            }
            else if(!waitingR->isEmpty()) {

                Caller *answered = waitingR->removeFront();
                progression = answered->duration - 1;

                cout << "Answering call from " << answered->name << endl;

                delete answered;

            }
            else if(!list->isEmpty()) { // there is no waiting callers but there will be

                continue;

            }
            else { // serviced every callers

                break;

            }

        }
        else { // the agent is now servicing

            progression--;
            continue;

        }

    } // end of while

    // free all the lists
    delete list;
    delete waitingP;
    delete waitingG;
    delete waitingS;
    delete waitingR;

    return 0;
}