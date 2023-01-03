#pragma once
#include<iostream>
using namespace std;
struct dict {
	char elem;
	string path;

	dict() {
		elem = ' ';
		path = "";
	}
	dict(char c) {
		elem = c;
		path = "";
	}
	void addPath(char c) {
		path = path + c;
	}
	void Print() {
		cout << elem << ":" << path << endl;
	}
};
struct Node {
	char data;
	int freq;
	Node* left;
	Node* right;
	Node() {
		data = ' ';
		freq = 0;
		left = nullptr;
		right = nullptr;
	}
	Node(char dt, int fr) {
		data = dt;
		freq = fr;
		left = nullptr;
		right = nullptr;
	}
	Node(char dt, int fr, Node *l,Node* r) {
		data = dt;
		freq = fr;
		left = l;
		right = r;
	}
	Node(Node* temp) {
		if (temp == nullptr) {
		
		}
		else {
			*this = new Node(temp->data, temp->freq, temp->left, temp->right);
			Node(this->left);
			Node(this->right);
		}
		
	}
	void operator =(Node temp) {
		this->data = temp.data;
		this->freq = temp.freq;
		this->left = temp.left;
		this->right = temp.right;
	}
	void Print() {
		cout << data << "\t" << freq<<endl;
		//cout << left->data << "\t" << left->freq << endl;
		
	}
	void Print1() {
		cout << this->data << "\t" << this->freq << endl;
		cout << this->left->data << "\t" << this->left->freq << endl;
		cout << this->right->data << "\t" << this->right->freq << endl;
		cout << this->right->left->data << "\t" << this->right->left->freq << endl;
		cout << this->right->right->data << "\t" << this->right->right->freq << endl;
		cout << this->left->left->data << "\t" << this->left->left->freq << endl;
		cout << this->left->right->data << "\t" << this->left->right->freq << endl;
		cout << this->left->right->left->data << "\t" << this->left->right->left->freq << endl;
		cout << this->left->right->right->data << "\t" << this->left->right->right->freq << endl;
	}
	

};
