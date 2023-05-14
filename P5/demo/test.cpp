#include <iostream>
#include <string>

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

    return 0;
}