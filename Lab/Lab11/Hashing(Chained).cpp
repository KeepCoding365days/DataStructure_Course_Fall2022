#include <iostream>
//#include <stdlib.h>
#include <vector>
using namespace std;
//template <class v>
int getHash(int i,int size) {
	return i % size;
}
struct item {
	int value;
	int key;
	int status;
	item* next;
	item(int k) {
		value = 0;
		key = k;
		status = 0;
		next = nullptr;
	}
	item(int k, int val) {
		value = val;
		key = k;
		status = 1;
		next = nullptr;
	}

};
template<class v>
class hashmap {
	
	vector <v> hashVector;
	int currentElements;
	void Insert(int key1, int val1) {
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
			item ptr =  item(i);
			hashVector.push_back(ptr);
		}
	}
	hashmap(int capacity) {
		for (int i = 0; i <capacity; i++) {
			item ptr = item(i);
			hashVector.push_back(ptr);
		}
	}
	void Insert(int val1) {
		Insert(getHash(val1, hashVector.size()), val1);
	}

	bool deleteKey(int k) {
		bool check = false;
		item* idx = nullptr;
		for (auto i = hashVector.begin(); i != hashVector.end() && !check; i++) {
			if ((*i).key == k) {
				check = true;
				idx = &(*(i));
			}

		}
		//if (idx != nullptr) {
		if (idx->next == nullptr) {	//used linked list to delete
			check = false;
		}
		else {
			item* ptr = idx->next;
			delete ptr;
			idx->next = nullptr;
		}

//	}
		return check;
	}
	item* get(int k) {
		item *ptr = nullptr;
		for (auto i = hashVector.begin(); i != hashVector.end(); i++) {
			if ((*i).key == k) {
				ptr = &(*i);
			}
		}
		return ptr;
	}
	void Print() {
		for (auto i = hashVector.begin(); i != hashVector.end(); i++) {
			item* ptr = &(*i);
			bool check = false;
			while (ptr != nullptr) {
				cout << ptr->value<<"\t";
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
	obj.Insert(3);
	obj.Insert(2);
	obj.Insert(12);
	obj.Insert(4);
	//obj.Print();
	item* ptr=obj.get(2);
	cout << "Printing values after get function:" << endl;
	while (ptr != nullptr) {
		cout << ptr->value<<"\t";
		ptr =ptr->next;
	}
	cout << endl;
	obj.deleteKey(1);
	cout << "Printing values:" << endl;
	obj.Print();
	system("pause");
	return 0;

}