#include <iostream>
using namespace std;
template<class T>
class SLL {
	struct Node {
		T data;
		Node* next;

		Node() {
			data = 0;
			next = nullptr;
		}

		Node(T val, Node* ptr) {
			data = val;
			next = ptr;
		}
	};
	Node* head;
	Node* tail;

public:
	SLL<T>() {
		head = nullptr;
		tail = nullptr;
	}
	void InsertAtHead(T val) {
		if (head == nullptr && tail == nullptr) {
  			head = new Node(val, nullptr);
			tail = head;
		}
		else {
			head = new Node(val, head);
		}
	}

	void InsertAtTail(T val) {
		if (head == nullptr && tail == nullptr) {
			tail = new Node(val, nullptr);
			tail = head;
		}
		else {
			tail->next = new Node(val, nullptr);
			tail = tail->next;
		}
	}

	void Print() {
		Node* ptr = head;
		while(ptr!=nullptr){
			cout << ptr->data << "\t";
			ptr = ptr->next;
		}
	}

	void EraseAtHead() {
		if (head != nullptr) {
				head = head->next;
			}
		}
	void EraseAtTail() {
		Node* ptr = head;
		while (ptr->next != tail) {
			ptr = ptr->next;
		}
		tail = ptr;
		ptr->next = nullptr;
	
	}
	~SLL() {
		Node* ptr = head;
		while (ptr != tail) {
			Node* temp = ptr;
			ptr = ptr->next;
			delete temp;
		}
	}
};
int main() {
	SLL<int> list;
	list.InsertAtHead(2);
	list.InsertAtHead(6);
	list.InsertAtHead(7);
	list.InsertAtTail(3);
	list.InsertAtTail(8);
	list.InsertAtTail(1);
	
	list.EraseAtHead();
	list.EraseAtTail();
	
	list.Print();
	return 0;
}
