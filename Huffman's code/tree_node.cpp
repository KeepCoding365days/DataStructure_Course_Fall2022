#include "Node.cpp"
#include <vector>
class Tree{
	Node* root;
	void print(Node* ptr) {//------
		if (ptr != nullptr) {
			
			ptr->Print();
			//if(ptr->left!=nullptr)
			print(ptr->left);
			//if(ptr->right!=nullptr)
			print(ptr->right);
		}
	}
public:
	Tree() {
		root = nullptr;
		
	}
	Tree(Node* ptr) {
		root = ptr;
		root->left = ptr->left;
		root->right = ptr->right;
	}
	void Print() {
		print(root);
	}
	void assign_path(Node*ptr,string c,vector<dict>& list) {
		//Node* ptr = root;
		if (ptr->left == nullptr && ptr->right == nullptr) {
			bool check = false;
			for (auto i = list.begin(); i != list.end() &&! check; i++) {
				if ((*i).elem == ptr->data) {
					(*i).path = c;
					check = true;
				}
			}
		}

		else {
			assign_path(ptr->left, c + "0", list);
			assign_path(ptr->right, c + "1", list);
		}
		
	}
	void assign_path(vector <dict>& list) {
		assign_path(root, "", list);
	}
	Node* getRoot() {
		return root;
	}
	void Print1() {
		cout << root->data << "\t" << root->freq << endl;
		cout << root->left->data << "\t" << root->left->freq << endl;
		cout << root->right->data << "\t" << root->right->freq << endl;
		cout << root->right->left->data << "\t" << root->right->left->freq << endl;
		cout << root->right->right->data << "\t" << root->right->right->freq << endl;
		cout << root->left->left->data << "\t" << root->left->left->freq << endl;
		cout << root->left->right->data << "\t" << root->left->right->freq << endl;
		cout << root->left->right->left->data << "\t" << root->left->right->left->freq << endl;
		cout << root->left->right->right->data << "\t" << root->left->right->right->freq << endl;
	}
};