#include <iostream>
#include <string>
#include "dlist.h"

using namespace std;

bool isInt(const string &s) {

    for(int i = 0; i < s.length(); i++) {
        int asc = (int)s.at(i);
        if((asc < 48 || asc > 57) && (asc != 45)) {
            return false;
        }
    }
    return true;
}

int main() {

    string in;
    Dlist<int> *stack = new Dlist<int>;
    int stackSize = 0;

    cin>>in;
    while(in != "q") {
        if(isInt(in) && in != "-") {
            stack->insertFront(reinterpret_cast<int *>(stoi(in)));
            stackSize++;
        }
        else if(in.length() > 1){
            cout << "Bad input" << endl;
        }
        else {
            switch(in.at(0)) {
                case '+': {
                    if(stackSize >= 2) {
                        int a = *stack->removeFront();
                        cout<<a<<endl;
                        int b = *stack->removeFront();
                        cout<<b<<endl;
                        int sum = a + b;
                        cout<<sum<<endl;
                        stack->insertFront(&sum);
                        stackSize--;
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case '-': {
                    if(stackSize >= 2) {
                        int subtractor = *stack->removeFront();
                        int result = *stack->removeFront() - subtractor;
                        stack->insertFront(&result);
                        stackSize--;
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case '*': {
                    if(stackSize >= 2) {
                        int product = *stack->removeFront();
                        product *= *stack->removeFront();
                        stack->insertFront(&product);
                        stackSize--;
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case '/': {
                    if(stackSize >= 2) {
                        int dividor = *stack->removeFront();
                        if(dividor == 0) {
                            cout << "Divide by zero" << endl;
                        }
                        else {
                            int result = *stack->removeFront() / dividor;
                            stack->insertFront(&result);
                            stackSize--;
                        }
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case 'n': {
                    if(stackSize >= 1) {
                        int temp = (-1) * (*stack->removeFront());
                        stack->insertFront(&temp);
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case 'd': {
                    if(stackSize >= 1) {
                        int temp = *stack->removeFront();
                        stack->insertFront(&temp);
                        stack->insertFront(&temp);
                        stackSize++;
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case 'r': {
                    if(stackSize >= 2) {
                        int first = *stack->removeFront();
                        int second = *stack->removeFront();
                        stack->insertFront(&first);
                        stack->insertFront(&second);
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case 'p': {
                    if(stackSize >= 1) {
                        int temp = *stack->removeFront();
                        cout << temp << endl;
                        stack->insertFront(&temp);
                    }
                    else {
                        cout << "Not enough operands" << endl;
                    }
                    break;
                }
                case 'c': {
                    while(!stack->isEmpty()) {
                        int trash = *stack->removeFront();
                    }
                    stackSize = 0;
                    break;
                }
                case 'a': {
                    Dlist<int> *temp = new Dlist<int>;
                    temp = stack;
                    if(temp->isEmpty()) {
                        cout << endl;
                    }
                    else {
                        while(!temp->isEmpty()) {
                            cout << *temp->removeFront() << endl;
                        }
                    }
                    delete temp;
                    break;
                }
                default:
                    cout << "Bad input" << endl;
                    break;
            }
        }
        cin>>in;
    }

    return 0;
}