#include<iostream>
using namespace std;
class vector {
	int* arrPtr;
	int capacity;
	int currentSize;
public:
	vector() {
		arrPtr = new int[2];
		capacity = 2;
		currentSize = 0;
		for (int i = 0;i < capacity;i++) {
			arrPtr[i] = 0;
		}
	}
	vector(int num) {
		arrPtr = new int[num];
		capacity = num;
		currentSize = 0;
		for (int i = 0;i < capacity;i++) {
			arrPtr[i] = 0;
		}
	}
	vector(const vector& obj) {
		*this = obj;

	}
	int getCapacity() {
		return capacity;
	}
	int getSize() {
		return currentSize;
	}
	void operator +(int num) {
		if (currentSize == capacity) {
			capacity = capacity * 2;
			int* temp = arrPtr;
			arrPtr = new int[capacity];
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
			arrPtr[currentSize] = 0;
			currentSize--;
	}
	vector operator+ (const vector& obj) {
		vector temp(currentSize+obj.currentSize);
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
		arrPtr = new int[capacity];
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

	friend istream& operator>> (istream& in, vector &obj);
	friend ostream& operator<< (ostream& out,const vector &obj);
	
	~vector() {
		delete [] arrPtr;
	}
};
ostream& operator <<(ostream& out,const vector &obj) {
	out << "Elements of vector:" << endl;
	for (int i = 0;i < obj.currentSize;i++) {
		out << obj.arrPtr[i] << endl;
	}
	return out;
}
istream& operator>> (istream& in, vector& obj) {
	int input=0;
	cout<< "Enter elements of Vector. Enter -1 to exit:" << endl;
	in >> input;
	while (input != -1) {
		obj + input;
		in >> input;

	}
	return in;
}
int main() {
	vector V1;
	cin >> V1;
	cout << "V1:" << endl;
	cout << V1;
	vector V2(V1);
	-V1;
	cout << "V2 after copy constructor" << endl;
	cout << V2;
	cout << "-V1:" << endl;
	cout << V1;
	vector V3;
	//cout << 5;
	V3=V1 + V2;
	//cout << 6;
	cout << "V3=V1+V2" << endl;
	cout << V3;
	cout << "Capacity of V2 is:" << V2.getCapacity() << endl;
	cout << "CurrentSize of V2 is:" << V2.getSize()<<endl;
	cout << V2[2]<<endl;
	system("pause");
	return 0;
}