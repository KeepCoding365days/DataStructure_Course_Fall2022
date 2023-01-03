#include <iostream>
using namespace std;
template<class T>
class DLL {
	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node() {
			data = nullptr;
			next = nullptr;
			prev = nullptr;
		}

		Node(T val, Node* ptr, Node* ptr1) {
			data = val;
			prev = ptr1;
			next = ptr;

		}
	};
	Node* head;
	Node* tail;

public:
	DLL<T>() {
		head = nullptr;
		tail = nullptr;
	}
	DLL<T>(DLL& list) {
		Node* ptr = list.head;

		head = new Node(ptr->data, nullptr, nullptr);
		Node* ptr1 = head;

		while (ptr != nullptr) {
			if (ptr != list.tail) {
				ptr1->next = new Node(ptr->next->data, nullptr, nullptr);
				ptr1->next->prev = ptr1;
			}
			else {
				tail = ptr1;
			}
			ptr1 = ptr1->next;
			ptr = ptr->next;

		}
	}
	void InsertAtHead(T val) {
		if (head == nullptr) {
			head = new Node(val, nullptr, nullptr);
			tail = head;
		}
		else {
			Node* ptr = new Node(val, head, nullptr);
			head->prev = ptr;
			head = ptr;

		}
	}

	void InsertAtTail(T val) {
		if (head == nullptr && tail == nullptr) {
			tail = new Node(val, nullptr, nullptr);
			tail = head;
		}
		else {
			Node* ptr = new Node(val, nullptr, tail);
			tail->next = ptr;
			tail = ptr;
		}
	}

	void PrintForward() {
		Node* ptr = head;
		cout << "Printing from head to tail: " << endl;
		while (ptr != nullptr) {
			cout << ptr->data << "->";
			ptr = ptr->next;
		}
		cout << "null";
		cout << endl;
	}
	void PrintBackward() {
		Node* ptr = tail;
		cout << "Printing from tail to head: " << endl;
		while (ptr != nullptr) {
			cout << ptr->data << "->";
			ptr = ptr->prev;
		}
		cout << "null";
		cout << endl;
	}

	void EraseAtHead() {
		if (head != nullptr) {
			Node* ptr = head;
			head = head->next;
			head->prev = nullptr;
			delete ptr;
		}
	}
	void EraseAtTail() {
		Node* ptr = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete ptr;

	}
	int getSize() {
		int size = 0;
		Node* ptr = head;
		while (ptr != nullptr) {
			size++;
			ptr = ptr->next;
		}
		return size;
	}
	int getMiddle() {
		return (this->getSize() / 2);
	}
	bool isEmpty() {
		bool check = false;
		if (head == nullptr && tail == nullptr) {
			check = true;
		}
		return check;
	}
	int getMax();
	void InsertAfter(T val, T key) {
		Node* ptr = head;
		while (ptr->next != nullptr && ptr->data != key) {
			ptr = ptr->next;
		}

		if (ptr->next != nullptr) {
			Node* temp = new Node(val, ptr->next, ptr);
			ptr->next->prev = temp;
			ptr->next = temp;


		}
		else {
			ptr->next = new Node(val, nullptr, ptr);
			tail = ptr->next;

		}

	}

	void InsertBefore(T val, T key) {
		Node* ptr = tail;
		while (ptr->prev != nullptr && ptr->data != key) {
			ptr = ptr->prev;
		}

		if (ptr->prev != nullptr) {
			Node* temp = new Node(val, ptr, ptr->prev);
			ptr->prev->next = temp;
			ptr->prev = temp;


		}
		else {
			ptr->prev = new Node(val, ptr, nullptr);
			head = ptr->prev;

		}

	}
	void Merge(DLL& first_half, DLL& second_half) {
		this->head = first_half.head;
		this->tail = second_half.tail;
		first_half.tail->next = second_half.head;
		second_half.head->prev = first_half.tail;
	}
	~DLL() {
		Node* ptr = head;
		while (ptr != nullptr) {
			Node* temp = ptr;
			ptr = ptr->next;
			delete temp;
		}
	}
};
int DLL<int>::getMax() {
	int max = 0;
	Node* ptr = head;
	while (ptr != tail) {
		if (ptr->data > max) {
			max = ptr->data;
		}
		ptr = ptr->next;
	}
	return max;
}

int main() {
	DLL <int>list;
	list.InsertAtHead(5);
	list.InsertAtHead(1);
	list.InsertAtHead(12);
	list.InsertAtHead(16);
	list.InsertAtHead(23);
	list.InsertAtTail(40);
	list.EraseAtTail();
	list.EraseAtHead();
	list.PrintForward();
	list.InsertBefore(10, 17);
	cout << "After inserting 10 before 17:" << endl;
	list.PrintForward();
	list.InsertAfter(6, 1);
	cout << "After inserting 6 after 1:" << endl;
	list.PrintForward();
	list.PrintForward();
	list.PrintBackward();
	if (!list.isEmpty()) {
		cout << "Size is: " << list.getSize() << endl;
		cout << "Middle is: " << list.getMiddle() << endl;
	}
	cout << "Maximum is: " << list.getMax() << endl;
	DLL<int>list1;
	list1.InsertAtHead(100);
	list1.InsertAtHead(200);
	list1.InsertAtHead(300);

	DLL<int>list2(list);
	list.EraseAtHead();
	cout << "List 2:" << endl;
	list2.PrintForward();
	list2.PrintBackward();
	cout << "List:" << endl;
	list.PrintForward();
	list.PrintBackward();
	cout << "List1:" << endl;
	list1.PrintForward();
	cout << "List2=List+list1:" << endl;
	
	list.Merge(list, list1);
	list2.PrintForward();
	list2.PrintBackward();



	system("pause");
	return 0;
}
