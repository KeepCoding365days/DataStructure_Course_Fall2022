#include <iostream>
#include<string>
using namespace std;
template <class T>
class Stack {
	struct Node {
		T data;
		Node* next;


		Node() {
			data = NULL;
			next = 0;
		}
		Node(T data_1, Node* next_1) {

			data = data_1;
			next = next_1;
		}

	};
	Node* top;
	int size;
public:
	Stack() {
		top = nullptr;
		size = 0;
	}
	Stack(T val) {
		top = new Node(val, top);
		size = 1;
	}
	T Pop() {
		T val = top->data;
		top = top->next;
		size--;
		return val;
	}
	bool get_top(T& val) {
		bool check = true;
		if (size > 0) {
			val = top->data;
		}
		else {
			check = false;
		}
		return check;
	}
	bool Push(T val) {
		top = new Node(val, top);
		size++;
		return true;
	}
	bool isEmpty() {
		if (size == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void Print() {
		Node* ptr = top;

		while (ptr != nullptr) {
			cout << ptr->data;
			ptr = ptr->next;
		}

	}
	~Stack() {
		Node* ptr = top;
		while (ptr != nullptr) {
			Node* temp = ptr;
			ptr = ptr->next;
			delete temp;
		}
	}

};

void long_sum(Stack <int>& ResultStack) {
	string num1;
	string num2;

	Stack <int> stack1;
	Stack <int> stack2;


	cout << "Enter first Number:" << endl;
	getline(cin, num1);

	cout << "Enter second Number:" << endl;
	getline(cin, num2);

	for (int i = 0;i < num1.length();i++) {	//subtracting 48 bcz int(char) returns ascii value of char
		stack1.Push(int(num1[i]) - 48);
	}

	for (int i = 0;i < num2.length();i++) {	//subtracting 48 bcz int(char) returns ascii value of char
		stack2.Push(int(num2[i]) - 48);
	}

	if (num1.length() > num2.length()) {	//incase if size of num1 > num 2
		int temp = 0;
		while (!stack1.isEmpty()) {

			temp += stack1.Pop();
			if (!stack2.isEmpty()) {
				temp += stack2.Pop();
			}
			if (temp < 10) {
				ResultStack.Push(temp);
				temp = 0;
			}
			else if(!stack1.isEmpty()){
				ResultStack.Push(temp % 10);
				temp = temp / 10;
			}
			else {
				ResultStack.Push(temp);
			}
		}
	}

	else {
		int temp = 0;
		while (!stack2.isEmpty()) {


			temp += stack2.Pop();
			if (!stack1.isEmpty()) {
				temp += stack1.Pop();
			}

			if (temp < 10) {

				ResultStack.Push(temp);
				temp = 0;
			}

			else if(!stack2.isEmpty()){

				ResultStack.Push(temp % 10);
				temp = temp / 10;
			}
			else {
				ResultStack.Push(temp);
			}
		}
	}


}

int main() {
	Stack<int> result;
	long_sum(result);
	cout << "Sum of long integers is:";
	result.Print();
	cout << "." << endl;

	system("pause");
	return 0;

}
