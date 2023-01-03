#pragma once
//#include "Node.cpp"
#include"tree_node.cpp"
#include "minHeap.cpp"
#include<string>
//#include<vector>
#include<fstream>
//#include<iostream>
//using namespace std;

void Decompression(string f_name, Tree obj);
void Decompression(string f_name);
void Compress(string file_name,Tree*&tree);
void Compress(string file_name,Tree*&tree) {
	//Node tree;
	MinHeap data;
	vector<dict> uniq_char;
	vector<Node*> arr;
	ifstream inFile;
	inFile.open(file_name);
	bool exist;
	int size = 0;
	char temp;
	
	while (!inFile.eof()) {	//storing all the unique characters and their frequencyin arr vector 
		bool exist = false;
		inFile >> temp;	//checking id character already exit in arr. if no add it else inrement its freq
		for (auto i = arr.begin(); i != arr.end(); i++) {
			if ((*i)->data == temp) {
				exist = true;
				(*i)->freq++;
			}
		}
		
		if (!exist) {
			arr.push_back(new Node(temp,1));
			uniq_char.push_back(temp);
		}
	}
	for (auto i = uniq_char.begin(); i != uniq_char.end(); i++) {
		(*i).Print();
	}
	//cout << endl;
	
	for (auto i = arr.begin(); i != arr.end(); i++) { //inserting into minheap
		data.Insert((*i)->data,(*i)->freq);
	}
	
	data.print();
	cout << "Tree:" << endl;
	while (!data.isEmpty()) {
		
		Node *temp1=nullptr;
		Node *temp2=nullptr;
		if (data.getSize() != 0) {
			temp1 = data.dequeue();
		}
		if (data.getSize() != 0) {
			temp2 = data.dequeue();
		}
		//temp1.Print();
		//temp2.Print();
		//cout << 5;
		Node *temp=new Node('\0', temp1->freq + temp2->freq, temp1, temp2);
		//temp.Print1();
		data.Insert(temp);
		if(data.getSize()==1){
			temp->Print1();
			//data.getItem(0).Print1();
			tree =new Tree( data.dequeue());
			
		}
		//cout << "Tree" << endl;
		//temp.Print1();
		//cout << "Data:"<<endl;
		//data.print();
		
	}
	
	//assigning path to unique char
	tree->assign_path(uniq_char);
	for (auto i = uniq_char.begin(); i != uniq_char.end(); i++) {
		(*i).Print();
	}
	
	//Node temp(tree.data,tree.freq,tree.left,tree.right);
	/*while (tree.left != nullptr) {
		tree.left = tree.left;
		tree.right = tree.right;
	}*/

	//tree.Print1();
	//Tree dict(&tree);
	//dict.Print();
	char c;
	inFile.close();
	string f2 = "Compressed.txt";
	ofstream OutFile;
	OutFile.open(f2);
	inFile.open(file_name);
	while (!inFile.eof()) {
		inFile >> c;
		bool check = false;
		for (auto i = uniq_char.begin(); i != uniq_char.end()&& ! check; i++) {
			if ((*i).elem == c) {
				check = true;
				OutFile << (*i).path;
			}
		}


	}
	inFile.close();
	OutFile.close();
	//return tree;
}
void Decompression(string f_name, Tree *obj) {
	ifstream inFile;
	ofstream outFile;
	string f_name2 = "uncompressed.txt";
	char c;
	inFile.open(f_name);
	outFile.open(f_name2);
	Node* ptr = obj->getRoot();
	while (!inFile.eof()) {
		inFile >> c;
		if (c == '0') {
			ptr = ptr->left;
		}
		else if (c == '1') {
			ptr = ptr->right;
		}
		if (ptr->left == nullptr && ptr->right == nullptr) {
			outFile << ptr->data;
			ptr = obj->getRoot();
		}
	}

	inFile.close();
	outFile.close();
}


int main() {
	Tree *temp;
	Compress("input.txt",temp);
	temp->Print1();
	Decompression("Compressed1.txt", temp);
	//temp.Print1();
	//tree obj(&temp);
	//obj.Print();
	//Node* l = new Node('a', 2, nullptr, nullptr);
	//l->Print();
	//Node* r = new Node('b', 2, nullptr, nullptr);
	//r->Print();
	//Node* temp = new Node('\0', 4,l, r);
	////temp = new Node('\0', 6, l, temp);
	//temp->Print1();

	system("pause");
	return 0;
}