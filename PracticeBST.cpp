#include <iostream>

using namespace std;

class TreeNode{
public:
  TreeNode();
  TreeNode(int d);
  ~TreeNode();
  TreeNode* left;
  TreeNode* right;
  int data;
};

TreeNode::TreeNode(){
  left = nullptr;
  right = nullptr;
}

TreeNode::~TreeNode(){
  delete left;
  delete right;
}

TreeNode::TreeNode(int d){
  left = nullptr;
  right = nullptr;
  data = d;
}

class BST{
public:
  BST();
  virtual ~BST();
  void insert(int value);
  bool contains(int value); //AKA search
  // bool deleteNode(int value);
  TreeNode* getSuccessor(TreeNode* d);
  // bool deleteRec();
  bool deleter(int k);
  TreeNode* getMin();
  TreeNode* getMax();
  void printTree();
  void recPrint(TreeNode* node);

private:
  TreeNode* root;
};

BST::BST(){
  root = nullptr;
}

BST::~BST(){

}

void BST::insert(int value){
  if(root == nullptr){
    TreeNode* temp = new TreeNode(value);
    root = temp;
    return;
  }
  bool isLeft;
  TreeNode* current = root;
  TreeNode* parent = current;
  while(current != nullptr){
    parent = current;
    if(value < current->data){
      current = current->left;
      isLeft = true;
    }else{
      current = current->right;
      isLeft = false;
    }
  }
  TreeNode* temp = new TreeNode(value);
  if(isLeft){
    parent->left = temp;
  }else{
    parent->right = temp;
  }
}

void BST::printTree(){
  recPrint(root);
}

void BST::recPrint(TreeNode* node){
  if(node == nullptr){
    return;
  }
  recPrint(node->left);
  cout << node->data << endl;
  recPrint(node->right);
}

TreeNode* BST::getMin(){
  TreeNode* current = root;
  TreeNode* parent = current;
  while(current != nullptr){
    parent = current;
    current = current->left;
  }
  // delete current;
  return parent;
}

TreeNode* BST::getMax(){
  TreeNode* current = root;
  TreeNode* parent = current;
  while(current != nullptr){
    parent = current;
    current = current->right;
  }
  // delete current;
  return parent;
}

bool BST::contains(int value){
  TreeNode* current = root;
  while(true){
    if(current == nullptr){
      return false;
    }else if(current->data == value){
      return true;
    }

    if(value < current->data){
      current = current->left;
    }else{
      current = current->right;
    }
  }
}

bool BST::deleter(int k){
  TreeNode* current = root;
  TreeNode* parent = current;
  bool isLeft;
  while(true){
    parent = current;
    if(current == nullptr){
      return false;
    }
    if(k == current->data){
      break;
    }else if(k < current->data){
      current = current->left;
      isLeft = true;
    }else{
      current = current->right;
      isLeft = false;
    }
  }

  if(current->left == nullptr && current->right == nullptr){
    if(isLeft){
      parent->left = nullptr;
      return true;
    }else{
      parent->right = nullptr;
      return true;
    }
  }else if(current->left == nullptr){
    if(isLeft){
      current->right = nullptr;
      parent->left = nullptr;
      return true;
    }else{
      current->right = nullptr;
      parent->right = nullptr;
      return true;
    }
  }else if(current->right = nullptr){
    if(isLeft){
      current->left = nullptr;
      parent->left = nullptr;
      return true;
    }else{
      current->left = nullptr;
      parent->right = nullptr;
      return true;
    }
  }else{
    TreeNode* successor = getSuccessor(current);
    parent->left = successor;
    successor = current->left;
  }

}

TreeNode* BST::getSuccessor(TreeNode* d){
  sp = successor;
  successor = d->right;
  while(successor->left != nullptr){
    successor = successor->left;
  }

  return successor;
}
