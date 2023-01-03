#include <iostream>
//#include <stdlib.h>
#include <vector>
using namespace std;
//template <class v>
int getHash(int i, int size) {
	return i;
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
		item* ptr = nullptr;
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
				cout << ptr->value << "\t";
				ptr = ptr->next;
				check = true;
			}
			if (!check) {
				cout << 0;
			}
			cout << endl;

		}

	}
	void count() {
		int count = 0;
		vector <int>odd_recur;
		for (auto i = hashVector.begin(); i != hashVector.end(); i++) {
			count = 0;
			item *ptr= &(*i);
			
			while (ptr->next != nullptr) {
				ptr = ptr->next;
				count++;
			}
			if (count >= 1) {
				cout << (*i).next->value << " appears " << count << " times." << endl;
			}
			if (count % 2 != 0) {
				odd_recur.push_back((*i).next->value);
			}
		}
		cout << odd_recur.at(0) << "," << odd_recur.at(1) << " are odd occuring elements." << endl;
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
	int size = 10;
	hashmap <item>obj(size);
	cout << "Please neter element of array. Enter -1 to exit:" << endl;
	int input = 0;
	cin >> input;
	while (input != -1) {
		obj.Insert(input);
		cin >> input;
	}
	obj.count();
	system("pause");
	return 0;

}