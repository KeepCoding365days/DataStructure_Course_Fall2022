#include <iostream>
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
		top = new Node(val,top);
		size = 1;
	}
	T Pop() {
		T val= top->data;
		top = top->next;
		size--;
		return val;
	}
	bool get_top(T & val) {
		bool check=true;
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
		cout << "Elements of stack: " << endl;
		while (ptr != nullptr) {
			cout << ptr->data << endl;
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


int main() {
	Stack <int> S;
	S.Push(5);
	S.Push(6);
	S.Push(7);
	S.Push(8);
	S.Pop();
	S.Print();
	cout << "At top:";
	int temp;
	S.get_top(temp);
	cout << temp << endl;
	system("pause");
	return 0;

}
