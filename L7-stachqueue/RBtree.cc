#include<iostream>
using namespace std;

class RBtree {
private:
	class Node {
		public:
			int val;
			Node* parent;
			Node* left;			
			Node* right;
			enum Color {Red, Black};
			Color c;
			Node(int v, Node* L, Node* R, Node* p) : val(v), left(L), right(R), parent(p) {
				c = Color.Red;
			}
			void print() {
				if( left != nullptr)
					left->print();
				cout << val;
				if( right != nullptr)
					right->print();
			}
			Node uncle() {
				if(parent == nullptr || parent.parent == nullptr)
					return nullptr;
				if(parent->parent->left == parent) { //if Gp's left child is my parent 
					return parent->parent->right;
				}
				else 
					return parent->parent->left;
			}
			void repair() {
				if( parent == nullptr)
					c = C.Black;
				else if(this->parent.c == Black)
					return;
				else {
					Node* g = parent->parent;
					Node* u = uncle();
					if(u != nullptr) {
						if( u.c == Red) {
							parent.c = Black;
							u.c = Black;
							g->c = Red;
							g->repair();
						}
						else { //case 4: 
							if(this == g->left->right) {
								parent.rotateLeft();
								this = this->left;
							}
							else if(this == g->right->left) {
								parent.rotateRight();
								this = this->right;
							}

							}
						}
					}
				
				}
			}
	};
	Node * root;
public:
	RBtree() {
		root = nullptr;
	}
	void add(int v) {
		if (root == nullptr) {
			root = new Node(v, nullptr, nullptr, nullptr);
			return;
		} 
		Node* p = root;
		while(p)  {
			if ( v < p->val) {
				if(p->left == nullptr) {
					p->left = new Node(v, nullptr, nullptr, p);
					repair();
					return;
				}
				else {
					p = p->left;
				}
			}
			else {
				if(p->right == nullptr) {
					p->right = new Node(v, nullptr, nullptr, p);
					repair();
					return;
				}
				else {
					p = p->right;
				}
			}		
		}
	}
	
	void repair() {

	}
	void print() {
		root->print();
	}
};

int main() {
//	RBtree t = new RBtree();
	RBtree t ;
	t.add(3);
	t.add(1);
	t.print();
}
