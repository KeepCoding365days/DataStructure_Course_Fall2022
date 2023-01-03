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

	Data() {
		data = 0;
		list_authors;
		iss_copy = 0;
		ref_copy;
		title = " ";
		
	}
	Data(int ISSN, string titl, SLL<string>& list, int iss, int ref) {
		data = ISSN;
		title = titl;
		list_authors = list;
		iss_copy = iss;
		ref_copy = ref;

	}
	void Print() {
		cout << "ISBN:" << data<<endl;
		cout << "Title:" << title<<endl;
		list_authors.Print();
		cout << "Issuance copies:" << iss_copy << endl;
		cout << "Reference copies:" << ref_copy << endl;
	}
};