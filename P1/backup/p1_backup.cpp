/*
 * VE280
 * Jinlock Choi 520370990012
 * Project One: Integers!
 */

#include <iostream>
#include <cmath>

using namespace std;

void triangleNum(int num);
void powerNum(int num);
void sumSquares(int num);
void abundantNum(int num);

int main() {
	int num; // an integer tested. (1) should be positive and no larger than 10,000,000.
	int testNum; // the test number,(2) should between 1 and 4, inclusively.
	
	cout<<"Please enter the integer and the test choice: "; // initial prompt
	cin>>num>>testNum;

	while(num <= 0 || num > 10000000 || testNum < 1 || testNum > 4) { // if the input numbers are not matched with the requirements (1) or (2)
		cout<<"Please enter the integer and the test choice: "; // receive new numbers
		cin>>num>>testNum;
	}
	
	// run functions according to the test number
	if(testNum == 1) {
		triangleNum(num); // test whether the integer is a triangle number or not
	}
	else if(testNum == 2) {
		powerNum(num); // test whether the integer is a power number or not
	}
	else if(testNum == 3) {
		sumSquares(num); // test whether the integer is a sum of consecutive squares or not
	}
	else { // if testNum == 4
		abundantNum(num); // test whether the integer is an abundant number or not
	}
	
	return 0;
}

/*
 * triangleNum(int num) :
 * A function tests whether the integer is a triangle number or not.
 * An integer is a triangle number if it equals n(n + 1)/2, where n is an integer.
 */
void triangleNum(int num) {
	for(int i = 1; i <= num; i++) {
		if(num == ((i * (i + 1)) / 2)) { // it is a triangle number
			cout<<"Pass"<<endl;
			return;
		}
	}

	cout<<"Fail"<<endl;
	return;
}

/*
 * powerNum(int num) :
 * A function test whether the integer is a power number or not.
 * An integer is a power number if it equals m^n, where m and n are both integers and n >= 2.
 * If the integer has only one prime factor except for 1 and itself, then it is a power number.
 */
void powerNum(int num) {
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
		cout<<"Pass"<<endl;
	}
	else {
		cout<<"Fail"<<endl;
	}
	return;
}

/*
 * sumSquares(int num) :
 * A function tests whether the integer is a sum of consecutive squares. 
 * An integer is a sum of consecutive squares if the integer is equal to m^2 + (m + 1)^2 + (m + 2)^2 + ... + n^2
 * for two integers 0 <= m <= n.
 */
void sumSquares(int num) {
	int halfNum = num / 2;

	for(int i = 0; i <= halfNum; i++) { // a number larger than half of the integer is not considered because its square is always larger than the integer
		int tempNum = num;
		int j = i;
		while(tempNum >= pow(j, 2)) {
			tempNum = tempNum - pow(j, 2);
			if(tempNum == 0) {
				cout<<"Pass"<<endl;
				return;
			}
			j++;
		}
	}

	cout<<"Fail"<<endl;
	return;
}

/*
 * abundantNum(int num) :
 * A function tests whether the integer is an abundant number or not.
 * An integer is an abundant number if the sum of its proper divisors exceeds the integer.
 */
void abundantNum(int num) {
	int halfNum = num / 2;
	int sum = 0;
	
	// for loop searching for proper divisors
	for(int i = 1; i <= halfNum; i++) { // itself is not considered as a proper divisor
		if(num % i == 0) {
			sum = sum + i;
		}
	}

	if(num < sum) { // sum of proper divisors exceeds the integer
		cout<<"Pass"<<endl;
	}
	else {
		cout<<"Fail"<<endl;
	}

	return;
}
