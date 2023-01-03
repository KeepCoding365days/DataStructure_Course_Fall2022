#include <iostream>
using namespace std;
template <class T>
class BST {
	template <class T>
	struct Node {
		T data;
		Node<T>* left;
		Node<T>* right;
		Node(T d) {
			data = d;
			left = nullptr;
			right = nullptr;
		}
		Node(T d, Node*& l, Node*& r) {
			data = d;
			left = l;
			right = r;
		}
	};

	Node<T>* root;

	void leafsum(Node<T>* const ptr, int& sum) {
		Node<T>* temp = ptr;
		if (root != nullptr) {
			if (ptr->left == nullptr && ptr->right == nullptr) {
				sum++;
				//leafsum()
			}
			else if (ptr->left != nullptr && ptr->right == nullptr) {
				leafsum(ptr->left, sum);
			}
			else if (ptr->right != nullptr && ptr->left == nullptr) {
				leafsum(ptr->right, sum);
			}
			else if (ptr->left != nullptr && ptr->right != nullptr) {
				leafsum(ptr->right, sum);
				leafsum(ptr->left, sum);

			}
		}
	}

	void Insert_Recurssive(T val, Node<T>*& ptr) {

		if (ptr->data < val) {
			if (ptr->right == nullptr) {
				ptr->right = new Node<T>(val);
			}
			else {
				Insert_Recurssive(val, ptr->right);
			}
		}
		else if (ptr->data > val) {
			if (ptr->left == nullptr) {
				ptr->left = new Node<T>(val);
			}
			else {
				Insert_Recurssive(val, ptr->left);
			}
		}
	}

	bool delete_R(T val, Node<T>* ptr) {
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

	bool delete_Node(Node<T>* ptr) {
		if (ptr->left == nullptr && ptr->right == nullptr) {
			if (ptr == root) {
				delete ptr;
				return true;
			}
			else {
				delete ptr;
				return true;
			}
		}
		else if (ptr->left != nullptr && ptr->right == nullptr) {
			Node<T>* temp;
			temp = ptr;
			ptr = ptr->left;
			delete temp;
			return true;
		}
		else if (ptr->right != nullptr && ptr->left == nullptr) {
			Node<T>* temp;
			temp = ptr;
			ptr = ptr->right;
			delete temp;
			return true;
		}
		else {
			Node<T>* temp;
			Node<T>* prev = ptr;
			temp = find_Predecessor(ptr->left, prev);
			ptr->data = temp->data;
			if (prev == ptr) {
				prev->left = nullptr;
			}
			else {
				prev->right = nullptr;
			}
			delete temp;
			return true;
		}
	}
	Node<T>* find_Predecessor(Node<T>* ptr, Node<T>* prev) {
		if (ptr->right == nullptr) {
			return ptr;
		}
		else {
			prev = ptr;
			find_Predecessor(ptr->right, prev);
		}
	}

	void clean_memory(Node<T>* ptr) {
		if (ptr != nullptr) {
			if (ptr->left == nullptr && ptr->right == nullptr) {
				if (ptr != root) {
					
					Node<T>* temp = findLeftupper(ptr->data, root);
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

	Node<T>* findLeftupper(T N, Node<T>* ptr) {
		if (ptr->left != nullptr && ptr->left->data == N) {
				return ptr;
		}
		else if (ptr->right != nullptr&& ptr->right->data == N) {
				return ptr;
		}
		
		else if (ptr->data > N) {
			return findLeftupper(N, ptr->left);
		}
		else if (ptr->data < N) {
			return findLeftupper(N, ptr->right);
		}
	}
	void Display(Node<T>* ptr, Node<T>* prev, bool upper) {
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
					Node<T>* ptr1 = findLeftupper(prev->data, root);

					if (ptr1->left == prev) {
						cout << ptr1->data << "\t";
						Display(ptr1->right, ptr1, false);
					}
					else {

						Display(ptr1->right, ptr1, true);
					}

				}
				else if (prev->right == nullptr) {
					Node<T>* ptr1 = findLeftupper(prev->data, root);
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
					Node<T>* ptr1 = findLeftupper(prev->data, root);
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
	BST() {
		root = nullptr;
	}
	BST(BST& obj){
		if (obj.root != nullptr) {
			Node<T>* ptr = obj.root;
			root = new Node<T>(ptr->data,ptr->left,ptr->right);
			

		}

	}

	void Insert(T N) {
		Node<T>* curr = root;
		Node<T>* temp = curr;

		Node<T>* temp1 = new Node<T>(N);
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
			temp = temp1;
		}

	}
	bool find(T N) {
		Node<T>* curr = root;
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

		return check;

	}

	bool del(T N) {
		bool check = false, completed = false;
		Node<T>* curr = root;
		Node<T>* prev = curr;
		if (curr != nullptr) {
			if (curr->data == N) {
				check = true;
			}
		}
		else {
			completed = true;
		}
		if (curr != nullptr && !check && !completed) {
			//prev = curr;
			while (!check && !completed) {
				if (curr->data < N) {
					if (curr->right != nullptr) {
						prev = curr;
						curr = curr->right;
					}
					else {
						completed = true;
					}
				}
				else if (curr->data > N) {
					if (curr->left != nullptr) {
						prev = curr;
						curr = curr->left;
					}
					else {
						completed = true;
					}
				}
				else {
					check = true;
				}
			}
		}

		if (check) {
			if (curr->right == nullptr && curr->left == nullptr) {
				if (prev->right->data == N) {
					prev->right = nullptr;
				}
				else if (prev->left->data == N) {
					prev->left = nullptr;
				}
				delete curr;
			}
			else if (curr->left != nullptr && curr->right == nullptr) {
				if (prev->left->data == N) {
					prev->left = curr->left;
				}
				else {
					prev->right = curr->left;
				}
			}
			else if (curr->left == nullptr && curr->right != nullptr) {
				if (prev->left->data == N) {
					prev->left = curr->right;
				}
				else {
					prev->right = curr->right;
				}
			}
			else if (curr->left != nullptr && curr->right != nullptr) {
				prev = curr;
				Node<T>* temp = curr->left;					//replacing with predecessor
				while (temp->right != nullptr) {
					prev = temp;
					temp = temp->right;
				}

				if (prev != curr) {
					prev->right = nullptr;
				}
				else {
					prev->left = nullptr;
				}
				curr->data = temp->data;

				delete temp;
			}
		}

		return check;
	}


	void InsertR(T val) {
		if (root == nullptr) {
			root = new Node<T>(val);
		}
		else {
			Insert_Recurssive(val, root);
		}
	}
	bool delete_R(T val) {
		return delete_R(val, root);
	}


	void Display() {
		Display(root, root, false);
		

	}


	void leafsum(int& sum) {
		sum = 0;
		leafsum(root, sum);
	}




	~BST() {
		clean_memory(root);
	}
};
int main() {
	BST<int> tree;
	tree.Insert(5);
	tree.InsertR(10);
	tree.InsertR(3);
	tree.InsertR(12);
	tree.InsertR(7);
	tree.InsertR(6);
	tree.InsertR(8);
	tree.InsertR(2);
	tree.Insert(4);
	tree.delete_R(3);
	cout << "Finding 8:" << tree.find(8);
	//BST<int> tree_duplicate(tree);(Not deep copy that's why clash when destructor called)
	//tree.del(10);
	cout << "Tree";
	cout << endl;
	tree.Display();
	int s;
	tree.leafsum(s);
	cout << endl;
	cout << "Total leaves of tree are:";
	cout << s << endl;
	system("pause");

	return 0;
}
