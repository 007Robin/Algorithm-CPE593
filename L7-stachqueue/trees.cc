#include<iostream>
using namespace std;

class OrderedBinaryTree {
private:
	class Node {
		public:
			int val;
			Node* parent;
			Node* left;				// int* a,b; a is pointer to int, b is just int
			Node* right;
			Node(int v, Node* L, Node* R) : val(v), left(L), right(R) {}
			void print() {
				if( left != nullptr)
					left->print();
				cout << val;
				if( right != nullptr)
					right->print();
			}
	};
	Node * root;
public:
	OrderedBinaryTree() {
		root = nullptr;
	}
	void add(int v) {
		if (root == nullptr) {
			root = new Node(v, nullptr, nullptr);
			return;
		} 
		Node* p = root;
		while(p)  {
			if ( v < p->val) {
				if(p->left == nullptr) {
					p->left = new Node(v, nullptr, nullptr);
					return;
				}
				else {
					p = p->left;
				}
			}
			else {
				if(p->right == nullptr) {
					p->right = new Node(v, nullptr, nullptr);
					return;
				}
				else {
					p = p->right;
				}
			}		
		}
	}
	void print() {
		root->print();
	}
};

int main() {
//	OrderedBinaryTree t = new OrderedBinaryTree();
	OrderedBinaryTree t ;
	t.add(3);
	t.add(1);
	t.print();
}
