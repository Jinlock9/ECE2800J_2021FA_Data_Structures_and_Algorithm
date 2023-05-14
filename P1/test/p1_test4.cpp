#include <iostream>
#include <cmath>

using namespace std;

int abundantNum(int num);

int main() {
	for(int i = 1; i <= 100; i++) {
		if(abundantNum(i) == 1) {
			cout<<i<<endl;
		}
	}	
	return 0;
}

/*
 * abundantNum(int num) :
 * A function tests whether the integer is an abundant number or not.
 * An integer is an abundant number if the sum of its proper divisors exceeds the integer.
 */
int abundantNum(int num) {
	int halfNum = num / 2;
	int sum = 0;
	
	// for loop searching for proper divisors
	for(int i = 1; i <= halfNum; i++) { // itself is not considered as a proper divisor
		if(num % i == 0) {
			sum = sum + i;
		}
	}

	if(num < sum) { // sum of proper divisors exceeds the integer
		return 1;
	}
	else {
		return 0;
	}

}
