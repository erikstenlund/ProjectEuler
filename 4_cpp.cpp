#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

bool isPalindrome(int nbr) {
	ostringstream oss;
	oss << nbr;
	string strNbr = oss.str();

	for (int i = 0; i < strNbr.size() / 2; i++) {
    	if (strNbr[i] != strNbr[strNbr.size() - 1 - i]) {
			return false;
    		
    	}
	}
	
	return true;
}

int main() {
	int largest = 0;

	for (int i = 999; i > 100; i--) {
		for (int j = i; j > 100; j--) {
			int tmp = i * j;
			
			if (isPalindrome(tmp) && tmp > largest)
				largest = tmp;
		}
	}

	cout << "Largest palindrome product: " << largest << endl;
	
	
}