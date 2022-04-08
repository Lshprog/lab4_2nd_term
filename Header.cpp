#include "Header.h";
#include <iostream>
#include <string>
#include <map>

treecalc::BinaryTree::Node::Node() {
	this->left = nullptr;
	this->right = nullptr;
	this->next = nullptr;
}
treecalc::BinaryTree::Node::Node(char value) {
	this->value = value;
	this->left = nullptr;
	this->right = nullptr;
	this->next = nullptr;
}

treecalc::BinaryTree::Node::~Node()
{
	delete left,right,next;
}

void treecalc::BinaryTree::Stack::push(Node* n)
{
	if (head == nullptr)
		head = n;
	else {
		n->next = head;
		head = n;
	}
}

treecalc::BinaryTree::Node* treecalc::BinaryTree::Stack::pop()
{
	Node* temp = head;
	if (head->next == nullptr)
		head = nullptr;
	else
		head = head->next;
	return temp;
}

void treecalc::BinaryTree::build_expression_tree(int size,char* s)
{
	char k;
	Stack numbers;
	Node* x = new Node();
	Node* y = new Node();
	Node* z = new Node();

	for (int i = 0; i < size; i++) {
		if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*') {
			z = new Node(s[i]);
			x = numbers.pop();
			y = numbers.pop();
			z->left = y;
			z->right = x;
			numbers.push(z);
		}
		else {
			x = new Node(s[i]);
			numbers.push(x);
		}
	}
	inorder(z);
	std::cout << '\n';
	std::cout << "Dif for what variable? ";
	std::cin >> k;
	derivative(z,k);
	delete x, y, z;
}


void treecalc::BinaryTree::create_rpn(int size,char* s) {
	Stack rpn;
	int temp_count=0;
	Node* temp_useless= new Node();
	Node* x = new Node();
	Node* y = new Node();
	Node* z = new Node();
	std::map<char, int> mp{
		{'+',1},
		{'-',1},
		{'*',2},
		{'/',2},
		{'(',3},
		{')',3}
	};

	char new_string[100] = { 0 };
	for (int i = 0; i < size; i++) {
		if (s[i]== '+' || s[i] == '-' || s[i] == '/' || s[i] == '*' || s[i] == ')' || s[i] == '('){
			if (rpn.head == nullptr) {
				z = new Node(s[i]);
				rpn.push(z);
			}
			
			else if (s[i] == ')') {
				while (rpn.head->value != '(') {
					if (rpn.head->next == nullptr) {
						std::cout << "Erorr";
						return;
					}
					new_string[temp_count]=rpn.head->value;
					temp_count++;
					temp_useless = rpn.pop();
				}
				temp_useless = rpn.pop();
			}
			else if (s[i] == '(' || mp[rpn.head->value] < mp[s[i]]) {
				z = new Node(s[i]);
				rpn.push(z);
			}
			
			else if (mp[rpn.head->value] >= mp[s[i]]){
				z = new Node(s[i]);
				while ((mp[rpn.head->value] >= mp[s[i]])&&(rpn.head->value!='(')) {
					new_string[temp_count] = rpn.head->value;
					temp_count++;
					temp_useless = rpn.pop();
					if (rpn.head == nullptr)
						break;
				}
				rpn.push(z);
			}
		}
		else {
			new_string[temp_count] = s[i];
			temp_count++;
		}
	}
	while (true) {
		if (rpn.head == nullptr)
			break;
		new_string[temp_count] = rpn.head->value;
		temp_count++;
		temp_useless = rpn.pop();
	}
			
	for (int j = 0; j < temp_count; j++) {
		std::cout << new_string[j];
	}
	std::cout << '\n';
	build_expression_tree(temp_count , new_string);
	delete x, y, z,temp_useless;
	
}

void treecalc::BinaryTree::inorder(Node* z)
{
	if (z == nullptr) {
		return;
	}
	if (z->value == '*' || z->value == '/')
		std::cout << "(";
	inorder(z->left);
	if (z->value == '*' || z->value == '/')
		std::cout << ")";
	std::cout << z->value;
	if (z->value == '*' || z->value == '/')
		std::cout << "(";
	inorder(z->right);
	if (z->value == '*' || z->value == '/')
		std::cout << ")";
	
}

void treecalc::BinaryTree::derivative(Node* z,char k)
{
	if (z->value == '*') {
		std::cout << '(';
		derivative(z->left,k);
		std::cout << ')';
		std::cout << '*';
		std::cout << '(';
		inorder(z->right);
		std::cout << ')';
		std::cout << '+';
		std::cout << '(';
		derivative(z->right,k);
		std::cout << ')';
		std::cout << '*';
		std::cout << '(';
		inorder(z->left);
		std::cout << ')';
	}
	else if (z->value == '/') {
		std::cout << '(';
		std::cout << '(';
		derivative(z->left,k);
		std::cout << ')';
		std::cout << '*';
		std::cout << '(';
		inorder(z->right);
		std::cout << ')';
		std::cout << '-';
		std::cout << '(';
		derivative(z->right,k);
		std::cout << ')';
		std::cout << '*';
		std::cout << '(';
		inorder(z->left);
		std::cout << ')';
		std::cout << ")/(";
		inorder(z->right);
		std::cout << ")^2";
	}
	else if (z->value == '+'|| z->value == '-') {
		derivative(z->left,k);
		std::cout << z->value;
		derivative(z->right,k);

	}
	else if (z->value == k) {
		std::cout << 'd'<<k;
	}
	else if (z->value>47 && z->value<59){
		std::cout << '0';
	}
	else {
		std::cout << '1';
	}
	
}

void startprog() {
	char string_to_read[100] = {0};
	std::cout << "Enter your expression:\n";
	std::cin >> string_to_read;

	int string_size = strlen(string_to_read);
	treecalc::BinaryTree tree = treecalc::BinaryTree();
	tree.create_rpn(string_size,string_to_read);

}