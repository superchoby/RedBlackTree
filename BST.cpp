#include <iostream>

using namespace std;
class TreeNode{
	public:
		TreeNode();
		TreeNode(int key);
		virtual ~TreeNode();// some hw for you guys

		int key;
		TreeNode *left;
		TreeNode *right;

};

////implement it////
TreeNode::TreeNode(){
	left = nullptr;
	right = nullptr;
}

TreeNode::TreeNode(int k){
	left = nullptr;
	right = nullptr;
	key = k;
}

TreeNode::~TreeNode(){
	//let's do a little research (that means you guys)
	delete left;
	delete right;
}

///////let's define our Tree Class///////
class BST{
	public:
		BST();
		// virtual ~BST();
		void insert(int value);
		bool contains(int value); //AKA search
		bool deleteNode(int value);
		TreeNode* getSuccessor(TreeNode* d);
		bool deleteRec();
		bool deleter(int k);
		TreeNode* getMin();
		TreeNode* getMax();
		void printTree();
		bool isEmpty();
		void recPrint(TreeNode* node);

	private:
		TreeNode* root;
};

//implement this bad boy
BST::BST(){//default constructor
	root = nullptr;
}

// BST()::~BST(){
// 	//iterate and delete
// 	//lets put on our research hats!!!!
// }

void BST::printTree(){//print entire tree
	recPrint(root);
}

void BST::recPrint(TreeNode* node){
	if(node == nullptr){
		return;
	}
	recPrint(node->left);
	cout << node->key << endl;
	recPrint(node->right);
}

bool BST::isEmpty(){
	return (root == nullptr);
}

void BST::insert(int value){
	//check if this value exist, if not continue
	TreeNode* node = new TreeNode(value);

	if(isEmpty()){//empty tree
		root = node;
	}else{//not an empty tree, lets continue to add
		TreeNode* current = root;
		TreeNode* parent;//empty Node

		while(true){//lets look for our insertion point
			parent = current;
			if(value < current->key){//go left
				current = current->left;
				if(current == nullptr){//we found our location
					parent->left = node;
					break;
				}
			}else{//go right
				current = current->right;
				if(current == nullptr){
					parent->right = node;
					break;
				}
			}
		}
	}
}

bool BST::contains(int value){
	if(isEmpty()){//empty tree, nothing exists
		return false;
	}else{ //not an empty tree
		TreeNode* current = root;
		while(current->key != value){
			if(value < current->key){
				current = current->left;
			}else{
				current = current->right;
			}
			if(current == nullptr){ //item not in tree
				return false;
			}
		}
		return true;
	}
}

bool BST::deleter(int k){
	if(isEmpty()){
		return false;
	}
	//check if key/value exist in the Tree
	TreeNode* current = root;
	TreeNode* parent = root;
	bool isLeft = true;

	//now, let's iterate and update our pointers
	while(current->key != k){
		parent = current;
		if(k < current->key){
				isLeft = true;
				current = current->left;
		}else{
			isLeft = false;
			current = current->right;
		}

		if(current == nullptr){
			return false;
		}
	}
	//at this point we found our node to be deleteNode
	if(current->left == nullptr && current->right == nullptr){//leaf node, no children
		if(current == root){
			root = nullptr;
		}else if(isLeft){
			parent->left = nullptr;
		}else{
			parent->right = nullptr;
		}
	}else if(current->right == nullptr){//no right child
		if(current == root){
			root = current->left;
		}else if(isLeft){
			parent->left = current->left;
		}else{
			parent->right = current->left;
		}
	}else if(current->left == nullptr){//no left child
		if(current == root){
			root = current->right;
		}else if(isLeft){
			parent->left = current->right;
		}else{
			parent->right = current->right;
		}
	}
	//we need to check if node to be deleted has one child
	// else if(current->right == nullptr){//no right child
	// 	if(current == root){
	// 		root = current->left;
	// 	}else if(isLeft){
	// 		parent->left = current->left;
	// 	}else{
	// 		parent->right = current->left;
	// 	}
	// }
	else{//the node to be deleted has 2 children
		//find successor of the node to be deleted (current)
		// cout << "whatup" << endl;
		TreeNode* successor = getSuccessor(current);
		if(current == root){
			root = successor;
		}else if(isLeft){
			parent->left = successor;
		}else{
			parent->right = successor;
		}
		successor->left = current->left;
	}

	return true;
}

TreeNode* BST::getSuccessor(TreeNode *d){//d is the node to be deleted
	TreeNode* sp = d; //successor's parent
	TreeNode* successor = d;
	TreeNode* current = d->right;

	while(current != nullptr){
		sp = successor;
		successor = current;
		current = current->left;
	}
	//we need to check if successor is a descendant of right child
	if(successor != d->right){
		sp->left = successor->right;
		successor->right = d->right;
	}
	return successor;
}

TreeNode* BST::getMin(){
	TreeNode* current = root;
	TreeNode* parent;
	while(current->left != nullptr){
		current = current->left;
	}
	return current;
}

TreeNode* BST::getMax(){
	TreeNode* current = root;
	while(current->right != nullptr){
		current = current->right;
	}
	return current;
}
