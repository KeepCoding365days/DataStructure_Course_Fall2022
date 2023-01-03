#include <iostream>
#include<string>
using namespace std;

bool is_palindrome(string);
bool is_palindrome(string, int);

int main() {
	string a;
	cout << "Enter a string to check if it is palindrome or not:";
	cin >> a;
	if (is_palindrome(a, 0)) {
		cout << a << " is a palindrome." << endl;
	}
	else {
		cout << a << " is not a palindrome." << endl;
	}
	system("pause");
	return 0;
}
bool is_palindrome(string a) {
	return is_palindrome(a, 0);

}
bool is_palindrome(string word, int idx) {
	bool check = false;
	if (idx == word.length() - 1) {
		check = true;
		return check;
	}
	else {
		check = (word[idx] == word[word.length()-1-idx]);
		if (check) {
			return is_palindrome(word, idx+1);
		}
		return check;
	}
}