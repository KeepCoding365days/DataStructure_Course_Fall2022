#pragma once
#include <iostream>
#include <string>
using namespace std;
template<class t>
class SLL {
	struct Node {
		t data;
		Node* next;

		Node() {
			data = " ";
			next = nullptr;
		}

		Node(t val, Node* ptr) {
			data = val;
			next = ptr;
		}
	};
	Node* head;
	Node* tail;

public:
	SLL<t>() {
		head = nullptr;
		tail = nullptr;
	}
	void InsertAtHead(t val) {
		if (head == nullptr && tail == nullptr) {
			head = new Node(val, nullptr);
			tail = head;
		}
		else {
			head = new Node(val, head);
		}
	}

	void InsertAtTail(t val) {
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
		cout << "Authors:" << endl;
		while (ptr != nullptr) {
			cout << ptr->data << endl;
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
		/*Node* ptr = head;
		while (ptr != tail) {
			Node* temp = ptr;
			ptr = ptr->next;
			delete temp;
		}*/
	}
};