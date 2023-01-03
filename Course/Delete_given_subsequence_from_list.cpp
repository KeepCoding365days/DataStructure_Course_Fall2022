#include <iostream>
using namespace std;

class List{

struct node{
	int data;
	node* next;
	node(){
		data=0;
		next=0;
	}
	node(int num, node*ptr){
		data=num;
		next=ptr;
	}
};

node* head;
node* tail;
node * dummy_ptr;
node * dummy_ptr_tail;

class Iterator{
	node * iptr;
	
	public:
		Iterator(){
			iptr=0;
		}
		Iterator(node* ptr){
			iptr=ptr;
		}
		Iterator & operator ++(int){
			iptr=iptr->next;
			return *this;
		}
		Iterator & operator ++(){
			iptr=iptr->next;
			return *this;
		}
				
		int & operator*(){
			return iptr->data;
		}
		node* pointer(Iterator j){
			return j.iptr;
		}	
		
		bool operator==(const Iterator & l){
			return iptr==l.iptr;
		}
		bool operator!=(const Iterator & l){
			return iptr!=l.iptr;
		}
	};

public:
	typedef Iterator It;
	It begin(){
			return head->next;
		}
	It end(){
			return tail;
		}
	
	List(){
		dummy_ptr=new node (0,0);
		*head=*dummy_ptr;
		*tail=*dummy_ptr;
		
		
	}
	List(int num){
		dummy_ptr=new node (0,0);
		dummy_ptr_tail=new node(0,0);
		head=dummy_ptr;
		tail=dummy_ptr_tail;
		node* num_ptr=new node(num,tail);
		head->next=num_ptr;
		//tail->next=num_ptr;
		
	}
	void insert(int num){
		node* iptr=head->next;
		while(iptr->next!=tail){
			iptr=iptr->next;
		}
		
		node* num_ptr=new node(num,tail);
		iptr->next=num_ptr;
		
	}
	void print(){
		node*ptr=head->next;
		int counter=0;
		//cout<<tail->next->data;
		while(ptr->next!=0){
			counter++;
			cout<<ptr->data;
			ptr=ptr->next;
		}
	}
	void del(Iterator j){
		node * pointer_new=j.pointer(j);
		node*pointer_prev=head;
		while( pointer_prev->next!=pointer_new){
			pointer_prev=pointer_prev->next;
		}
		pointer_prev->next=pointer_new->next;
	}
	
	
	
void deleteSubSequence(List list){
	Iterator it;
	int counter=0;
	for(Iterator i=list.begin(); i!=list.end();i++){
		counter=0;
		
		if(*i==1){
			Iterator j=i;
			for(j++;*j!=1&& j!=list.end();j++){
				counter++;
			}
			if(counter>0){
				counter++;
			}
		
		int cnt=0;
		for(Iterator k=i;cnt<counter;k++,cnt++){
			
			del(k);
		}
	}
	}
}
};

int main(){
	List data(1);
	data.insert(0);
	data.insert(1);
	data.insert(1);
	data.insert(1);
	data.insert(1);
	data.insert(0);
	cout<<"Data before subsequence deletion: ";
	data.print();
	cout<<endl;
	data.deleteSubSequence(data);
	cout<<"Data after subsequence deletion: ";
	data.print();
	return 0;
	system("pause");
}
