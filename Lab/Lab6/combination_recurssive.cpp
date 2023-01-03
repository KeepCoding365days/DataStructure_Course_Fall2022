#include <iostream>
using namespace std;

int fact(int);
double combination(int, int);

int main() {
	cout << "C(5,3)= "<<combination(5, 3);
	cout << endl;

	cout << "C(9,4)= "<<combination(9, 4);
	cout << endl;

	system("pause");
	return 0;
}

int fact(int N) {
	if (N == 0) {
		return 1;
	}
	else {
		return N * fact(N - 1);
	}
}
double combination(int N, int R) {
	if (N > R) {
		return (fact(N) / (fact(R) * fact(N - R)));
	}
	else {
		cout << "Wrong input";
		return 0;
	}
}