#include <iostream>
using namespace std;
class SLL_memory{
	struct Node{
	int data;
	Node* next;
	bool free;
	int start_byte;
	int ending_byte;
	
	Node(){
		data=0;
		next=0;
		free=0;
	}
	Node(int data_1, Node* next_1,bool free1,int strt,int end){
		
		data=data_1;
		next=next_1;
		free=free1;
		start_byte=strt;
		ending_byte=end;
	}	
	
};

	Node *head;
	Node* tail;
	int size;
	
	

public:
	SLL_memory(){
		head= 0;	//without dummies
		tail= 0;
		
	}
	void add_fragment(int size){
		Node*ptr=new Node(size,head,true,0,size);
		
		if(tail->data>size){
		head=ptr;
		tail->start_byte+=size;
			ptr=ptr->next;
			
			while(ptr->next!=0){
				ptr->ending_byte+=size;
				ptr->start_byte+=size;
				ptr=ptr->next;
			}
			
			tail->data-=size;
		}
		else{
			cout<<"Not enough space in memory to create this fragment!"<<endl;
		}
		
	}		
	int * assign_memory(int data_1){ 		//returning first byte of assigned memory block		
		if(head==0 && tail==0){
			
			Node * ptr=new Node(data_1,0,true,0,data_1);
			head=ptr;
			tail=ptr;
			return &(ptr->start_byte);
		}
		else{
			
			Node * ptr1= head;
			while((ptr1->data<data_1 || ptr1->free==false)&& ptr1->next!=0){
				ptr1=ptr1->next;
			}
			
			if(ptr1->data>data_1 && ptr1->free==true){
				Node * ptr=new Node(data_1,ptr1,false,ptr1->start_byte,(ptr1->start_byte)+data_1);
				//ptr->next=ptr1;
				ptr->next->start_byte=ptr->ending_byte;
				ptr->next->data-=data_1;
				if(ptr1==head){
				head=ptr;
				return &(ptr->start_byte);
				}
				else{
					Node * ptr2=head;
					while(ptr2->next!=ptr1){
						ptr2=ptr2->next;
					}
					ptr2->next=ptr;
					return &(ptr->start_byte);
				}
			}
			
			else if(ptr1->data==data_1 && ptr1->free==true){
				ptr1->free=false;
				return &(ptr1->start_byte);
			}
			else{
				cout<<"Not enough memory to run this Program.";
				int *p =new int (-1);
				return p;
			}
			
			
		
		}
	}
	
	int * assign_memory_best_fit(int size){
		if(head==0 && tail==0){
			SLL_memory::assign_memory(size);
		}
		else{
			
			Node * ptr= head;
			while((ptr->data<size||ptr->free==false) && ptr->next!=0){
				ptr=ptr->next;
			}
			
			if(ptr->data==size&& ptr->free==true){
				ptr->free=false;
				return &(ptr->start_byte);
			}
			else if(ptr->data>size&& ptr->free ==true){
				Node * array[100];		//keeping best nodes in form of stack
				array[0]=ptr;
				int efec=ptr->data-size; 	//measuring freq
				int count=1; 	//to count all bigger blocks
				
				while(ptr->next!=0){
					ptr=ptr->next;
					if(ptr->data-size<efec && ptr->data-size>=0){
						efec=ptr->data-size;
						count++;
						array[count-1]=ptr;
						
					}
				}// (data_1,ptr1,false,ptr1->start_byte,(ptr1->start_byte)+data_1)
				
				Node* ptr1=new Node(size,array[count-1],false,array[count-1]->start_byte,(array[count-1]->start_byte)+size);
				Node *ptr2= head;
				if(array[count-1]!=head){
				
				while(ptr2->next!=array[count-1]){
					ptr2=ptr2->next;
				}
				
				ptr2->next=ptr1;
			}
			else{
					head=ptr1;
					
				}
				array[count-1]->data-=size;
				array[count-1]->start_byte+=size;
				return &(ptr1->start_byte);
			
				
			}
			else{
				cout<<"Not Enough Memory to run this program"<<endl;
				int * p= new int (-1);
				return p;
			}
		}
		
	}
	int * start_byte(int size){
		int *a=&(head->start_byte);
		
		return a;
	}
	
	void SetFree(int strt,int tot){
		Node* ptr=head;
		while(ptr->data!=tot && ptr->start_byte!=strt){
			ptr=ptr->next;
		}
		ptr->free=true;
	}

	void Print(){
		Node *ptr=head;
		
		while(ptr!=0){
			cout<<endl;
			cout<<"Memory Size: "<<ptr->data<<endl;
			cout<<"Starting Byte: "<<ptr->start_byte<<endl;
			cout<<"Ending Byte: "<<ptr->ending_byte<<endl;
			if(ptr->free){
				cout<<"free"<<endl;
			}
			else{
				cout<<"Not Free "<<endl;
			}
			cout<<endl;
			ptr=ptr->next;
		}
	}
	~SLL_memory(){
		Node *ptr=head;
		while(ptr!=0){
			Node * temp=ptr;
			ptr=ptr->next;
			delete temp;
		}
		
	}
};
class SLL_Progs{
	
class Program{
	class SLL_blocks{
		struct block{
			block * next;
			int * start_byte_id;
			int total_bytes;
			public:
				block(){
					next=0;
					start_byte_id=0;
					total_bytes=0;
				}
				block(int * strt, int  tot){
					next=0;
					start_byte_id=strt;
					total_bytes=tot;
					
				}
		};
		
		block* head;
		block * tail;
		
		public:
			SLL_block(){
				
				head=0;
				tail=0;//implementation without dummies
			}
			SLL_block(int * strt, int tot){
				block * ptr= new block (strt, tot);
				if(head==0 && tail==0){
					head->next=ptr;
					tail->next=ptr;
				}
				else{
					tail->next->next=ptr;
					tail->next=ptr;
				}
			}
			void add_block(int * strt, int tot){
				block * ptr= new block (strt, tot);
				if(head==0 && tail==0){
					head=ptr;
					tail=ptr;
					
				}
				else{
					tail->next=ptr;
				   	tail=ptr;
				}
			}
			
			int shrink(){
				
				block*ptr=head;
				if(head!=tail){
				
				while(ptr->next!=tail){
					ptr=ptr->next;
				}
			}
				  
				if(head==tail){
					head=tail=0;
					int temp=ptr->total_bytes;
					delete ptr;
					return temp;
				}
				else{
				
				tail=ptr;
				int temp=ptr->next->total_bytes;
				delete ptr->next;
				ptr->next=0;
				return temp;
			}
				
			}
			
			int getSize(){	//returning total bytes of tail to set free in memory
				if(head==0 &&tail==0){
					return -1;
				}
				else{
				return tail->total_bytes;
				}
			}
			
			int getStart(){	//returning Start of tail to set free in memory
				if(head==0 &&tail==0){
					return -1;
				}
				else{
				return *(tail->start_byte_id);
				}
			}
			void print(){
			block * ptr= head;
			if(head!=0){
			while(ptr!=0){
			cout<<endl;
			cout<<"Memory Start index: "<<*ptr->start_byte_id<<endl;
			cout<<"Total bytes in block: "<<ptr->total_bytes<<endl;
			ptr=ptr->next;
			}
		}
		else{
			cout<<"No memory assigned to this program!"<<endl;
		}
			}
		~SLL_blocks(){
			block *ptr=head;
			while(ptr!=0){
				block *temp=ptr;
				ptr=ptr->next;
				delete ptr;
			}
		}
};
	public:	
	SLL_blocks * block_record; 
	
	int id;
	int size;
	Program* next;
	
		Program(){
			id=0;
			size=0;
			next=0;
		}
		Program(int id_1, int size_1, int *strt){
			id=id_1;
			size=size_1;
			block_record=new SLL_blocks();
			block_record->add_block(strt,size_1);
			next=0;
		}
		void assign_Memory(int size_1, int * start_byte){
			block_record->add_block(start_byte,size_1);
			size+=size_1;
		}
		
		void shrink(){
			
			size=size-block_record->shrink();
			
		}
		int getSize(){
			return block_record->getSize();
		}
		
		int getStart(){
			return block_record->getStart();
		}
		void print(){
			block_record->print();
			}
		
		
		
	
};

Program * head;
Program * tail;

public:
	SLL_Progs(){
		head=new Program();
		tail=new Program();//using dummies nodes at head & tail
	}
	void add_prog(int id, int size, int *strt){
		
		Program* ptr=new Program(id, size, strt);
			
		if(head->next==0 ){
			
				head->next=ptr;
				ptr->next=tail;
			}
			else{	//check else
				Program * check=head;
				
				while(check->next!=tail){
					check=check->next;
				}
				//cout<<"OK";
				check->next=ptr;
				ptr->next=tail;
			}
			
	}
	
	void assign_memory(int id,int size, int * start_bytes){
		Program * ptr=head;
		bool flag=0; //finding particular program to update memory
		while(ptr->next!=0){
			if(ptr->next->id==id){
				flag=1;
				break;
			}
			else{
				ptr=ptr->next;
			}
			
		}
		if(!flag){
			cout<<"Invalid Program id!";	
			}
		else{
			ptr=ptr->next;
			ptr->assign_Memory(size, start_bytes);
		}
		
		
	}
	void shrink(int id_1){
		
		Program *ptr=head;
		while(ptr->id!=id_1){
			ptr=ptr->next;
		}
		
		ptr->shrink();
	}
	
	Program* find_Program(int id){	//use in .shrink method
		Program *ptr=head;
		while(ptr->id!=id && ptr->next->id!=0){
			ptr=ptr->next;
		}
		if(ptr->id==id){
			return ptr;
		}
		else{
			return 0;
		}
	}
	int getStart(int id){
		Program*ptr=find_Program(id);
		return ptr->getStart();
	}
	int getSize(int id){
		Program*ptr=find_Program(id);
		return ptr->getSize();
	}
	
	void terminate(int id1){
		Program * ptr=head;
		
		while(ptr->next->id!=id1 && ptr->next->id!=0){
			ptr=ptr->next;
		}
		if(ptr->next->id==id1){
			Program * temp=ptr->next;
			ptr->next=ptr->next->next;
			delete temp;
		}
		else{
			cout<<"Program "<<id1<<" does not exist"<<endl;
		}
		
		
	}
	
	void print_1(){
		Program *ptr=head;
		
		if(head->next!=0){
		
		while(ptr->next->id!=0){ //because of dummy node at tail
			cout<<endl;
			cout<<"Program id: ";
			cout<<ptr->next->id<<endl;
			cout<<"Program size: "<<ptr->next->size<<endl;
			cout<<"Memory taken by Program "<<endl;
			ptr->next->block_record->print();
			
			ptr=ptr->next;
			
		}	
	}
	else{
		cout<<"No Programs currently running"<<endl;
	}
}
	~SLL_Progs(){
		Program *ptr=head;
		while(ptr->next!=0){
			Program*temp=ptr;
			ptr=ptr->next;
			delete temp;
		}
		
	
}
};


class MemoryManagementSystem{
	int memory_size;
	bool strategy; // 0 for first fit, 1 for best fit
	SLL_memory Memory;
	SLL_Progs Programs;
	public:
	MemoryManagementSystem(){
		memory_size=0;
		strategy=0;
		
	}
	MemoryManagementSystem(int size, bool str){
		memory_size=size;
		strategy=str;
		Memory.assign_memory(size);
		
	}
	void create_Blocks(int size){
		Memory.add_fragment(size);
	}
	void Add_Program(int id, int size){
		if(strategy==0){
			int *ptr=Memory.assign_memory(size);
			if(*ptr!=-1){
			Programs.add_prog(id,size, ptr);	
		}
			else{
				delete ptr;
			}
		}
		else{
		int * ptr=Memory.assign_memory_best_fit(size);
		if(*ptr!=-1){
		Programs.add_prog(id,size,ptr);
	}
		else{
			delete ptr;
		}
	}
			
	}
	void Extend_Program(int id,int size){
		if(strategy==0){
		int * ptr=Memory.assign_memory(size);
		if(*ptr!=-1){
		Programs.assign_memory(id,size,ptr);
	}
		else{
			delete ptr;
		}
	}
	else{
		int * ptr=Memory.assign_memory_best_fit(size);
		if(*ptr!=-1){
		Programs.assign_memory(id,size,ptr);
	}
		else{
			delete ptr;
		}
	}
		
	}
	void Shrink_Program(int id){
		if(Programs.getSize(id)!=-1|| Programs.getStart(id)!=-1){
		
		Memory.SetFree(Programs.getStart(id),Programs.getSize(id));
		Programs.shrink(id);
	}
		else{
			cout<<"Program "<<id<<" already have 0 memory!"<<endl;
		}
	}
	void Terminate_Program(int id){
		if(Programs.find_Program(id)!=0){
		
		while(Programs.getSize(id)!=-1|| Programs.getStart(id)!=-1){
			Memory.SetFree(Programs.getStart(id),Programs.getSize(id));
			Programs.shrink(id);
		}
		Programs.terminate(id);
	}
	else{
		cout<<"Program "<<id<<" does not exist!"<<endl;;
	}
		
		
	}
	void print(){
		cout<<"Memory Blocks:"<<endl;
		Memory.Print();
		cout<<"Program Blocks:"<<endl;
		Programs.print_1();
	}
	~MemoryManagementSystem(){
		SLL_memory* ptr=&Memory;
		SLL_Progs* ptr1=&Programs;
		delete  ptr;
		delete ptr1;
	}
};
int main(){
	int size;
	bool strt;
	char input;
	cout<<"Please enter size of memory to initailize:"<<endl;
	cin>>size;
	cout<<"Please Enter 0 for first fit or 1 for best fit:"<<endl;
	cin>>ws;
	cin>>strt;
//	cin>>ws;
	MemoryManagementSystem test (size, strt);
	
	cout<<"If you want to add fragments of memory, Enter Y:"<<endl;
	cin>>ws;
	cin>>input;
	
	while(input=='Y'){
		cout<<"Enter size of new block:";
		cin>>ws;
		cin>>size;
		test.create_Blocks(size);
		test.print();
		
		cout<<"Enter Y to create new fragments or any other character to exit:";
		cin>>ws;
		cin>>input;
	}
	
	cout<<"If you want to add program please enter A. If you want to extend, please enter E. If you want to shrink please enter S. If you want to terminate a Program please enter T.\nEnter Z to exit:"<<endl;
	cin>>ws;
	cin>>input;
	while(input!='Z'){
		if(input=='A'){
			int id,size;
			cout<<"Enter id of Program :";
			cin>>ws;
			cin>>id;
			cout<<"Enter size of Program :";
			cin>>ws;
			cin>>size;
			test.Add_Program(id,size);
			test.print();
			}
		else if(input =='E'){
			
			int id,size;
			cout<<"Enter id of program to be extended:"<<endl;
			cin>>ws;
			cin>>id;
			cout<<"Enter bytes to assign to Program:"<<endl;
			cin>>ws;
			cin>>size;
			test.Extend_Program(id,size);
			test.print();
		}
		else if(input =='S'){
			int id;
			cout<<"Enter id of program to be shrinked:"<<endl;
			cin>>ws;
			cin>>id;
			test.Shrink_Program(id);
			test.print();
		}
		else if(input =='T'){
			int id;
			cout<<"Enter id of program to be terminated:"<<endl;
			cin>>ws;
			cin>>id;
			test.Terminate_Program(id);
			test.print();
			
		}
		else{
			cout<<"Choose correct option"<<endl;
		}
		cout<<endl;
		cout<<"Choose an option:";	
		cin>>ws;
		cin>>input;		
		}
		test.print();
	
	

	
	system ("pause");
	
	return 0;
}
