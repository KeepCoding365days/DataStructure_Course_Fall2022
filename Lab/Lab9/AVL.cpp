//change height after single rotation, add double rotation check height again
/*Helper:
	Doube rotation done. Check once more and go to deletion
*/
#pragma once

#include <iostream>
using namespace std;
template <class T>
class AVL {
	struct Node {
		T data;
		
		int height;
		Node* left;
		Node* right;
		Node() {
			left = nullptr;
			right = nullptr;
			data = 0;
			height = 0;
		}
		Node(T input) {
			left = nullptr;
			right = nullptr;
			data = input;
			
			height = 0;
		}
	};
	Node* root;

	bool delete_R(T val, Node* ptr) {
		if (ptr->data == val) {
			return delete_Node(ptr);
		}
		else if (ptr->data > val) {
			return delete_R(val, ptr->left);
		}
		else if (ptr->data < val) {
			return delete_R(val, ptr->right);
		}

	}

	bool delete_Node(Node* ptr) {
		//cout << ptr->data;
		if (ptr->left == nullptr && ptr->right == nullptr) {
			if (ptr == root) {
				delete ptr;
				root = nullptr;

				return true;
			}
			else {
				//delete ptr;
				Node* temp1 = root;
				while (temp1->left != ptr && temp1->right != ptr) {
					if (temp1->data > ptr->data) {
						temp1 = temp1->left;
					}
					else {
						temp1 = temp1->right;
					}
				}
				//cout << temp1->data;
				if (temp1->left == ptr) {
					temp1->left = nullptr;
					if (temp1->right != nullptr) {
						temp1->height = temp1->right->height + 1;
					}
					else {
						temp1->height = 0;
					}
				}
				else {
					temp1->right = nullptr;
					if (temp1->left != nullptr) {
						temp1->height = temp1->left->height + 1;
					}
					else {
						temp1->height = 0;
					}
				}

				delete ptr;
				//ptr = nullptr;
				set_height(temp1);
				balanceTree(root, temp1);
				//this->print();
				return true;
			}
		}
		else if (ptr->left != nullptr && ptr->right == nullptr) {
			if (ptr == root) {

				root = root->left;
				Node* temp = ptr;
				delete temp;

				return true;
			}
			else {
				Node* temp1 = root;
				if (ptr != root) {
					while (temp1->left != ptr && temp1->right != ptr) {
						if (temp1->data > ptr->data) {
							temp1 = temp1->left;
						}
						else {
							temp1 = temp1->right;
						}
					}
				}
				if (temp1->left == ptr) {
					temp1->left = ptr->left;
					set_height(temp1->left);
				}
				else {
					temp1->right = ptr->left;
					set_height(temp1->right);
				}
				Node* temp;
				temp = ptr;
				//ptr = ptr->left;
				delete temp;
				//temp = nullptr;
				balanceTree(root, temp1);

				return true;
			}
		}
		else if (ptr->right != nullptr && ptr->left == nullptr) {
			if (ptr == root) {

				root = root->right;
				Node* temp = ptr;
				delete temp;

				return true;
			}
			else {
				Node* temp1 = root;
				while (temp1->left != ptr && temp1->right != ptr) {
					if (temp1->data > ptr->data) {
						temp1 = temp1->left;
					}
					else {
						temp1 = temp1->right;
					}
				}
				if (temp1->left == ptr) {
					temp1->left = ptr->right;
					set_height(temp1->left);
				}
				else {
					temp1->right = ptr->right;
					set_height(temp1->right);
				}
				Node* temp;
				temp = ptr;
				//ptr = ptr->right;
				delete temp;
				//temp = nullptr;
				balanceTree(root, temp1);
				return true;
			}
		}
		else {

			if (ptr == root) {
				cout << "A";
				Node* prev = ptr;//settting child nodes of previous in all 
				Node* temp = find_Predecessor(ptr->left, prev);
				cout << root->data;
				root->data = temp->data;
				cout << root->data;
				delete_Node(temp);
				/*if (prev->left ==temp) {
					delete_Node(prev->left);
				}
				else {
					delete_Node(prev);
				}*/
				//delete temp;
				//temp=nullptr;
				if (prev->left == nullptr && prev->right == nullptr) {
					prev->height = 0;
				}
				else if (prev->left != nullptr && prev->right != nullptr)//maybe unnecessary check, see it later
					prev->left->height > prev->right->height ? prev->height = prev->left->height + 1 : prev->height = prev->right->height + 1;	//checking if left child has more height or right child and assigning it to root
				else if (prev->left == nullptr)
					prev->height = prev->right->height + 1;
				else {
					prev->height = prev->left->height + 1;
				}
				if (root == nullptr) {
					cout << "B";
				}
				//set_height(prev);
				if (prev->left != nullptr) {
					cout << "C";
					balanceTree(root, prev->left);
				}
				else {
					balanceTree(root, prev);
				}
				/*if (root == nullptr) {
					cout << "A";
				}*/
				//cout << root->data;

				return true;
			}
			else {
				Node* temp;
				Node* prev = ptr;//settting child nodes of previous in all 
				temp = find_Predecessor(ptr->left, prev);//prev parsed by referene
				ptr->data = temp->data;
				if (prev->left == ptr) {
					prev->left = nullptr;
				}
				else {
					prev->right = nullptr;
				}
				delete temp;
				//temp=nullptr;
				if (prev->left == nullptr && prev->right == nullptr) {
					prev->height = 0;
				}
				else if (prev->left != nullptr && prev->right != nullptr)//maybe unnecessary check, see it later
					prev->left->height > prev->right->height ? prev->height = prev->left->height + 1 : prev->height = prev->right->height + 1;	//checking if left child has more height or right child and assigning it to root
				else if (prev->left == nullptr)
					prev->height = prev->right->height + 1;
				else {
					prev->height = prev->left->height + 1;
				}
				set_height(prev);
				if (prev->left != nullptr) {
					balanceTree(root, prev->left);
				}
				else {
					balanceTree(root, prev);
				}
				return true;
			}
		}
	}
	Node* find_Predecessor(Node* ptr, Node*& prev) {
		if (ptr->right == nullptr) {
			return ptr;
		}
		else {
			prev = ptr;
			find_Predecessor(ptr->right, prev);
		}
	}
	void clean_memory(Node* ptr) {
		if (ptr != nullptr) {
			if (ptr->left == nullptr && ptr->right == nullptr) {
				if (ptr != root) {

					Node* temp = findLeftupper(ptr->data, root);
					if (temp->left == ptr) {
						temp->left = nullptr;
					}
					else {
						temp->right = nullptr;
					}
					delete ptr;
				}
				else {
					delete ptr;
				}
			}
			else if (ptr->left == nullptr && ptr->right != nullptr) {
				clean_memory(ptr->right);
			}
			else if (ptr->left != nullptr && ptr->right == nullptr) {
				clean_memory(ptr->left);
			}
			else {
				clean_memory(ptr->left);
				clean_memory(ptr->right);
				clean_memory(ptr);
			}
		}
	}
	Node* findLeftupper(T N, Node* ptr) {
		if (ptr->left != nullptr && ptr->left->data == N) {
			return ptr;
		}
		else if (ptr->right != nullptr && ptr->right->data == N) {
			return ptr;
		}

		else if (ptr->data > N) {
			return findLeftupper(N, ptr->left);
		}
		else if (ptr->data < N) {
			return findLeftupper(N, ptr->right);
		}
	}
	void Display(Node* ptr, Node* prev, bool upper) {
		if (root != nullptr) {
			if (ptr->left == nullptr && ptr->right == nullptr) {

				if (ptr != prev->right) {
					cout << ptr->data << "\t";
					cout << prev->data << "\t";

				}
				if (prev->left != ptr && ptr != root) {
					if (prev->left == nullptr || upper)
						cout << prev->data << "\t";
					cout << ptr->data << "\t";
					Node* ptr1 = findLeftupper(prev->data, root);

					if (ptr1->left == prev) {
						cout << ptr1->data << "\t";
						Display(ptr1->right, ptr1, false);
					}
					else {

						Display(ptr1->right, ptr1, true);
					}

				}
				else if (prev->right == nullptr) {
					Node* ptr1 = findLeftupper(prev->data, root);
					cout << ptr1->data << "\t";
					Display(ptr1->right, ptr1, false);
				}
				else if (prev->right != ptr) {

					Display(prev->right, prev, false);
				}
			}
			else if (!upper && ptr->left != nullptr) {
				//cout << 'A';

				Display(ptr->left, ptr, false);
			}
			else if (!upper && ptr->right != nullptr) {
				Display(ptr->right, ptr, false);
			}
			else if (upper) {
				//cout << ptr->data;
				if (prev != root) {
					Node* ptr1 = findLeftupper(prev->data, root);
					if (ptr1->left->data == ptr->data) {
						Display(ptr1->left, ptr1, true);
					}
					else {
						Display(ptr1->right, ptr1, true);
					}
				}

			}
		}
	}


public:
	AVL() {
		root = nullptr;
	}
	void Insert(T N) {
		Node* curr = root;
		Node* temp = curr;

		Node* temp1 = new Node(N);
		if (root == nullptr) {
			root = temp1;
		}
		else {
			while (curr != nullptr) {
				temp = curr;
				if (curr->data > N) {
					curr = curr->left;
				}
				else {
					curr = curr->right;
				}
			}
			if (N > temp->data) {
				temp->right = temp1;
			}
			else if (N < temp->data) {
				temp->left = temp1;
			}
			//temp = temp1;
		}


		height_inc(temp1);
		balanceTree(root, temp1);

	}
	void set_height(Node* ptr) {
		Node* ptr1 = root;
		Node* prev = root;
		Node* temp;

		if (ptr != ptr1) {
			while (ptr1->left != ptr && ptr1->right != ptr) {
				prev = ptr1;
				if (ptr1->data > ptr->data) {
					ptr1 = ptr1->left;
				}
				else {
					ptr1 = ptr1->right;
				}

			}
		}
		if (ptr1->left == nullptr && ptr1->right == nullptr) {
			ptr1->height = 0;
		}
		else if (ptr1->left != nullptr && ptr1->right != nullptr)//maybe unnecessary check, see it later
			ptr1->left->height > ptr1->right->height ? ptr1->height = ptr1->left->height + 1 : ptr1->height = ptr1->right->height + 1;	//checking if left child has more height or right child and assigning it to root
		else if (ptr1->left == nullptr)
			ptr1->height = ptr1->right->height + 1;
		else {
			ptr1->height = ptr1->left->height + 1;
		}
		if (ptr1 != root) {
			set_height(prev);
		}


	}
	void height_inc(Node* temp) {
		Node* ptr = root;
		/*if (ptr != temp) {
			//ptr->height++;
		}*/
		while (ptr != temp) {
			if (temp->data < ptr->data) {
				if (ptr->left != temp) {
					if ((ptr->left->left != temp && ptr->left->right != temp) || ptr->left->height == 0) {
						ptr->left->height++;
					}
				}

				if (ptr->left == nullptr && ptr->right == nullptr) {
					ptr->height = 0;
				}
				else if (ptr->left != nullptr && ptr->right != nullptr)//maybe unnecessary check, see it later
					ptr->left->height > ptr->right->height ? ptr->height = ptr->left->height + 1 : ptr->height = ptr->right->height + 1;	//checking if left child has more height or right child and assigning it to root
				else if (ptr->left == nullptr)
					ptr->height = ptr->right->height + 1;
				else {
					ptr->height = ptr->left->height + 1;
				}
				ptr = ptr->left;

			}
			else if (temp->data > ptr->data) {
				if (ptr->right != temp) {
					if ((ptr->right->left != temp && ptr->right->right != temp) || ptr->right->height == 0) {
						ptr->right->height++;
					}
				}

				if (ptr->left == nullptr && ptr->right == nullptr) {
					ptr->height = 0;
				}
				else if (ptr->left != nullptr && ptr->right != nullptr)//maybe unnecessary check, see it later
					ptr->left->height > ptr->right->height ? ptr->height = ptr->left->height + 1 : ptr->height = ptr->right->height + 1;	//checking if left child has more height por right child and assigning it to root
				else if (ptr->left == nullptr)
					ptr->height = ptr->right->height + 1;
				else {
					ptr->height = ptr->left->height + 1;
				}
				ptr = ptr->right;
			}
		}
	}
	void heightdecr() {

	}
	void balanceTree(Node* base, Node* temp) {
		//cout << temp->data << "\t" << bf(temp);
		if (bf(temp) > 1 || bf(temp) < -1) {
			if (bf(temp) > 1) {	//for single rotation if tree is unbalanced
				//cout << temp->data;
				if (bf(temp->right) < 0) {
					//cout << "RL";
					//cout << temp->data;
					//this->print();
					rightRotate(temp->right);
					//this->print();
					leftRotate(temp);

				}
				else {

					//cout << temp->data;
					leftRotate(temp);
				}
			}
			else {

				if (bf(temp->left) > 0) {

					leftRotate(temp->left);
					rightRotate(temp);
				}
				else {

					rightRotate(temp);
				}


			}

			balanceTree(root, temp);

		}
		else if (temp == root) {

		}
		else {
			if (temp != root) {
				while (base->left != temp && base->right != temp) {	//going upward if level is balanced

					if (temp->data > base->data) {
						base = base->right;
					}
					else {
						base = base->left;
					}
				}
			}
			else {
				base = root;
			}
			balanceTree(root, base);
		}


	}
	void leftRotate(Node* temp) {
		Node* ptr = root;
		if (temp != root) {

			while (ptr->left != temp && ptr->right != temp) {
				if (temp->data > ptr->data) {
					ptr = ptr->right;
				}
				else {
					ptr = ptr->left;
				}
			}

			if (ptr->data > temp->data) {
				ptr->left = temp->right;
				if (ptr->left->left != nullptr)
					cout << ptr->left->left->data;
				Node* temp1 = temp->right->left;
				ptr->left->left = temp;
				temp->right = temp1;

			}
			else {
				ptr->right = temp->right;
				if (temp->right->left != nullptr)
					cout << temp->right->left->data;
				Node* temp1 = temp->right->left;
				ptr->right->left = temp;
				temp->right = temp1;
			}
			//changing height we need to modify the height of node coming up, going down and parent one
			if (temp->left == nullptr && temp->right == nullptr) {
				temp->height = 0;
			}
			else if (temp->left != nullptr && temp->right != nullptr)//maybe unnecessary check, see it later
				temp->left->height > temp->right->height ? temp->height = temp->left->height + 1 : temp->height = temp->right->height + 1;	//checking if left child has more height por right child and assigning it to root
			else if (temp->left == nullptr)
				temp->height = temp->right->height + 1;
			else {
				temp->height = temp->left->height + 1;
			}
			if (ptr->right != nullptr) {
				if (ptr->right->left == nullptr && ptr->right->right == nullptr) {
					ptr->right->height = 0;
				}
				else if (ptr->right->left != nullptr && ptr->right->right != nullptr)//maybe unnecessary check, see it later
					ptr->right->left->height > ptr->right->right->height ? ptr->right->height = ptr->right->left->height + 1 : ptr->right->height = ptr->right->right->height + 1;	//checking if left child has more height por right child and assigning it to root
				else if (ptr->right->left == nullptr)
					ptr->right->height = ptr->right->right->height + 1;
				else {
					ptr->right->height = ptr->right->left->height + 1;
				}
			}
			if (ptr->left != nullptr) {
				if (ptr->left == nullptr && ptr->right == nullptr) {
					ptr->height = 0;
				}
				else if (ptr->left != nullptr && ptr->right != nullptr)//maybe unnecessary check, see it later
					ptr->left->height > ptr->right->height ? ptr->height = ptr->left->height + 1 : ptr->height = ptr->right->height + 1;	//checking if left child has more height por right child and assigning it to root
				else if (ptr->left == nullptr)
					ptr->height = ptr->right->height + 1;
				else {
					ptr->height = ptr->left->height + 1;
				}
			}
		}
		else {
			root = temp->right;
			Node* temp1 = root->left;
			root->left = temp;
			temp->right = temp1;
			//when we rotate root only two nodes need to modify their height
			if (temp->left == nullptr && temp->right == nullptr) {
				temp->height = 0;
			}
			else if (temp->left != nullptr && temp->right != nullptr)
				temp->left->height > temp->right->height ? temp->height = temp->left->height + 1 : temp->height = temp->right->height + 1;	//checking if left child has more height por right child and assigning it to temp

			else if (temp->left == nullptr)
				temp->height = temp->right->height + 1;
			else {
				temp->height = temp->left->height + 1;
			}

			if (root->left == nullptr && root->right == nullptr) {
				root->height = 0;
			}
			else if (root->left != nullptr && root->right != nullptr)//maybe unnecessary check, see it later
				root->left->height > root->right->height ? root->height = root->left->height + 1 : root->height = root->right->height + 1;	//checking if left child has more height por right child and assigning it to root
			else if (root->left == nullptr)
				root->height = root->right->height + 1;
			else {
				root->height = root->left->height + 1;
			}
		}
		/*if (root->left->height > root->right->height) {
				root->height = root->left->height + 1;
			}
			else {
				root->height = root->right->height + 1;
			}*/

	}
	void rightRotate(Node* temp) {
		//cout << "R";
		//cout << temp->data;
		Node* ptr = root;
		if (temp != root) {
			while (ptr->right != temp && ptr->left != temp) {
				if (temp->data > ptr->data) {
					ptr = ptr->right;
				}
				else {
					ptr = ptr->left;
				}

			}
			//cout << ptr->data;
			if (ptr->data > temp->data) {
				ptr->left = temp->left;
				Node* temp1 = ptr->left->right;
				if (temp1 == nullptr)
					//cout << "A";
					ptr->left->right = temp;
				temp->left = temp1;
			}
			else {
				ptr->right = temp->left;
				Node* temp1 = ptr->right->right;
				//if (temp1 == nullptr)
					//cout << "A";
				ptr->right->right = temp;
				temp->left = temp1;
			}
			if (temp->left == nullptr && temp->right == nullptr) {
				temp->height = 0;
			}
			else if (temp->left != nullptr && temp->right != nullptr)//maybe unnecessary check, see it later
				temp->left->height > temp->right->height ? temp->height = temp->left->height + 1 : temp->height = temp->right->height + 1;	//checking if left child has more height por right child and assigning it to root
			else if (temp->left == nullptr)
				temp->height = temp->right->height + 1;
			else {
				temp->height = temp->left->height + 1;
			}
			set_height(temp);
			//if (ptr->right->left != nullptr) {
			//	if (ptr->left->left == nullptr && ptr->left->right == nullptr) {
			//		ptr->left->height = 0;
			//	}
			//	else if (ptr->left->left != nullptr && ptr->left->right != nullptr)//maybe unnecessary check, see it later
			//		ptr->left->left->height > ptr->left->right->height ? ptr->left->height = ptr->left->left->height + 1 : ptr->left->height = ptr->left->right->height + 1;	//checking if left child has more height por right child and assigning it to root
			//	else if (ptr->left->left == nullptr)
			//		ptr->left->height = ptr->left->right->height + 1;
			//	else {
			//		ptr->left->height = ptr->left->left->height + 1;
			//	}
			//}
			//if (ptr->left == nullptr && ptr->right == nullptr) {
			//	ptr->height = 0;
			//}
			//else if (ptr->left != nullptr && ptr->right != nullptr)//maybe unnecessary check, see it later
			//	ptr->left->height > ptr->right->height ? ptr->height = ptr->left->height + 1 : ptr->height = ptr->right->height + 1;	//checking if left child has more height por right child and assigning it to root
			//else if (ptr->left == nullptr)
			//	ptr->height = ptr->right->height + 1;
			//else {
			//	ptr->height = ptr->left->height + 1;
			//}
		}

		else {

			root = temp->left;
			Node* temp1 = root->right;
			root->right = temp;
			temp->left = temp1;

			if (temp->left == nullptr && temp->right == nullptr) {
				temp->height = 0;
			}
			else if (temp->left != nullptr && temp->right != nullptr)
				temp->left->height > temp->right->height ? temp->height = temp->left->height + 1 : temp->height = temp->right->height + 1;	//checking if left child has more height por right child and assigning it to temp

			else if (temp->left == nullptr)
				temp->height = temp->right->height + 1;
			else {
				temp->height = temp->left->height + 1;
			}
			if (root->left == nullptr && root->right == nullptr) {
				root->height = 0;
			}
			else if (root->left != nullptr && root->right != nullptr)//maybe unnecessary check, see it later
				root->left->height > root->right->height ? root->height = root->left->height + 1 : root->height = root->right->height + 1;	//checking if left child has more height por right child and assigning it to root
			else if (root->left == nullptr)
				root->height = root->right->height + 1;
			else {
				root->height = root->left->height + 1;
			}
		}

	}
	int bf(Node* temp) {
		int balance;
		if (temp == nullptr) {
			balance = 0;
		}
		else if (temp->right != nullptr && temp->left != nullptr) {
			balance = temp->right->height - temp->left->height;
		}
		else if (temp->right == nullptr && temp->left != nullptr) {
			balance = -1 - temp->left->height;
		}
		else if (temp->left == nullptr && temp->right != nullptr) {
			balance = temp->right->height + 1;
		}
		else {
			balance = 0;
		}
		return balance;
	}
	bool delete_R(T val) {
		return delete_R(val, root);
	}
	void print(Node* ptr) {//------
		if (ptr != nullptr) {
			cout << ptr->data << "\t" << ptr->height << endl;
			print(ptr->left);

			print(ptr->right);
		}
	}
	/*Data* find(T N) {
		Node* curr = root;
		bool check = false;

		while (curr != nullptr && !check) {
			if (curr->data > N) {
				curr = curr->left;
			}
			else if (curr->data < N) {
				curr = curr->right;
			}
			else {
				check = true;
			}
		}
		if (check) {
			return curr->ptr;
		}
		else {
			return nullptr;
		}


	}*/
	void print() {
		print(root);
	}
	T findMax(Node* ptr) {
		
		if (ptr->right == nullptr) {
			return ptr->data;
			
		}
		else {
			return findMax(ptr->right);
		}
	}
	T findSecondMax(Node* ptr) {
		//cout << "a";
		if (ptr->right == nullptr) {
			if (ptr != root) {
				//cout << ptr->data;
				Node* temp = findLeftupper(ptr->data, root);
				return temp->data;
			}
			else {
				return ptr->data;
			}

		}
		else {
			return findSecondMax(ptr->right);
		}
	}
	T findThirdMax(Node* ptr) {
		//cout << "a";
		if (ptr->right == nullptr) {
			if (ptr != root) {
				//cout << ptr->data;
				Node* temp = findLeftupper(ptr->data, root);
				
				if (temp->left == nullptr) {
					if (temp != root) {
						temp = findLeftupper(temp->data, root);
						return temp->data;
					}
					else {
						return root->data;
					}
				}
				else {
					temp = find_Predecessor(temp->left,temp);
					return temp->data;
				}
			}
			else {
				return ptr->data;
			}

		}
		else {
			return findThirdMax(ptr->right);
		}
	}
	T findMax() {
		return findMax(root);
	}
	T findSecondMax() {
		return findSecondMax(root);
	}
	T findThirdMax() {
		return findThirdMax(root);
	}
	void Display() {
		Display(root, root, false);

	}
	~AVL() {
		clean_memory(root);
	}
};

int main() {
	AVL <int>obj;
	obj.Insert(4);
	obj.Insert(5);
	obj.Insert(9);
	obj.Insert(12);
	//obj.Insert(8);
	obj.Insert(3);
	
	obj.print();
	cout << "Maximum is " << obj.findMax() << endl;
	cout << "Second Maximum is " << obj.findSecondMax() << endl;
	cout << "Third Maximum is " << obj.findThirdMax() << endl;
	cout << "InOrder traversal:" << endl;
	obj.Display();
	system("pause");
	return 0;
}
