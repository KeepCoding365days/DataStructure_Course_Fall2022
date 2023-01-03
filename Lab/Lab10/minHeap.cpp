
#include <vector>
#include <iostream>
using namespace std;
class MinHeap {
	vector<int> heap_data;
	int curr_size;
	int capacity;
	void reheap_up(int n) {
		//parent_idx=n-1/2
		while (heap_data.at(n)!= heap_data.at(0) && heap_data.at(n) < heap_data.at((n - 1) / 2)) {
			
			int temp = heap_data.at((n - 1) / 2);
			heap_data.at((n - 1) / 2) = heap_data.at(n);
			heap_data.at(n) = temp;
			n = (n - 1) / 2;
		}
	}
void reheap_Down() {
		int n = 0;
		if (curr_size != 0) {
			
			while (heap_data.at(n) != heap_data.at(curr_size - 1) && (n * 2) + 2 <= curr_size - 1 && (heap_data.at(n) > heap_data.at((2 * n) + 1) || heap_data.at(n) > heap_data.at((2 * n) + 2))) {

				if (heap_data.at(n) > heap_data.at((n * 2) + 1)) {
					int temp = heap_data.at((n * 2) + 1);
					heap_data.at((n * 2) + 1) = heap_data.at(n);
					heap_data.at(n) = temp;
					n = (n * 2) + 1;
				}
				else {
					int temp = heap_data.at((n * 2) + 2);
					heap_data.at((n * 2) + 2) = heap_data.at(n);
					heap_data.at(n) = temp;
					n = (n * 2) + 2;
				}
			}
		}
		if (curr_size == 2) {
			if (heap_data.at(0) > heap_data.at(1)) {
				int temp = heap_data.at(0);
				heap_data.at(0) = heap_data.at(1);
				heap_data.at(1) = temp;
			}
		}
	}
public:
	MinHeap() {
		curr_size = 0;
		capacity = 0;
	}
	MinHeap(int dt) {
		heap_data.push_back(dt);
		curr_size = 1;
		capacity = heap_data.capacity();

	}
	void Insert(int dt) {
		
	
		heap_data.push_back(dt);
		curr_size = heap_data.size();
		capacity = heap_data.capacity();
		
		reheap_up(curr_size - 1);
	}
	
	int getSize() {
		return curr_size;
	}
	int getItem(int n) {
		return heap_data.at(n);
	}
	int dequeue() {
	
		int temp=heap_data.at(0);
		heap_data.at(0) = heap_data.at(curr_size - 1);
		heap_data.pop_back();
		//heap_data.erase(heap_data.at(curr_size-1));
		curr_size = heap_data.size();
		capacity = heap_data.capacity();
		reheap_Down();
		return temp;
	}
	bool isEmpty() {
		bool  check = false;
		if (curr_size == 0) {
			check = true;
		}
		return check;
	}
	void print() {
		for (auto i = heap_data.begin(); i != heap_data.end(); i++) {
			cout<<(*i)<<endl;
		}
		
	}
	
};
int main() {
	MinHeap obj(10);
	obj.Insert(8);
	obj.Insert(9);
	obj.Insert(1);
	obj.dequeue();
	//obj.del();
	obj.Insert(6);
	obj.Insert(4);
	obj.print();
	system("pause");
	return 0;
}
