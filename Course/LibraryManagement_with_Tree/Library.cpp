#include "AVL.cpp"
#include "DLL.cpp"
#include "SLL.cpp"
#include <iostream>
using namespace std;
class Library{
	DLL<Data> books_data;
	AVL<int> tree_table;


public:
	Library() {
		books_data;
		tree_table;
		
	}
	void Reg() {
		SLL<string> authors;
		string title, author=" ";
		int ISSN, ref, iss=0;
		cout << "Please enter ISSN number:" << endl;
		cin >> ISSN;
		cout << "Please enter names of authors. Enter z to exit:";
		while (author != "z") {
			
			cin >> author;
			if (author != "z") {
				authors.InsertAtHead(author);
			}
		}
		cout << "Please enter Title:" << endl;
		cin >> title;
		cin.ignore();
		cout << "Please enter issuance copies number:" << endl;
		cin.ignore();
		cin >> iss;

		cout << "Please enter reference copies number:" << endl;
		cin >> ref;
		Data*ptr= new Data (ISSN, title, authors, iss, ref);
		books_data.InsertAtHead(ptr);
		tree_table.Insert(ISSN, ptr);
		

	}
	void Review() {
		int n;
		cout << "Please enter ISBN number of your boook to see more details:" << endl;
		cin >> n;
		Data* ptr=tree_table.find(n);
		ptr->Print();
	}
	void Update() {
		string a;
		int n;
		cout << "Please enter ISBN number of book to update:" << endl;
		cin >> n;
		Data* ptr = tree_table.find(n);
		cout << "Update title:";
		cin >> ptr->title;
		cout << "Add author:";
		cin >> a;
		ptr->list_authors.InsertAtHead(a);
		cout << "Update issuance quantity:";
		cin >> ptr->iss_copy;
		cout << "Update refernce quantity:";
		cin >> ptr->ref_copy;
	}

		void Del() {
			int n;
			cout << "Please enter ISBN number of book to delete records:" << endl;
			cin >> n;
			Data* p=tree_table.find(n);
			tree_table.delete_R(n);

			//books_data.del(p);
	}
	
	void Print() {
		books_data.Print();
	}

};

int main() {
	Library obj;
	int input=0;
	cout << "Add books:" << endl;
	while (input != -1) {
		obj.Reg();
		cout << "Enter -1 to exit:";
		cin >> input;
	}
	obj.Print();
	obj.Update();
	obj.Review();
	obj.Del();
	system("pause");
	return 0;
}