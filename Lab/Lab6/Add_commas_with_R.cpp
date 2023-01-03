#include <iostream>
#include <string>
using namespace std;

string add_commas(int,string,int);
string add_commas(int);

int main() {
	int num;
	cout << "Please enter a number:";
	cin >> num;
	cout << "After adding commas: " << add_commas(num)<<endl;
	system("pause");
	return 0;
}
string add_commas(int num) {
	string a = ".";
	return add_commas(num, a, 0);
}
string add_commas(int num, string str,int idx) {
	if (num <= 0) {
		return str;
	}
	else {
		if (idx % 3 != 0 || str[0] == ','||idx==0) {
			str = char((num % 10)+48) + str;
			num = num / 10;
			idx++;
			return add_commas(num, str, idx);
		}
		else {
			str = ',' + str;
			return add_commas(num, str, idx);
		}
	}
}