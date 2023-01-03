#include<iostream>
using namespace std;

template <class T>
class CircularQueue{
	T * data;
	T * front;
	T* rear;
	int size;
	
	public:
		CircularQueue(){
			data= new T [5];
			size=5;
			for(int i=0;i<5;i++){
				data[i]=NULL;
			}
			front= &data[0];
			rear=&data[0];
		}
		CircularQueue(int k){
			data= new T[k];
			size=k;
			for(int i=0;i<5;i++){
				data[i]=NULL;
			}
			front= &data[0];
			rear=&data[0];
		}
		bool isFull(){
			bool check = false;
			if(front!=rear){
				if(data[size]!=NULL&& rear==&data[size] && data[0]!=NULL){
					check=true;
				}
				else if(data[size]!=NULL&& rear==&data[size] && *(rear+1)!=NULL){
					check=true;
				}
				else if(data[0]!=NULL&& *(rear+1)!=NULL){
					check=true;
				}
				
			}
			return check;
		}
		bool isNull(){
			bool check= false;
			if(rear==front&& *front==NULL){
				check=true;
			}
			return check;
		}
		void Enqueue(T input){
			
			if(!isFull()){
				//*rear=input;
				if(rear==front && *front==NULL){
					*rear=input;
				}
				else if(rear!=&data[size]){
					
					rear=rear+1;
					*rear=input;
				}
				else if(data[0]==NULL){
					 rear=&data[0];
					 *rear=input;
				}
			}
		}
		T Dequeue(){
			T check=NULL;
			if(!isNull()){
				check=*front;
				*front=NULL;
				if(front!=&data[size]){
					front=front+1;
			}
				else{
					front=&data[0];
				}
			//	if(rear!=NULL){
					
			//	}
			}
			return check;
		}
		T Front(){
			return *front;
		}
		T Rear(){
			return *rear;
		}
		int Size(){
			return size;
		}
		void print(){
			cout<<"Elements of queue:"<<endl;
			for(int i=0;i<size;i++){
				cout<<"Value at index "<<i<<": "<<data[i]<<endl;
			}
		}
		~CircularQueue(){
			for(int i=0;i<size;i++){
				delete &data[i];
			}
			delete [] data;
		}
};
int main(){
	CircularQueue <int>Q(7);
	for(int k=1;k<=7;k++){
		Q.Enqueue(k);
	}
	 
	for(int k=1;k<=4;k++){
		Q.Enqueue(Q.Dequeue());
		cout<<Q.isFull();
		Q.Dequeue();
	}
	
	Q.print();
	system("pause");
	return 0;
}
