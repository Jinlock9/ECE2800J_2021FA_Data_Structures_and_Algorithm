/*
 * VE280
 * Jinlock Choi 520370990012
 * Project One: Integers!
 */

#include <iostream>
#include <cmath>

using namespace std;

int triangleNum(int num);

int main() {
	for(int i = 1; i <= 100; i++) {
		if(triangleNum(i) == 1) {
			cout<<i<<endl;
		}
	}
	return 0;
}

/*
 * triangleNum(int num) :
 * A function tests whether the integer is a triangle number or not.
 * An integer is a triangle number if it equals n(n + 1)/2, where n is an integer.
 */
int triangleNum(int num) {
	for(int i = 1; i <= num; i++) {
		if(num == ((i * (i + 1)) / 2)) { // it is a triangle number
			return 1;
		}
	}

	return 0;
}
