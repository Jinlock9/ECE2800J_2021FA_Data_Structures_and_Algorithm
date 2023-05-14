#include <iostream>
#include <cmath>

using namespace std;

int powerNum(int num);

int main() {
	for(int i = 1; i <= 1000; i++) {
		if(powerNum(i) == 1) {
			cout<<i<<endl;
		}
	}		
	return 0;
}

/*
 * powerNum(int num) :
 * A function test whether the integer is a power number or not.
 * An integer is a power number if it equals m^n, where m and n are both integers and n >= 2.
 * If the integer has only one prime factor except for 1 and itself, then it is a power number.
 */
int powerNum(int num) {
	int halfNum = num / 2;
	int i = 2; // excluding 1 from prime factors
	int primeNum = 0; // the number of prime factors
	
	// while loop searching for prime factors
	while(i <= halfNum) { // a number larger than half of the integer is not considered because its square is always larger than the integer
		int count = 0;
		if(num % i == 0) { // searching for proper divisor <i> of the integer
			int j = 1;	
			while(j <= i) {
				if(i % j == 0) { // count the number of the proper divisor of the proper divisor <i>
					count++;
				}
				j++;
			}
			if(count == 2) { // if count == 2, it is a prime factor: the one has prime factors 1 and itself
				primeNum++;
			}
		}
		i++;
	}

	if(primeNum == 1) { // it is a power number
		return 1;
	}
	else {
		return 0;
	}
}
