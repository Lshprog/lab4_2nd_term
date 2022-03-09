#pragma once
namespace treecalc {
	struct BinaryTree {
		struct Node {
			char value;
			Node* left;
			Node* right;
			Node* next;
			Node();
			Node(char value);
		};
		struct Stack {
			Node* head = nullptr;
			void push(Node*);
			Node* pop();
		};
	
		void build_expression_tree(int ,char* );
		void create_rpn(int , char* );
		void inorder(Node* z);

	};
}
void startprog();