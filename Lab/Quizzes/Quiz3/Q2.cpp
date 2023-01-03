#include <iostream>
using namespace std;
float get_hash(float n1,float n2) {
	if (n1 > n2) {
		
		return n1 / n2;
	}
	else { 
		return n2 / n1; }
}

int main() {
	float n1, n2;
	cout << "Please enter first number:";
	cin >> n1;
	cout << "Please enter second number:";
	cin >> n2;
	if (get_hash(n1, n2) == 1) {
		cout << "Both numbers are equal." << endl;
	}
	else {
		cout << "Numbers are not equal." << endl;
	}
	system("pause");
	return 0;
}