#include <iostream>
using namespace std;
bool is_even_sum(int num) {
	int sum = 0;
	bool check = false;
	if (num < 10) {
		if (num % 2 == 0) {
			check = true;
		}
	}
	else {
		while (num > 0) {
			sum += num % 10;
			num = num / 10;
		}
		sum += num;
		if (sum % 2 == 0) {
			check = true;
		}
	}
	return check;
}
template<class T>
class CLL {

	struct Node {
		T data;
		Node* next;

		Node() {
			data = nullptr;
			next = nullptr;
		}

		Node(T val, Node* ptr) {
			data = val;
			next = ptr;

		}
	};
	Node* tail;

	class ListIterator {
	public:
		Node* current;

		ListIterator() {
			current = nullptr;
		}

		T operator * () {
			return current->data;
		}
		ListIterator& operator++() {
			ListIterator temp = *this;
			if (current) {
				current = current->next;
			}

			return *(this);
		}
		ListIterator& operator ++ (int) {
			return (++ * this);
		}
		bool operator ==(ListIterator obj) {
			bool check = false;
			if (this->current == obj.current) {
				check = true;
			}
			return check;
		}
		bool operator !=(ListIterator obj) {
			bool check = true;
			if (this->current == obj.current) {
				check = false;
			}
			return check;
		}


	};
public:
	typedef ListIterator Iterator;
	CLL<T>() {
		tail = nullptr;
	}
	CLL<T>(CLL<T>& list) {
		tail = new Node(list.tail->data, nullptr);
		Node* ptr = list.tail;
		Node* ptr1 = tail;
		while (ptr->next != list.tail) {
			ptr1->next = new Node(ptr->next->data, nullptr);
			ptr1 = ptr1->next;
			ptr = ptr->next;
		}
		ptr1->next = tail;

	}
	Iterator begin() {
		Iterator obj;
		obj.current = tail->next;
		return obj;
	}
	Iterator end() {
		Iterator obj;
		obj.current = tail;
		while (obj.current != tail) {
			obj++;
		}
		return obj;
	}

	void InsertAtTail(T val) {
		if (tail == nullptr) {
			tail = new Node(val, nullptr);
			tail->next = tail;

		}
		else {
			Node* ptr = new Node(val, nullptr);
			ptr->next = tail->next;
			tail->next = ptr;
			tail = ptr;
		}
	}

	void sum_product();
	void ReverseCLL() {
		Node* ptr = tail;
		Node* ptr1 = tail->next;
		while (ptr1 != tail) {
			Node* temp = ptr1->next;
			ptr1->next = ptr;
			ptr = ptr1;
			ptr1 = temp;

		}
		Node* temp = tail->next;
		tail->next = ptr;
		tail = temp;

	}
	void MoveOccurrence(T val) {
		bool completed = false;
		Node* ptr = tail->next;
		while (ptr->next != tail) {

			if (ptr->next->data == val) {
				Node* temp = ptr->next;
				ptr->next = ptr->next->next;
				temp->next = tail->next;
				tail->next = temp;
				tail = temp;
			}
			completed = true;
			Node* temp = ptr->next;

			while (temp != tail) {

				if (temp->data != val) {
					completed = false;
				}
				temp = temp->next;
			}
			if (ptr->next->data != val || completed) {
				ptr = ptr->next;
			}

		}
	}
	int size() {
		int size = 0;
		if (tail != nullptr) {
			Node* ptr = tail->next;
			while (ptr != tail) {
				size++;
				ptr = ptr->next;
			}
			size++;
		}
		return size;
	}
	bool isEmpty() {
		bool check = false;
		if (tail == nullptr) {
			check = true;
		}
		return check;
	}

	void InsertAfter(T val, T key) {
		if (!isEmpty()) {
			Node* temp = new Node(val, nullptr);
			Node* ptr = tail->next;
			while (ptr != tail && ptr->data != key) {
				ptr = ptr->next;
			}
			temp->next = ptr->next;
			ptr->next = temp;
			if (ptr == tail) {
				tail = temp;
			}
		}
	}
	void InsertBefore(T val, T key) {
		Node* temp = new Node(val, nullptr);
		if (!isEmpty()) {
			Node* ptr = tail->next;
			if (ptr->data != key) {
				while (ptr != tail && ptr->next->data != key) {
					ptr = ptr->next;
				}
				temp->next = ptr->next;
				ptr->next = temp;
				if (ptr == tail) {
					tail = temp;
				}
			}
			else {
				tail->next = temp;
				temp->next = ptr;

			}
		}
	}
	void DeleteDuplicates() {
		Node* ptr = tail->next;
		while (ptr != tail) {
			if (ptr->next->data == ptr->data) {
				Node* temp = ptr->next;
				ptr->next = ptr->next->next;
				delete temp;
			}
			ptr = ptr->next;
		}
	}
	void Print() {
		Node* ptr = tail->next;
		cout << "Printing CLL:" << endl;
		while (ptr != tail) {
			cout << ptr->data << "->";
			ptr = ptr->next;
		}
		cout << ptr->data << "->";
		cout << "null";
		cout << endl;
	}
	~CLL() {
		Node* ptr = tail->next;
		Node* temp;
		while (ptr != tail) {
			temp = ptr->next;
			delete ptr;
			ptr = temp;
		}
		delete ptr;
	}
};

void CLL<int>::sum_product() {
	Node* ptr = tail->next;
	int sum = 0, multiple = 1;
	bool reach = false;

	while (ptr != tail || !reach) {

		if (is_even_sum(ptr->next->data)) {
			Node* temp = ptr->next;
			ptr->next = ptr->next->next;
			if (temp == tail) {
				tail = ptr;
				reach = true;
			}
			delete temp;
		}
		ptr = ptr->next;
	}
	//checking for head
	if (is_even_sum(tail->next->data)) {
		Node* temp = tail->next;
		tail->next = temp->next;
		delete temp;
	}

	ptr = tail->next;
	while (ptr != tail) {
		sum += ptr->data;
		multiple *= ptr->data;
		ptr = ptr->next;
	}
	sum += ptr->data;
	multiple *= ptr->data; //for tail

	cout << "Sum is:" << sum << endl;
	cout << "Multiple is:" << multiple << endl;

}

int main() {
	CLL<int> list;
	list.InsertAtTail(1);
	list.InsertAtTail(2);
	list.InsertAtTail(3);
	list.InsertAtTail(3);
	list.InsertAtTail(4);
	list.InsertAtTail(5);
	list.Print();
	
	list.Print();
	cout << "Size is:" << list.size() << endl;;
	if (list.isEmpty()) {
		cout << "List is Empty" << endl;
	}
	else {
		cout << "List is not empty." << endl;
	}

	list.Print();
	list.InsertAfter(9, 100);
	cout << "After inserting 9 after 100 :" << endl;
	list.Print();
	list.InsertBefore(2, 2);
	cout << "After inserting 2 before 2 :" << endl;
	list.Print();
	list.InsertBefore(19, 100);
	cout << "After inserting 19 before 100 :" << endl;
	list.Print();
	cout << "SumProduct():" << endl;
	list.sum_product();
	list.Print();
	cout << "After removing duplicates:" << endl;
	list.DeleteDuplicates();
	list.Print();

	cout << "After Reverse:" << endl;
	list.ReverseCLL();
	list.Print();
	CLL<int>list1(list);
	list.InsertAfter(23, 3);
	cout << "After inserting 23 after 3 :" << endl;
	list.Print();
	cout << "List1 after copy constructor:" << endl;
	list1.Print();

	CLL<int>::Iterator obj;
	obj = list.begin();
	++obj;
	cout << "Printing second element of list using Iterator:" << *obj << endl;
	obj = list.end();
	cout << "Printing last element of list using Iterator:" << *obj << endl;
	cout << "Moving occurence(3):" << endl;
	list.MoveOccurrence(3);
	list.Print();
	system("pause");
	return 0;
}
