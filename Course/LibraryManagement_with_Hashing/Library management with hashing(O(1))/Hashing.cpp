#include <iostream>
#include <vector>
#include<time.h>
#include "Node.cpp"
using namespace std;
//Check hash fuction check deletion once more add driver.cpp 

bool isPrime(int n) {
	bool check = true;
	if (n == 0 || n == 1) {
		check = false;
	}
	for (int i = 2; i < n && check; i++) {//dividing all the numbers<n to see if it is prime oor not
		if (n % i == 0) {
			check = false;
		}
	}
	return check;
}
int findP(int n) {
	bool check = false;
	int n1 = n * 1000;
	for (int i = n1; i > n && !check; i++) {
		if (isPrime(i)) {
			n1 = i;
			check = true;
		}
	}
	return n1;
}
int getHash(int i, int size) {
	int P = findP(i);
	srand(time(0));
	int a = rand()%P;//making a and b completely random
	srand(time(0));
	int b = rand() % P;

	int hash = ((a * i + b) % P) % size;
	return hash;
}
struct item {
	Data value;
	int key;
	int status;
	item* next;
	item(int k) {
		value = Data();
		key = k;
		status = 0;
		next = nullptr;
	}
	item(int k, Data &val) {
		value = Data(val.data,val.title,val.list_authors,val.iss_copy,val.ref_copy);
		key = k;
		status = 1;
		next = nullptr;
	}

};
template<class v>
class hashmap {

	vector <v> hashVector;
	int currentElements;
	void Insert(int key1, Data val1) {
		auto i = hashVector.begin();
		while ((*i).key != key1) {
			i++;
		}
		//cout << (*i).key;
		item* ptr = &(*i);
		while (ptr->next != nullptr) {
			ptr = ptr->next;
		}
		ptr->next = new item(key1, val1);
		
	}
public:
	hashmap() {
		for (int i = 0; i < 10; i++) {
			item ptr = item(i);
			hashVector.push_back(ptr);
		}
	}
	hashmap(int capacity) {
		for (int i = 0; i < capacity; i++) {
			item ptr = item(i);
			hashVector.push_back(ptr);
		}
	}
	void Insert() {
		SLL<string> authors;
		string title, author = " ";
		int ISSN, ref, iss = 0;
		cout << "Please enter ISBN number:" << endl;
		cin >> ISSN;
		cout << "Please enter names of authors. Enter z to exit:";
		while (author != "z") {

			cin >> author;
			if (author != "z") {
				authors.InsertAtHead(author);
			}
		}
		cin.ignore();
		cout << "Please enter Title:" << endl;
		cin >> title;
		cin.ignore();
		cout << "Please enter issuance copies number:" << endl;
		cin.ignore();
		cin >> iss;

		cout << "Please enter reference copies number:" << endl;
		cin >> ref;

		Data obj= Data(ISSN, title, authors, iss, ref);
		//cout << hashVector.size();
		Insert(getHash(ISSN, hashVector.size()), obj);
		
	}

	bool deleteKey(int k) {
		int k1 = getHash(k, hashVector.size());
		bool check = false;
		item* idx = nullptr;
		for (auto i = hashVector.begin(); i != hashVector.end() && !check; i++) {
			if ((*i).key == k1) {
				check = true;
				idx = &(*(i));
			}

		}
		//if (idx != nullptr) {
		if (idx->next == nullptr) {	//used linked list to delete
			check = false;
		}
		else {
			item * temp= idx;
			while (temp->next != nullptr && !check) { //bcz of dummy node
				
				if (temp->next->value.data == k) {
					check = true;
				}
				if (!check)
					temp = temp->next;
			}
			if (check) {
				if (temp->next->next != nullptr) {
					
					item* temp1 = temp->next;
					temp->next = temp->next->next;
					delete temp1;
				}
				else {
					item* temp1 = temp->next;
					temp->next = nullptr;
					delete temp1;
				}
			}
			
		}
		
		//	}
		return check;
	}
	item* get(int k) {
		k = getHash(k, hashVector.size());
		item* ptr = nullptr;
		/*for (auto i = hashVector.begin(); i != hashVector.end(); i++) {
			if ((*i).key == k) {
				ptr = &(*i);
			}
		}*/
		ptr = &hashVector.at(k);
		return ptr;
	}
	void Review(int issn) {
		bool check = false;
		item* obj = get(issn);
		while (obj != nullptr) {
			if (obj->value.data == issn) {
				obj->value.Print();
				check = true;
			}
			obj = obj->next;
		}
		if (!check) {
			cout << "Record not Found. Wrong ISBN number." << endl;
		}
	}
	void Update(int issn) {
		bool check = false;
		item* obj = get(issn);
		
		while (obj != nullptr && !check) {
			if (obj->value.data == issn) {
				string a;
				cout << "Update title:";
				cin >> obj->value.title;
				cout << "Add author. Enter z if you don't want to enter authors:";
				cin >> a;
				if(a!="z")
					obj->value.list_authors.InsertAtHead(a);
				cout << "Update issuance quantity:";
				cin >> obj->value.iss_copy;
				cout << "Update refernce quantity:";
				cin >> obj->value.ref_copy;
				check = true;
			}
			if (!check) {
				obj = obj->next;
			}
		}
		if (!check) {
			cout << "Record not Found. Wrong ISBN number." << endl;
		}
		

	}
	void Print() {
		for (auto i = hashVector.begin(); i != hashVector.end(); i++) {
			item* ptr = &(*i);
			bool check = false;
			while (ptr != nullptr) {
				ptr->value.Print();
				ptr = ptr->next;
				check = true;
			}
			if (!check) {
				cout << 0;
			}
			cout << endl;

		}

	}
	~hashmap() {
		item* ptr;
		for (auto i = hashVector.begin(); i != hashVector.end(); i++) {
			ptr = &(*i);
			ptr = ptr->next;
			while (ptr != nullptr) {
				item* temp = ptr;
				ptr = ptr->next;
				delete temp;
			}
		}
	}
};
int main() {
	int size = 5;
	hashmap <item>obj(size);
	obj.Insert();
	obj.Review(20);
	obj.deleteKey(20);
	obj.Update(20);
	obj.Review(20);
	//cout << findP(100);
	system("pause");
	return 0;

}