//Xin Song -- expression tree
#include<iostream>
#include<string>
#include<cstring>
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
		root = new Node();
	}
	Node* splitByMultiDivision(string s, Node* root) {
		auto i = s.find_last_of("*/");
		if(i == string::npos) 
			return new Node(s);
		string L = s.substr(0, i);
		string op = string(1, s[i]);
		string R = s.substr(i + 1);
//		cout << L << "    " << op << "   " << R << " ";
//		cout << '\n';
		root->right = new Node(R);
		root->data = op;
		if(L.find_first_of("*/") == string::npos) {
			root->left = new Node(L);
		}
		else 
			root->left = splitByMultiDivision(L, new Node());
		
		return root;
	}

	Node* BuildExtree(string s, Node* root){ 
		auto i = s.find_last_of("+-");
		if(i == string::npos) {
			if(s.find_first_of("*/") == string::npos)
				return new Node(s);
			else {
				root = splitByMultiDivision(s, new Node());
				return root;
			}
		}
		string L = s.substr(0, i);
		string op = string(1, s[i]);
		string R = s.substr(i + 1);
//		cout << L << "    " << op << "   " << R << " ";
//		cout << '\n';
		if(R.find_first_of("*/") == string::npos) {
			root->right = new Node(R);
		}
		else { 
			root->right = splitByMultiDivision(R, new Node());
		}
		root->data = op;
		if(L.find_last_of("+-*/") == string::npos) {
			root->left = new Node(L);
		}
		else {
			//contain */ no +-
			if(L.find_first_of("*/") != string::npos && L.find_first_of("-+") == string::npos) {
				root->left = splitByMultiDivision(L, new Node());
			}
			else 
				root->left = BuildExtree(L, new Node());
		}
		return root;
	}

	void inorder(){
		if(root != nullptr)
			root->inorder();
	}	
	void postorder() {
		if(root != nullptr)
			root->postorder();
	}
	//normal preorder
	void preorder(Node* root){
		if(root){
			cout << root->data;
			preorder(root->left);
			preorder(root->right);
		}
	}
	//normal inorder
	void inorder2(Node* root){
		if(root){
			inorder2(root->left);
			cout << root->data;
			inorder2(root->right);
		}
	}
	//normal postorder
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
	
	bool IsNumber(string s) {
		for(int i = 0; i < s.size(); ++i) {
			int temp = (int)s[i];
			if(temp >= 48 && temp <= 57)
				continue;
			else
				return false;
		}
		return true;
	}

	//calculate
	double calculate(Node* root) {
		if(root == nullptr) 
			return 0;

		if(IsNumber(root->data))
			return stoi(root->data);

		if(root->left && root->right) {
			if(root->data ==  "+")
				return calculate(root->left) + calculate(root->right);
			else if(root->data == "-")
				return calculate(root->left) - calculate(root->right);
			else if(root->data == "/")
				return calculate(root->left) / calculate(root->right);
			else 
				return calculate(root->left) * calculate(root->right);
		}
		return 0;
	}
};

//BFS 
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
			Node* temp = q.front(); q.pop();
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
	for(auto a : res) {
		for(auto b : a) {
			cout << b << " ";
		}
		cout << '\n';
	}
	cout << '\n';
	return res;

}


int main(){
	string s = "5+4*3-6+7*9";
//	string s = "(3*(5-4))+((-6)/2)";
	string s1 = "5-5/5";
	
	EXtree t;
	EXtree t1;

	Node* root = t.BuildExtree(s, t.getroot());
	Node* root1 = t.BuildExtree(s1, t1.getroot());

	cout << "-------" << '\n';
	t.inorder2(root); 
	cout << '\n';
	t.postorder2(root); 
	cout << '\n';
	cout << t.calculate(root) << '\n';	

	cout << "-------" << '\n';
	t1.inorder2(root1); 
	cout << '\n';
	t1.postorder2(root1); 
	cout << '\n';
	cout << t1.calculate(root1) << '\n';	
//	vector<vector<string>> res = BFS(t.getroot());

}

