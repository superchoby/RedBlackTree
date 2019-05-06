#include <iostream>
#include "string"
#include <bits/stdc++.h>
#include <queue>

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
  bool pointsToDoubleBlack;
  bool isNULL;
  char color;
  int data;
  void switchColor();
};

TreeNode::TreeNode(){
  left = nullptr;
  right = nullptr;
  color = 'b';
  parent = nullptr;
  pointsToDoubleBlack = false;
  isNULL = true;
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
  pointsToDoubleBlack = false;
  isNULL = false;
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
  void swapValue(TreeNode *node1, TreeNode *node2);
  void redBlackTreeDelete(int k);
  void recPrint(TreeNode* node);
  void traverse(TreeNode* root);
  void levelOrder(TreeNode* root);
  void levelOrderPrint();

private:
  TreeNode* root;
};

RBT::RBT(){
  root = nullptr;
}

RBT::~RBT(){

}

void RBT::levelOrderPrint(){
  levelOrder(root);
}

void RBT::swapValue(TreeNode *node1, TreeNode *node2){
  int tempValue1 = node1->data;
  node1->data = node2->data;
  node2->data = tempValue1;
}
// A Binary Tree Node
// Function to do level order
// traversal line by line
void RBT::levelOrder(TreeNode* root)
{
    if (root == NULL) return;
    queue<TreeNode*> q;
    TreeNode* curr;
    q.push(root);
    q.push(NULL);
    while (q.size() > 1)
    {
        curr = q.front();
        q.pop();
        if (curr == NULL)
        {
           q.push(NULL);
           cout << "\n";
        }

        else {
            if(curr->left)
            q.push(curr->left);
            if(curr->right)
            q.push(curr->right);
            // cout << curr->color << " ";
            cout << curr->data << " ";
        }
    }
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

  fixInsert(temp);
}

void RBT::fixInsert(TreeNode *&node){
  while(root != node){

    TreeNode *parent = node->parent;
    if(parent->parent == nullptr){
      break;
    }
    TreeNode *grandpa = parent->parent;

    if(grandpa->left != nullptr && grandpa->right != nullptr){
      if(grandpa->left->color == 'r' && grandpa->right->color == 'r'){
        grandpa->color = 'r';
        grandpa->left->color = 'b';
        grandpa->right->color = 'b';
        node = grandpa;
        continue;
      }
    }
    if(parent->color == 'b'){
      break;
    }else if(node->color == 'b' && parent->color == 'r' && grandpa->color == 'b'){
      break;
    }
    TreeNode *greatGrandpa;
    bool grandpaIsLeftChild;

    if(grandpa->left == parent){
      if(parent->left == node){
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
      node = parent;

    }else{//grandpa rigth equal to parent
      if(parent->left == node){
        rightRotation(node, parent);
        grandpa->right = node;
      }else{//parent right == node
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
      node = parent;
    }
  }
  root->color = 'b';
}

void RBT::rightRotation(TreeNode* child, TreeNode* parent){
  if(child->right != nullptr){
    parent->left = child->right;
    child->right->parent = parent;
  }else{
    parent->left = nullptr;
  }
  child->right = parent;
  if(parent->parent != nullptr){
    if(parent->parent->left == parent){
      parent->parent->left = child;
    }else{
      parent->parent->right = child;
    }
    child->parent = parent->parent;
  }else{
    child->parent = nullptr;
    root = child;
  }
  parent->parent = child;
}

void RBT::leftRotation(TreeNode* child, TreeNode* parent){
  if(child->left != nullptr){
    parent->right = child->left;
    child->left->parent = parent;
  }else{
    parent->right = nullptr;
  }

  child->left = parent;
  if(parent->parent != nullptr){
    if(parent->parent->left == parent){
      parent->parent->left = child;
    }else{
      parent->parent->right = child;
    }
    child->parent = parent->parent;
  }else{
    child->parent = nullptr;
    root = child;
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

void RBT::redBlackTreeDelete(int k){
  TreeNode* current = root;
  TreeNode* parent = current;
  bool isLeft;
  while(true){
    if(current == nullptr){
      return;
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
  TreeNode* sibling;
  TreeNode* leftNephew;
  TreeNode* rightNewphew;
  TreeNode* leftChild;
  TreeNode* rightChild;

  if(isLeft){
    sibling = parent->right;
  }else{
    sibling = parent->left;
  }

  if(sibling->right != nullptr){
    rightNephew = sibling->right;
  }else{
    rightNephew = new Node();
  }

  if(sibling->left != nullptr){
    leftNephew = sibling->left;
  }else{
    leftNephew = new Node();
  }

  if(current->left != nullptr){
    leftChild = current->left;
  }else{
    leftChild = new Node();
  }

  if(current->right != nullptr){
    rightChild = current->right;
  }else{
    rightChild = new Node();
  }

  if(isLeft){
    parent->left = nullptr;
    if(current->isRed()){
      return;
    }else{//is black
      if(current->left->color == 'r'){
        TreeNode* successor = getSuccessor(current);
        swapValue(current, successor);
        if(successor == successor->parent->left){
          successor->parent->left = nullptr;
        }else{
          successor->parent->right = nullptr;
        }
      }











      parent->pointsToDoubleBlack = true;
      while(parent->pointsToDoubleBlack){
        if(rightNephew->isRed()){
          leftRotation(sibling, parent);
          rightNephew->switchColor();
          parent->pointsToDoubleBlack = false;
        }else if(leftNephew->isRed()){
          rightRotation
        }
      }



    }
  }else{
    if(current->isRed()){
      parent->right = nullptr;
    }
  }

}


// void RBT::redBlackTreeDelete(int k){
//   TreeNode* current = root;
//   TreeNode* parent = current;
//   bool isLeft;
//   while(true){
//     if(current == nullptr){
//       return;
//     }
//     if(k == current->data){
//       break;
//     }
//     parent = current;
//     if(k < current->data){
//       current = current->left;
//       isLeft = true;
//     }else{
//       current = current->right;
//       isLeft = false;
//     }
//   }
//
//
//   if(current->left == nullptr && current->right == nullptr && current->color == 'r'){
//     root = nullptr;
//     return;
//   }
//
//
//   if(current->left == nullptr && current->right == nullptr && current->color == 'r'){
//     if(parent->left == current){
//       parent->left = nullptr;
//     }if(parent->right == current){
//       parent->right = nullptr;
//     }
//   }
//
//   if(current->left == nullptr && current->right == nullptr && current->color == 'b' && current != root){
//     if(parent->left == current){
//       parent->left = nullptr;
//       if(parent->right != nullptr){
//         if(parent->right->right == nullptr && parent->right->left==nullptr){
//           parent->right->switchColor();
//         }else if(parent->right->right != nullptr){//right nephew is red
//           parent->parent->switchColor();
//           parent->parent->right->switchColor();
//           leftRotation(parent->right, parent);
//         }else{//right newphew does not exist and left does
//           parent->right->left->switchColor();
//           parent->right->switchColor();
//           rightRotation(parent->right->left, parent->right);
//         }
//       }//parent->left cant be nullptr cuz it current
//     }if(parent->right == current){
//       parent->right = nullptr;
//       if(parent->left != nullptr){
//         if(parent->left->left == nullptr && parent->left->right==nullptr){
//           parent->left->switchColor();
//         }else if(parent->left->left != nullptr){//right nephew is red
//           parent->parent->switchColor();
//           parent->parent->left->switchColor();
//           leftRotation(parent->left, parent);
//         }else{//right newphew does not exist and left does
//           parent->left->right->switchColor();
//           parent->left->switchColor();
//           rightRotation(parent->left->right, parent->left);
//         }
//       }
//     }
//   }
//   root->color = 'b';
// }


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
      if(parent->color == 'r' && parent->right != nullptr){
        parent->switchColor();
        parent->right->switchColor();
      }
      return true;
    }else{
      parent->right = nullptr;
      if(parent->color == 'r' && parent->left != nullptr){
        parent->switchColor();
        parent->left->switchColor();
      }
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
