  #include <iostream>
using namespace std;
struct Node{
	int data;
	Node* next;
	Node(){
		data=0;
		next=NULL;
		
	}
	Node(int val, Node * next_1){
		data=val;
		next=next_1;
	}
	
};
class List{
	Node*head;
	Node*tail;
	
	public:
		List(){
		head=NULL;
		tail=NULL;
	}
	List(int val){
		Node *ptr1=new Node();
		Node * ptr=new Node(val,ptr1);
		head=ptr;
		
		
	}
	void append_1(Node *nextptr){
		Node*ptr=new Node(nextptr->data,nextptr->next);
		if(tail!=NULL){
		tail->next=ptr;
	}	
	if(head==NULL){
		head=ptr;
	}
		tail=ptr;
		
	}
	
	void find_greatest(){
		Node*ptr=head->next;
		int check=0;
		bool complete=0;
		bool found=0;
		while(ptr!=tail){
			Node*ptr1=ptr->next;
			check=ptr->data;
			found=0;
			complete=0;
			while(!complete){
				if(ptr1->data>check){
					check=ptr1->data;
					found=1;
				}
				
				if(ptr1==tail){
					complete=1;
				}
				ptr1=ptr1->next;
			}
			if(found){
				cout<<check<<endl;
			}
			else{
				cout<<-1<<endl;
			}
			ptr=ptr->next;
		}
	}
};
int main(){
	cout<<"Please insert data of list. Enter -1 to exit:"<<endl;
	int input=0;
	int count=0;
	List lis;
	while(input!=-1){
		cin>>input;
		if(input!=-1 && count ==0){
			Node*ptr=new Node (input,0);
			lis.append_1(ptr);
			count++;
		}
		
		if(input!=-1 && count >0){
			Node* ptr=new Node(input,NULL);
			lis.append_1(ptr);
		}
	}
	cout<<"Next greater numbers:"<<endl;
	lis.find_greatest();
	
	system("pause");
	return 0;
}
