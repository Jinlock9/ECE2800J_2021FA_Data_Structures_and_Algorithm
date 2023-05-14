#include <iostream>
#include <string>
#include "dlist.h"

using namespace std;

bool isInt(const string &s) {

    for(int i = 0; i < s.length(); i++) { //48 57
        int asc = (int)s.at(i);
        if((asc < 48 || asc > 57) && (asc != 45)) {
            return false;
        }
    }
    return true;
}

int main() {
    /*
    int a = 1;
    int* p = &a;
    int* q = p;
    cout<<*p<<" "<<*q<<endl;
    bool i = NULL;
    i = false;
    string in;
    string ss = "a";
    cout<<(int)ss.at(0)<<endl;
    cin>>in;
    while(in != "q") {
        if(isInt(in)) {
            cout<<stoi(in)<<endl;
        }
        else {
            cout<<in<<endl;
        }
        cin>>in;
    }

    Dlist<int>* a = new Dlist<int>;
    int* d = new int;
    int* e = new int;
    *d = 1;
    *e = 2;
    a->insertFront(d);
    a->insertFront(e);

    Dlist<int>* b = a;
    Dlist<int>* c(a);
    cout << "a: " << endl;
    int i = 0;
    while(i < 2) {
        int* temp = a->removeFront();
        cout << *temp << " ";
        a->insertBack(temp);
        i++;
    }
    cout << endl;
    cout << "b: " << endl;
    i = 0;
    while(i < 2) {
        int* temp = b->removeFront();
        cout << *temp << " ";
        b->insertBack(temp);
        i++;
    }
    cout << endl;
    cout << "c: " << endl;
    i = 0;
    while(i < 2) {
        int* temp = c->removeFront();
        cout << *temp << " ";
        c->insertBack(temp);
        i++;
    }
    cout << endl;


    delete a;
    //delete b;
     */

    int num;
    Dlist<int> *list = new Dlist<int>;
    cin >> num;
    for(int i = 0; i < num; i++) {
        int* in = new int;
        cin >> *in;
        list->insertFront(in);
    }
    int* out = list->removeBack();
    cout << *out << endl;
    delete out;
    delete list;

    /*
     * while(i <= stackSize) {
                        int* temp = stack->removeFront();
                        cout << *temp << " ";
                        stack->insertBack(temp);
                        i++;
                    }
     */
    /*
    string name;
    name = "Jinlock";
    cout << name << endl;
     */
    return 0;
}