#include <iostream>
using namespace std;
template<class T>
class SLL {
	struct Node {
		T data;
		Node* next;

		Node() {
			data = 0;
			next = 0;
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
		head = 0;
		tail = 0;
	}
	void InsertAtHead(T val) {
		if (head == 0 && tail == 0) {
			head = new Node(val, 0);
			tail = head;
		}
		else {
			head = new Node(val, head);
		}
	}

	void InsertAtTail(T val) {
		if (head == 0 && tail == 0) {
			tail = new Node(val, 0);
			tail = head;
		}
		else {
			tail->next = new Node(val, 0);
			tail = tail->next;
		}
	}

	void Print() {
		Node* ptr = head;
		while (ptr != 0) {
			cout << ptr->data << "->";
			ptr = ptr->next;
		}
		cout << "null";
	}

	void EraseAtHead() {
		if (head != 0) {
			head = head->next;
		}
	}
	void EraseAtTail() {
		Node* ptr = head;
		while (ptr->next != tail) {
			ptr = ptr->next;
		}
		tail = ptr;
		ptr->next = 0;

	}
	void unio(SLL<int>& a, SLL<int>& b) {
		Node* ptr = a.head;
		Node* ptr1 = b.head;
		Node* ptr2 = head;
		bool exist = false;
		while (ptr != 0) {
			exist = false;
			ptr2 = head;
			while (ptr2 != 0) {
				if (ptr2->data == ptr->data) {
					exist = true;
				}
				ptr2 = ptr2->next;
			}
			if (!exist) {
				Insert_sorted(ptr->data);
			}
			ptr = ptr->next;
		}

		while (ptr1 != 0) {
			exist = false;
			ptr2 = head;
			while (ptr2 != 0) {
				if (ptr2->data == ptr1->data) {
					exist = true;
				}
				ptr2 = ptr2->next;
			}
			if (!exist) {
				Insert_sorted(ptr1->data);
			}
			ptr1 = ptr1->next;
		}
	}

	void intersect(SLL<int>& a, SLL<int>& b) {
		Node* ptr = a.head;
		Node* ptr1 = b.head;
		Node* ptr2 = head;
		bool exist = false;
		bool common = false;
		while (ptr != 0) {
			common = false;
			exist = false;
			ptr2 = head;
			ptr1 = b.head;

			while (ptr1 != 0) {
				if (ptr1->data == ptr->data) {
					common = true;
				}
				
				ptr1 = ptr1->next;
			}
			while (ptr2 != 0) {
				if (ptr2->data == ptr->data) {
					exist = true;
				}
				ptr2 = ptr2->next;
			}
			if (!exist && common) {
				Insert_sorted(ptr->data);
			}
			ptr = ptr->next;
		}


	}

	void Insert_sorted(T val) {
		Node* ptr = head;
		Node* prev = head;
		if (head != 0) {
			while (ptr->data < val && ptr->next != 0) {
				prev = ptr;
				ptr = ptr->next;
			}
			if (ptr == head) {
				InsertAtHead(val);
			}
			else if (ptr == tail && ptr->data < val) {
				InsertAtTail(val);
			}
			else {
				prev->next = new Node(val, ptr);
			}
		}
		else {
			InsertAtHead(val);
		}
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
	SLL<int> a;
	SLL<int> b;
	a.InsertAtHead(3);
	a.InsertAtHead(8);
	a.InsertAtHead(5);
	a.InsertAtHead(1);
	a.InsertAtHead(4);

	b.InsertAtHead(9);
	b.InsertAtHead(3);
	b.InsertAtHead(7);
	b.InsertAtHead(2);
	b.InsertAtHead(10);
	b.InsertAtHead(5);
	b.InsertAtHead(8);
	b.InsertAtHead(1);
	b.InsertAtHead(6);
	b.InsertAtHead(4);
	cout << "A:" << endl;
	a.Print();
	cout << endl;
	cout << "B:" << endl;
	b.Print();
	cout << endl;

	SLL<int>c;

	SLL<int>d;

	//Did not return a SLL b.c.z if we are using as method then we can result store in that SLL, creating new SLL will not be waste of memory

	d.unio(a, b);
	cout << "Union of A & B is:" << endl;
	d.Print();
	cout << endl;
	

	cout << "Instersection of A & B is:" << endl;
	c.intersect(a, b);
	c.Print();

	system("pause");
	return 0;
}