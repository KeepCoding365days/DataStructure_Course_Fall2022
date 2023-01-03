/*Destructor + calling get()in main*/
#include <iostream>
using namespace std;
int getHash(int val, int capacity) {
	return val % capacity;
}

template <class v>
struct Item {
	int status;
	v value;
	int key;

	Item<v>() {
		status = 0;
		value = " ";
		key = 0;
	}
	Item<v>(int key1,v val1) {
		status = 1;
		value = val1;
		key = key1;
	}
};

template <class v>
class HashMap {//linear Probing
protected:
	Item<v>* arr;
	int capacity;
	int current_elements;

	virtual int getNextCandidate(int key, int i);
	void doubleCapacity();

	void insert(int key1,int k, v val, Item<v>* arr) {
		if (arr[k].status == 0 || arr[k].status == 1) {
			arr[k].key = key1;
			arr[k].value = val;
			arr[k].status = 2;//setting status to occupied
			current_elements++;
		}
		else if ((double(current_elements) / double(capacity)) >= 0.75) {
			doubleCapacity();
			insert(key1,val);
		}
		else {
			k = getNextCandidate(key1, 1);
			arr[k].key = key1;
			arr[k].value = val;
			arr[k].status = 2;//setting status to occupied
			current_elements++;
		}
	}
public:
	HashMap() {
		capacity = 10;
		current_elements = 0;
		arr = new Item<v>[10];

	}
	HashMap(int capacity1) {
		capacity = capacity1;
		current_elements = 0;
		arr = new Item<v>[capacity1];
	}
	void insert(int k,v val) {
		int k1 = k;
		k = getHash(k, capacity);
		insert(k1,k,val, arr);

	}

	bool deleteKey(int key) {
		bool check = false;
		for (int i = 0; i < capacity; i++) {
			if (i == key) {
				arr[i].status = 1; //setting status to deleted
				check = true;
			}
		}
		return check;
	}

	Item<v>* get(int k) {
		Item<v>* ptr=nullptr;
		bool check = false;
		for (int i = 0; i < capacity&&!check; i++) {
			if (arr[i].key == k) {
				ptr = arr[i];
				check = true;
			}
		}
		return ptr;
	}
	void Print() {
		for (int i = 0; i < capacity; i++) {
			
			if (arr[i].status != 0){ //setting status to deleted
				cout <<"idx:"<<i<<"\t key:"<<arr[i].key<<"\t value:"<< arr[i].value << "\t status:" << arr[i].status;
			}
			else {
				cout <<"idx:"<<i<<"\t key:"<<arr[i].key<<"\t value:"<< arr[i].value << "\t status:" << arr[i].status;
			}
			cout << endl;
		}
	}
	~HashMap() {
		/*for (int i = 0; i < capacity; i++) {
			delete &arr[i];
		}*/
		delete[]arr;
	}
};
template <class v>
class QHashMap :public HashMap<v> {
public:
	QHashMap<v>():HashMap<v>() {
		
	}
	QHashMap<v>(int c1): HashMap<v>(c1) {
		
	}
	int getNextCandidate(int key, int i) {
		
		int key1 = getHash(key +( i*i), HashMap<v>::capacity);
		Item<v>* arr = HashMap<v> ::arr;
		if (arr[key1].status == 0 ||arr[key1].status == 1) {
			//cout << "done";
			return key1;
		}
		else {
			i = i+1;
			return getNextCandidate(key, i);
		}
	}
	~QHashMap<v>() {

	}
};

template <class v>
class DHashMap :public HashMap<v> {
public:
	DHashMap<v>() :HashMap<v>() {

	}
	DHashMap<v>(int c1) : HashMap<v>(c1) {

	}
	int getNextCandidate(int key, int i) {
		int Prime = 7;
		int key1 = getHash(key, HashMap<v>::capacity);
		int key2 = Prime - getHash(key, Prime);
		int idx = (key1 +( i * key2));
		
		if (idx >= HashMap<v>::capacity) {
			idx = idx % HashMap<v>::capacity;
		}
		//idx = getHash(idx, 10);
		Item<v>* arr = HashMap<v> ::arr;
		if (arr[idx].status == 0 || arr[idx].status == 1) {
			//cout << "done";
			return idx;
		}
		else {
			i = i + 1;
			return getNextCandidate(key, i);
		}
	}
	~DHashMap<v>() {
		
	}
};
template<class v>
int HashMap<v>::getNextCandidate(int key, int i) {
	//cout << key;
	//cout << i;
	int key1 = getHash(key+i, HashMap<v>::capacity);
	if (arr[key1].status == 0 || arr[key1].status == 1) {
		//cout << "done";
		return key1;
	}
	else {
		i = i + 1;
		return getNextCandidate(key, i);
	}
}
template<class v>
void HashMap<v>::doubleCapacity() {
	capacity = capacity * 2;
	Item<v>* temp = arr;
	arr = new Item<v>[capacity];
	for (int i = 0; i < (capacity / 2); i++) {
		insert(temp[i].key, temp[i].value);
	}
}


//template < v>
int main() {
	cout << "Linear Probing:" << endl;
	HashMap<string> obj(10);
	obj.insert(89,"hassan");
	obj.insert(18,"ali");
	obj.insert(49,"ayan");
	obj.insert(58, "ahsan");
	obj.insert(69,"baber");
	obj.Print();
	HashMap<string> obj1(1);
	obj1.insert(0, "a");
	obj1.insert(11, "b");
	obj1.Print();
	//Item<v>* ptr = &obj.get(69);
	//cout << "Value at key 69: " << ptr->value << endl;
	cout << "Quadratic Probing:" << endl;
	QHashMap<string> obj2(10);
	obj2.insert(89, "hassan");
	obj2.insert(18, "ali");
	obj2.insert(49, "ayan");
	obj2.insert(58, "ahsan");
	obj2.insert(69, "baber");
	obj2.Print();

	cout << "Double Hasing:" << endl;
	DHashMap<string> obj3(10);
	obj3.insert(89, "hassan");
	obj3.insert(18, "ali");
	obj3.insert(49, "ayan");
	obj3.insert(58, "ahsan");
	obj3.insert(69, "baber");
	obj3.Print();
	system("pause");
	return 0;

}