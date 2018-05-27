//Xin Song -- expression tree
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<queue>
using namespace std;

class Node{
public:
	string data;
	Node* left;
	Node* right;
	Node() {
		left = nullptr;
		right = nullptr;	
	}
	Node(string v) {
		data = v;
		left = nullptr;
		right = nullptr;	
	}

	void inorder() {
		if(left != nullptr)
			left->inorder();
		cout << data << " ";
		if(right != nullptr)
			right->inorder();
	}
	void postorder() {
		if(left != nullptr)
			left->postorder();
		
		if(right != nullptr)
			right->postorder();
		
		cout << data << " ";
	}
	~Node(){
		delete left;
		delete right;
	}

};

class EXtree{
private:
	Node* root;
public:
	EXtree() {
		root->left = root->right = nullptr;
	}
	Node* splitByMultiDivision(string s, Node* root) {
		auto i = s.find_first_of("*/");
		if(i == string::npos) 
			return new Node(s);
		string L = s.substr(0, i);
		string op = string(1, s[i]);
		string R = s.substr(i + 1);
//		cout << L << "    " << op << "   " << R << " ";
//		cout << '\n';
		Node *l, *r;
		if(L.find_first_of("*/") == string::npos) {
			l = new Node(L);
			root->left = l;
		}
		else 
			root->left = splitByMultiDivision(L, new Node());

		root->data = op;
		if(R.find_first_of("*/") == string::npos) {
			r = new Node(R);
			root->right = r;
		}
		else 
			root->right = splitByMultiDivision(R, new Node());
		
		return root;
	}

	Node* BuildExtree(string s){ 
		
		auto i = s.find_first_of("+-");
		if(i == string::npos) 
			return new Node(s);
		string op = string(1, s[i]);
		
		string L = giveLeft(s);
		if(L.find_first_of("*/") == string::npos) {
			root->left = new Node(L);
		}
		else { 
			root->left = splitByMultiDivision(L, new Node());
		}
		
		root->data = op;
	
		string R = giveOPright(s);
		if(R.find_first_of("*/") == string::npos) { 
			root->right = new Node(R);		
		}
		else {
			root->right = splitByMultiDivision(R, new Node());	
		}	
		
		return root;

	}
	Node* giveLeft(string s){ 	
		auto i = s.find_first_of("+-");
		if(i == string::npos) 
			return new Node(s);
		string L = s.substr(0, i);
		string op = string(1, s[i]);
		string allR = s.substr(i + 1);
		cout << L << "    " << op << "   ";
//		cout << '\n';
		
		if(L.find_first_of("*/") == string::npos) {
			root->left = new Node(L);
		}
		else { 
			root->left = splitByMultiDivision(L, new Node());
		}
		root->data = op;
		auto j = allR.find_first_of("+-");
		string R = allR.substr(0, j);
//		cout << R << " ";
		if(R.find_first_of("*/") == string::npos) { 
			root->right = new Node(R);		
		}
		else {
			root->right = splitByMultiDivision(R, new Node());	
		}	
		//return root;
		Node* r = new Node();
		r->left = root; 
		string op2 = string(1, s[j]);
		string allR2 = s.substr(j + 1);
		r->data = op2;
		r->right = BuildExtree(allR2);
		return r;
	}

	string giveOPleft(string s) {
		auto i = s.find_first_of("+-");
		if(i == string::npos) 
			return s;
		return s.substr(0, i);
	}

	string giveOPright(string s) {
		auto i = s.find_first_of("+-");
		if(i == string::npos) 
			return s;
		auto j = s.substr(i + 1).find_first_of("+-");
		return s.substr(i + 1, j - i - 1);
	}

	void inorder(){
		if(root != nullptr)
			root->inorder();
	}

	
	void postorder() {
		if(root != nullptr)
			root->postorder();
	}
	void inorder2(Node* root){
		if(root){
			inorder2(root->left);
			cout << root->data;
			inorder2(root->right);
		}
	}
	void postorder2(Node* root){
		if(root){
			postorder2(root->left);
			postorder2(root->right);
			cout << root->data;
		}
	}
	Node* getroot() {
		return root;
	}

};

vector<vector<string>> BFS(Node* root) {
	vector<vector<string>> res;
	if(root == nullptr)
		return res;
	
	queue<Node*> q;
	q.push(root);
	while(!q.empty()) {
		int size = q.size();
		vector<string> v(size);
		for(int i = 0; i < size; ++i) {
			Node* temp = q.back(); 
			q.pop();
			if(temp == nullptr)  {
				v.push_back("null");
				continue;
			}
			else {
				v.push_back(temp->data);
			}
			q.push(temp->left);
			q.push(temp->right);
		}
		res.push_back(v);
	}
	cout << "--*******--" << '\n';
	for(auto a : res) {
		for(auto b : a) {
			cout << b << " ";
		}
		cout << '\n';
	}
	return res;

}


int main(){
	string s = "5+4*3-6+7*9";
	EXtree t;
	cout << t.giveOPleft(s) << '\n'; 
	cout << t.giveOPright(s) << '\n';
//	Node* root = t.BuildExtree(s);
	cout << "-------" << '\n';
	t.inorder();
//	t.inorder2(root); 
	cout << '\n';
//	cout << root->data << '\n';
//	cout << root->left->data << '\n';
//	cout << root->right->data << '\n';
//	vector<vector<string>> res;
//	BFS(t.getroot());
	t.postorder();
//	t.postorder2(root); 
	cout << '\n';


}

