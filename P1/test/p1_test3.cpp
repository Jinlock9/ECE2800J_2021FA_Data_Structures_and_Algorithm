#include <iostream>
#include <cmath>

using namespace std;

int sumSquares(int num);

int main() {
	for(int i = 1; i <= 100; i++) {
		if(sumSquares(i) == 1) {
			cout<<i<<endl;
		}
	}	
	return 0;
}

/*
 * sumSquares(int num) :
 * A function tests whether the integer is a sum of consecutive squares. 
 * An integer is a sum of consecutive squares if the integer is equal to m^2 + (m + 1)^2 + (m + 2)^2 + ... + n^2
 * for two integers 0 <= m <= n.
 */
int sumSquares(int num) {
	int halfNum = num / 2;

	for(int i = 0; i <= halfNum; i++) { // a number larger than half of the integer is not considered because its square is always larger than the integer
		int tempNum = num;
		int j = i;
		while(tempNum >= pow(j, 2)) {
			tempNum = tempNum - pow(j, 2);
			if(tempNum == 0) {
				return 1;
			}
			j++;
		}
	}

	return 0;
}
