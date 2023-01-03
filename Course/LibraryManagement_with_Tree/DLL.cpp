#pragma once
#include"SLL.cpp"
#include <iostream>
#include <string>
using namespace std;

struct Data {
	int data;//ISSN
	string title;
	int ref_copy;
	int iss_copy;
	SLL<string> list_authors;

	Data* next;
	Data* prev;

	Data() {
		data = 0;
		list_authors;
		iss_copy = 0;
		ref_copy;
		title = " ";
		next = nullptr;
		prev = nullptr;
	}
	Data(int ISSN, string titl, SLL<string>& list, int iss, int ref) {
		data = ISSN;
		title = titl;
		list_authors = list;
		iss_copy = iss;
		ref_copy = ref;
		prev = nullptr;
		next = nullptr;

	}
	Data(int ISSN,string titl,SLL<string>&list,int iss, int ref, Data* ptr, Data* ptr1) {
		data = ISSN;
		title = titl;
		list_authors = list;
		iss_copy = iss;
		ref_copy = ref;
		prev = ptr1;
		next = ptr;

	}
	void Print() {
		cout << "ISBN:" << data<<endl;
		cout << "Title:" << title<<endl;
		list_authors.Print();
		cout << "Issuance copies:" << iss_copy << endl;
		cout << "Reference copies:" << ref_copy << endl;
	}
};
template<class T>
class DLL {
	
	Data* head;
	Data* tail;

public:
	DLL<T>() {
		head = nullptr;
		tail = nullptr;
	}
	/*DLL<T>(DLL& list) {
		Data* ptr = list.head;

		head = new Data(ptr->data," ",nullptr,0,0, nullptr, nullptr);
		Data* ptr1 = head;

		while (ptr != nullptr) {
			if (ptr != list.tail) {
				ptr1->next = new Data(ptr->next->data, " ", nullptr, 0, 0, nullptr, nullptr);
				ptr1->next->prev = ptr1;
			}
			else {
				tail = ptr1;
			}
			ptr1 = ptr1->next;
			ptr = ptr->next;

		}
	}*/
	void InsertAtHead(Data* ptr) {
		if (head == nullptr) {
			head = ptr;
			tail = head;
		}
		else {
			ptr->prev = head;
			head->prev = ptr;
			head = ptr;

		}
	}
	void del(Data* temp) {

		//temp->prev->next = temp->next;
		//temp->next->prev = temp->prev;
		
	}
	//void InsertAtTail(T val) {
	//	if (head == nullptr && tail == nullptr) {
	//		tail = new Data(val, nullptr, nullptr);
	//		tail = head;
	//	}
	//	else {
	//		Da* ptr = new Data(val, nullptr, tail);
	//		tail->next = ptr;
	//		tail = ptr;
	//	}
	//}

	//void PrintForward() {
	//	Data* ptr = head;
	//	cout << "Printing from head to tail: " << endl;
	//	while (ptr != nullptr) {
	//		cout << ptr->data << "->";
	//		ptr = ptr->next;
	//	}
	//	cout << "null";
	//	cout << endl;
	//}
	//void PrintBackward() {
	//	Data* ptr = tail;
	//	cout << "Printing from tail to head: " << endl;
	//	while (ptr != nullptr) {
	//		cout << ptr->data << "->";
	//		ptr = ptr->prev;
	//	}
	//	cout << "null";
	//	cout << endl;
	//}

	//void EraseAtHead() {
	//	if (head != nullptr) {
	//		Node* ptr = head;
	//		head = head->next;
	//		head->prev = nullptr;
	//		delete ptr;
	//	}
	//}
	//void EraseAtTail() {
	//	Node* ptr = tail;
	//	tail = tail->prev;
	//	tail->next = nullptr;
	//	delete ptr;

	//}
	//int getSize() {
	//	int size = 0;
	//	Node* ptr = head;
	//	while (ptr != nullptr) {
	//		size++;
	//		ptr = ptr->next;
	//	}
	//	return size;
	//}
	//int getMiddle() {
	//	return (this->getSize() / 2);
	//}
	//bool isEmpty() {
	//	bool check = false;
	//	if (head == nullptr && tail == nullptr) {
	//		check = true;
	//	}
	//	return check;
	//}
	//int getMax();
	//void InsertAfter(T val, T key) {
	//	Data* ptr = head;
	//	while (ptr->next != nullptr && ptr->data != key) {
	//		ptr = ptr->next;
	//	}

	//	if (ptr->next != nullptr) {
	//		Node* temp = new Node(val, ptr->next, ptr);
	//		ptr->next->prev = temp;
	//		ptr->next = temp;


	//	}
	//	else {
	//		ptr->next = new Node(val, nullptr, ptr);
	//		tail = ptr->next;

	//	}

	//}
	//
	//void InsertBefore(T val, T key) {
	//	Data* ptr = tail;
	//	while (ptr->prev != nullptr && ptr->data != key) {
	//		ptr = ptr->prev;
	//	}

	//	if (ptr->prev != nullptr) {
	//		Node* temp = new Data(val, ptr, ptr->prev);
	//		ptr->prev->next = temp;
	//		ptr->prev = temp;


	//	}
	//	else {
	//		ptr->prev = new Data(val, ptr, nullptr);
	//		head = ptr->prev;

	//	}

	//}
	///*void Merge(DLL& first_half, DLL& second_half) {
	//	this->head = first_half.head;
	//	this->tail = second_half.tail;
	//	first_half.tail->next = second_half.head;
	//	second_half.head->prev = first_half.tail;
	//}*/
void Print() {
	head->Print();
}
	~DLL() {
		Data* ptr = head;
		while (ptr != nullptr) {
			Data* temp = ptr;
			ptr = ptr->next;
			delete temp;
		}
	}
};
//int DLL<int>::getMax() {
//	int max = 0;
//	Node* ptr = head;
//	while (ptr != tail) {
//		if (ptr->data > max) {
//			max = ptr->data;
//		}
//		ptr = ptr->next;
//	}
//	return max;
//}
