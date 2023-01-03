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
	T val_top() {
		if (size > 0)
			return top->data;
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
	int getSize() {
		return size;
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

void SortStack(Stack<int>& stack1) {
	Stack <int>temp;
	//cout << stack1.getSize();
	int check;
	bool check1, done;
	while (stack1.getSize() > 0) {

		temp.Push(stack1.Pop());
	}

	stack1.Push(temp.Pop());
	//cout << temp.getSize();
	//temp.Print();
	temp.get_top(check);
	while (temp.getSize() != 0) {
		if (check >= stack1.val_top()) {
			stack1.Push(temp.Pop());
		}

		else {
			//cout << 5;
			int temp1 = check;
			temp.Pop();
			temp.Push(stack1.Pop());
			check1 = stack1.isEmpty();
			done = false;
			while (!check1 && !done) {
				while (!stack1.isEmpty() && temp1 < stack1.val_top()) {
					temp.Push(stack1.Pop());
				}
				done = true;
				check1 = stack1.isEmpty();
			}
			stack1.Push(temp1);
		}
		temp.get_top(check);
	}
}

int main() {
	int input = 0;
	Stack <int> list;

	cout << "Please enter list of numbers to sort. Enter -1 to exit:" << endl;
	cin >> input;
	while (input != -1) {
		list.Push(input);
		cin >> input;
	}
	SortStack(list);
	cout << "Stack sorted in descending form:" << endl;
	list.Print();

	system("pause");
	return 0;

}
