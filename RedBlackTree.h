#include <iostream>
#include "string"
using namespace std;

class TreeNode{
public:
  TreeNode();
  TreeNode(int d);
  ~TreeNode();
  bool isRed();
  bool isBlack();
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  char color;
  int data;
  void switchColor();
};

TreeNode::TreeNode(){
  left = nullptr;
  right = nullptr;
  color = 'b';
  parent = nullptr;
}

void TreeNode::switchColor(){
  if(color == 'b'){
    color = 'r';
  }else{
    color = 'b';
  }
}

TreeNode::~TreeNode(){
  // delete left;
  // delete right;
  if(left != nullptr){
  		delete left;
    }
  // if(data != nullptr){
  // 		delete data;
  //   }
  if(right != nullptr){
  		delete right;
  	}
}

TreeNode::TreeNode(int d){
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  data = d;
  color = 'r';
}

bool TreeNode::isRed(){
  return color == 'r';
}

bool TreeNode::isBlack(){
  return color == 'b';
}

class RBT{
public:
  RBT();
  virtual ~RBT();
  void insert(int value);
  bool contains(int value); //AKA search
  // bool deleteNode(int value);
  TreeNode* getSuccessor(TreeNode* d);
  // bool deleteRec();
  bool deleter(int k);
  void rightRotation(TreeNode* child, TreeNode* parent);
  void leftRotation(TreeNode* child, TreeNode* parent);
  void fixInsert(TreeNode *&node);
  void switchColors(TreeNode *node1, TreeNode *node2);
  TreeNode* getMin();
  TreeNode* getMax();
  void printTree();
  void recPrint(TreeNode* node);

private:
  TreeNode* root;
};

RBT::RBT(){
  root = nullptr;
}

RBT::~RBT(){

}

void RBT::insert(int value){
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
  temp->parent = parent;
  cout << temp->data << " temp data" << endl;
  fixInsert(temp);
}

void RBT::fixInsert(TreeNode *&node){
  while(true){
    // if(root == node){
    //   node->color = "black";
    //   break;
    // }
    TreeNode *parent = node->parent;
    if(parent->parent == nullptr){
      break;
    }
    TreeNode *grandpa = parent->parent;
    cout << parent->data << endl;
    cout << grandpa->left->data << " left data" << endl;
    cout << grandpa->right->data << " right daata" << endl;
    // cout << node->data << " beginning" << endl;
    if(grandpa->left != nullptr && grandpa->right != nullptr){
      if(grandpa->left->color == 'r' && grandpa->right->color == 'r'){
        // cout << "poop" << endl;
        grandpa->color = 'r';
        // cout << "poop" << endl;
        grandpa->left->color = 'b';
        // cout << "poop" << endl;
        grandpa->right->color = 'b';
        // cout << "poop" << endl;
      }
    }

    cout << node->data << " beginning" << endl;

    if(parent->color == 'b'){
      break;
    }

    cout << node->data << " end" << endl;

    TreeNode *greatGrandpa;
    bool grandpaIsLeftChild;
    // cout << node->data << endl;
    if(grandpa->left = parent){
      cout << node->data << " you to the light" << endl;
      cout << grandpa->data << " gpa data" << endl;
      // cout << grandpa->left->data << " left data" << endl;
      // cout << grandpa->right->data << " right daata" << endl;
      // cout << "whatup cuh" << endl;
      if(parent->left = node){
        if(grandpa->parent != nullptr){
          greatGrandpa = grandpa->parent;
          if(greatGrandpa->left == grandpa){
            grandpaIsLeftChild = true;
          }else{
            grandpaIsLeftChild = false;
          }
        }else{
          greatGrandpa = nullptr;
        }
        rightRotation(parent, grandpa);
        parent->switchColor();
        grandpa->switchColor();
        if(greatGrandpa != nullptr){
          if(grandpaIsLeftChild){
            greatGrandpa->left = parent;
          }else{
            greatGrandpa->right = parent;
          }
        }
      }else{
        leftRotation(node, parent);
        grandpa->left = node;
      }
    }else{//grandpa rigth equal to parent
      // cout << "whatup cuh" << endl;
      cout << node->data << " i will guide" << endl;
      if(parent->left = node){
        rightRotation(node, parent);
        grandpa->right = node;
      }else{
        // cout << "what up cuh" << endl;
        if(grandpa->parent != nullptr){
          greatGrandpa = grandpa->parent;
          if(greatGrandpa->left == grandpa){
            grandpaIsLeftChild = true;
          }else{
            grandpaIsLeftChild = false;
          }
        }else{
          greatGrandpa = nullptr;
        }
        leftRotation(parent, grandpa);
        parent->switchColor();
        grandpa->switchColor();
        if(greatGrandpa != nullptr){
          if(grandpaIsLeftChild){
            greatGrandpa->left = parent;
          }else{
            greatGrandpa->right = parent;
          }
        }
      }
    }

  }

  root->color = 'b';

}

void RBT::rightRotation(TreeNode* child, TreeNode* parent){
  parent->left = nullptr;
  child->right = parent;
  if(parent->parent != nullptr){
    child->parent = parent->parent;
  }
  parent->parent = child;
}

void RBT::leftRotation(TreeNode* child, TreeNode* parent){
  parent->right = nullptr;
  child->left = parent;
  if(parent->parent != nullptr){
    child->parent = parent->parent;
  }
  parent->parent = child;
}

void RBT::printTree(){
  recPrint(root);
}

void RBT::recPrint(TreeNode* node){
  if(node == nullptr){
    return;
  }
  recPrint(node->left);
  cout << node->data << endl;
  recPrint(node->right);
}

TreeNode* RBT::getMin(){
  TreeNode* current = root;
  TreeNode* parent = current;
  while(current != nullptr){
    parent = current;
    current = current->left;
  }
  // delete current;
  return parent;
}

TreeNode* RBT::getMax(){
  TreeNode* current = root;
  TreeNode* parent = current;
  while(current != nullptr){
    parent = current;
    current = current->right;
  }
  // delete current;
  return parent;
}

bool RBT::contains(int value){
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

bool RBT::deleter(int k){
  TreeNode* current = root;
  TreeNode* parent = current;
  bool isLeft;
  while(true){
    if(current == nullptr){
      return false;
    }
    if(k == current->data){
      break;
    }
    parent = current;
    if(k < current->data){
      current = current->left;
      isLeft = true;
    }else{
      current = current->right;
      isLeft = false;
    }
  }

  if(current->left == nullptr && current->right == nullptr){
    if(current == root){
      root = nullptr;
    }else if(isLeft){
      parent->left = nullptr;
      return true;
    }else{
      parent->right = nullptr;
      return true;
    }
  }else if(current->left == nullptr){
    if(current == root){
      root = current->right;
    }else if(isLeft){
      parent->left = current->right;
      current->right = nullptr;
      return true;
    }else{
      parent->right = current->right;
      current->right = nullptr;
      return true;
    }
  }else if(current->right == nullptr){
    if(current == root){
      root = current->left;
    }else if(isLeft){
      parent->left = current->left;
      current->left = nullptr;
      return true;
    }else{
      parent->right = current->left;
      current->left = nullptr;
      return true;
    }
  }else{
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

TreeNode* RBT::getSuccessor(TreeNode* d){
  TreeNode* sp = d;
  TreeNode* successor = d;
  TreeNode* current = d;
  // current =
  while(successor->left != nullptr){
    sp = successor;
    successor = current;
    current = current->left;
  }
  // //check if successor descendant of right child
  if(successor != d->right){
    sp->left = successor->right;
		successor->right = d->right;
  }
  return successor;

}
