#include<iostream>
using namespace std;
template<class T>
class vector {
	T* arrPtr;
	int capacity;
	int currentSize;
public:
	vector<T>() {
		arrPtr = new T[2];
		capacity = 2;
		currentSize = 0;
		for (int i = 0;i < capacity;i++) {
			arrPtr[i] = NULL;
		}
	}

	vector<T>(int num) {
		arrPtr = new T [num];
		capacity = num;
		currentSize = 0;
		for (int i = 0;i < capacity;i++) {
			arrPtr[i] = 0;
		}
	}
	vector<T>(const vector<T>& obj) {
		*this = obj;

	}
	int getCapacity() {
		return capacity;
	}
	int getSize() {
		return currentSize;
	}
	void operator +(T num) {
		if (currentSize == capacity) {
			capacity = capacity * 2;
			T* temp = arrPtr;
			arrPtr = new T[capacity];
			for (int i = 0;i < currentSize; i++) {
				arrPtr[i] = temp[i];
			}
			arrPtr[currentSize] = num;
			currentSize++;
			delete temp;
		}
		else {
			arrPtr[currentSize] = num;
			currentSize++;
		}

	}
	void operator -() {
			arrPtr[currentSize] = NULL;
			currentSize--;
	}
	vector operator+ (const vector<T>& obj) {
		vector <T>temp(currentSize+obj.currentSize);
		for (int i = 0;i < currentSize;i++) {
			temp + arrPtr[i];

		}
		for (int i = 0;i < obj.currentSize;i++) {
			
			temp + obj.arrPtr[i];
			

		}
		
		return temp;
	}
	void operator =(const vector& obj) {
		
		//delete[]arrPtr;
		//cout << 'a';
		//cout << getCapacity() << endl;;
		capacity = obj.capacity;
		currentSize = obj.currentSize;
		arrPtr = new T[capacity];
		for (int i = 0;i < currentSize;i++) {
			arrPtr[i] = obj.arrPtr[i];
		}

	}
	bool operator[](int idx) {
		bool check = true;
		if (idx > currentSize-1) {
			check = false;
		}
		return check;
	}
	template <class U>
	friend istream& operator>> (istream& in, vector<U> &obj);
	template <class U>
	friend ostream& operator<< (ostream& out,const vector<U> &obj);
	
	~vector<T>() {
		delete [] arrPtr;
	}
};
template<class T>
ostream& operator <<(ostream& out,const vector<T> &obj) {
	out << "Elements of vector:" << endl;
	for (int i = 0;i < obj.currentSize;i++) {
		out << obj.arrPtr[i] << endl;
	}
	return out;
}
template<class T>
istream& operator>> (istream& in, vector<T>& obj) {
	T input;
	cout<< "Enter elements of Vector. Enter 0 to exit:" << endl;
	in >> input;
	while (input != 0 && input!='0') {
		obj + input;
		in >> input;

	}
	return in;
}
int main() {
	vector<char> V1;
	cin >> V1;
	cout << "V1:" << endl;
	cout << V1;
	vector<char> V2(V1);
	-V1;
	cout << "V2 after copy constructor" << endl;
	cout << V2;
	cout << "-V1:" << endl;
	cout << V1;
	vector<char> V3;
	V3=V1 + V2;
	cout << "V3=V1+V2" << endl;
	cout << V3;
	cout << "Capacity of V2 is:" << V2.getCapacity() << endl;
	cout << "CurrentSize of V2 is:" << V2.getSize()<<endl;
	cout << V2[2]<<endl;
	system("pause");
	return 0;
}
