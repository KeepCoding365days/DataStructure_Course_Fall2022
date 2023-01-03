#include<iostream>
#include<string>
using namespace std;

bool is_sorted(int[],int,int);
int main() {
	int input = 0,size=0;
	int arr[100];
	cout << "Please enter numbers of array. Enter -99 to exit:"<<endl;
	for (int i = 0;input != -99;i++) {
		cin >> input;
		if (input != -99) {
			arr[i] = input;
			size++;
		}
		
	}
	
	if (is_sorted(arr, size, 0)) {
		cout << "Array is sorted." << endl;
	}
	else {
		cout << "Array is not sorted." << endl;
	}
	system("pause");
	return 0;
}

bool is_sorted(int arr[],int size,int idx) {
	bool check;
	if (idx + 1 < size) {
		check = (arr[idx] <= arr[idx + 1]);
	}
	if (idx == size - 2 || check == false) {
		return check;
	}
	else {
		return is_sorted(arr, size, idx + 1);
	}
}