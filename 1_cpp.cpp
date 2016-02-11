#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> v;

	for (int i = 1; i < 1000; i++) {
		if (i % 3 == 0 || i % 5 == 0) {
			v.push_back(i);
		}
	}
	int sum;
	for_each (v.begin(), v.end(), [sum] (int i) {sum += i});

	cout << "Summan är: " << sum << endl;

	return 0;


} 