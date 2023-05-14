#include <iostream>
#include <string>
#include "dlist.h"

using namespace std;

bool isInt(const string &s)
// EFFECT: return true if the string is only consisted of integers (which means the string is integer)
{

    int length = (int) s.length(); // length of the string

    for(int i = 0; i < length; i++) {
        int asc = (int)s.at(i); // ascii code of each charater
        if((asc < 48 || asc > 57) && (asc != 45)) { // ascii code of 0 ~ 9 : 48 ~ 57, - : 45 (integer can be negative)
            return false;
        }
    }
    return true;
}

int main() {

    string in; // input string
    Dlist<int> *stack = new Dlist<int>; // intialize the stack with integers
    int stackSize = 0; // initialize the stack size

    cin>>in;
    while(in != "q") { // q: exit the calculator

        if(isInt(in) && in != "-") { // if input string is integer

            int* num = new int; // new integer object
            *num = stoi(in);
            stack->insertFront(num); // put integer into stack
            stackSize++;

        }
        else if(in.length() > 1){ // except for integers, command is not longer than a single character

            cout << "Bad input" << endl;

        }
        else {

            switch(in.at(0)) {

                case '+': {

                    if(stackSize >= 2) { // only valid with at least two integers
                        int* sum = new int;
                        int* a = stack->removeFront(); // get first element
                        int* b = stack->removeFront(); // get second element
                        *sum = *a + *b; // sum of two integers
                        stack->insertFront(sum);
                        delete a;
                        delete b;
                        stackSize--; // there will be one less integers in the stack than just before
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case '-': {

                    if(stackSize >= 2) { // only valid with at least two integers
                        int* a = stack->removeFront(); // get first element
                        int* b = stack->removeFront(); // get second element
                        int* diff = new int;
                        *diff = *b - *a; // difference of two integers
                        stack->insertFront(diff);
                        delete a;
                        delete b;
                        stackSize--; // there will be one less integers in the stack than just before
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case '*': {

                    if(stackSize >= 2) { // only valid with at least two integers
                        int* a = stack->removeFront(); // get first element
                        int* b = stack->removeFront(); // get second element
                        int* product = new int;
                        *product = *a * *b;  // product of two integers
                        stack->insertFront(product);
                        delete a;
                        delete b;
                        stackSize--; // there will be one less integers in the stack than just before
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case '/': {

                    if(stackSize >= 2) { // only valid with at least two integers
                        int* dividor = stack->removeFront(); // get first element
                        if(*dividor == 0) { // we cannot divide integer with zero
                            cout << "Divide by zero" << endl;
                            stack->insertFront(dividor); // put back into stack
                        }
                        else {
                            int* num = stack->removeFront(); // get second element
                            int* result = new int;
                            *result = *num / *dividor;
                            stack->insertFront(result);
                            delete dividor;
                            delete num;
                            stackSize--; // there will be one less integers in the stack than just before
                        }
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case 'n': {

                    if(stackSize >= 1) { // only valid with at least one integers
                        int* temp = stack->removeFront();
                        int* result = new int;
                        *result = (-1) * *temp; // negation of the integer
                        stack->insertFront(result);
                        delete temp;
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case 'd': {

                    if(stackSize >= 1) {  // only valid with at least one integers
                        int* temp = stack->removeFront();
                        int* dup = new int;
                        *dup = *temp; // duplicate the integer
                        stack->insertFront(temp);
                        stack->insertFront(dup);
                        stackSize++; // there will be one more integers in the stack than just before
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case 'r': {

                    if(stackSize >= 2) { // only valid with at least two integers
                        int* first = stack->removeFront();
                        int* second = stack->removeFront();
                        // reverse the order
                        stack->insertFront(first);
                        stack->insertFront(second);
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case 'p': {

                    if(stackSize >= 1) { // only valid with at least one integers
                        int* temp = stack->removeFront();
                        cout << *temp << endl; // print the integer
                        stack->insertFront(temp); // put back into stack
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }

                    break;

                }
                case 'c': {

                    while(!stack->isEmpty()) { // clear all elements in the stack
                        int* trash = stack->removeFront();
                        delete trash;
                    }

                    stackSize = 0; // now there is no elements in the stack

                    break;

                }
                case 'a': {

                    int i = 1;
                    while(i <= stackSize) {
                        int* temp = stack->removeFront(); // get first element
                        cout << *temp << " "; // print it
                        stack->insertBack(temp); // put back into stack
                        i++;
                    }
                    cout << endl;

                    break;

                }
                default: { // commands other than -+*/ndrpcda are invalid

                    cout << "Bad input" << endl;
                    break;

                }
            } // end of switch

        } // end of else

        cin>>in;

    } // end of while

    delete stack; // free the stack!

    return 0;

}