#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

void triangleNum(int num); // triangle number
void powerNum(int num); // power number
void sumSquares(int num); // sum of consecutive squares
void abundantNum(int num); // abundant number

int main() {
	int num; // an integer tested. should be positive and no larger than 10,000,000.
	int testNum; // the test number, should between 1 and 4, inclusively.
	
	cout<<"Please enter the integer and the test choice: "; // initial prompt
	cin>>num>>testNum;

	while(num <= 0 || num > 10000000 || testNum < 1 || testNum > 4) { // if the input numbers are not matched with the requirements
		cout<<"Please enter the integer and the test choice: "; // receive new numbers
		cin>>num>>testNum;
	}
	
	//cout<<"No Problem"<<endl;

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

void powerNum(int num) {
	int numHalf = num / 2;
	int i = 2;
	int primeNum = 0;
	while(i <= numHalf) {
		int count = 0;
		if(num % i == 0) {
			int j = 1;
			while(j <= i) {
				if(i % j == 0) {
					count++;
				}
				j++;
			}
			if(count == 2) {
				primeNum++;
			}
		}
		i++;
	}
	if(primeNum == 1) {
		cout<<"Pass"<<endl;
	}
	else {
		cout<<"Fail"<<endl;
	}
	return;
}

void sumSquares(int num) {
	int numHalf = num / 2;
	for(int i = 0; i <= numHalf; i++) {
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

void abundantNum(int num) {
	int halfNum = num / 2;
	int sum = 0;
	for(int i = 1; i <= halfNum; i++) {
		if(num % i == 0) {
			sum = sum + i;
		}
	}
	if(num < sum) {
		cout<<"Pass"<<endl;
	}
	else {
		cout<<"Fail"<<endl;
	}

	return;
}
