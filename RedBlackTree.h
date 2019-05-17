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
  bool isDoubleBlack;
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
  isDoubleBlack = false;
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
  isDoubleBlack = false;
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
  void swapValue(TreeNode *node1, TreeNode *node2);
  void redBlackTreeDelete(int k);
  void recPrint(TreeNode* node);
  void traverse(TreeNode* root);
  void levelOrder(TreeNode* root);
  void levelOrderPrint();
  void fixDoubleBlack(TreeNode* node, bool isLeft);

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
            cout << curr->data << " ";
            cout << curr->color << " ";
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
  TreeNode* nodeToDelete = nullptr;
  bool isLeft;//checks if node is a left or right child
  while(true){
    if(current == nullptr){
      return true;
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
  bool leftIsDoubleBlack;
  if(current->left != nullptr){//check if there is a left value so we know there is a successor
    nodeToDelete = getSuccessor(current);
    bool doubleBlackExists = false;
    TreeNode* successorParent = nodeToDelete->parent;
    swapValue(current, nodeToDelete);
    if(nodeToDelete->color == 'r'){
      if(successorParent->left == nodeToDelete->parent){
        successorParent->left = nullptr;
      }else{
        successorParent->right = nullptr;
      }
      nodeToDelete->parent == nullptr;
    }else{
      if(nodeToDelete->left == nullptr){
        if(successorParent == current){
          current->left = nullptr;
          leftIsDoubleBlack == true;
          fixDoubleBlack(current, leftIsDoubleBlack);
        }else{

          successorParent->right = nullptr;
          leftIsDoubleBlack = false;
        }
      }
      // if(successorParent->left == nodeToDelete->parent){
      //   successorParent->left = nullptr;
      //   leftIsDoubleBlack = true;
      // }else{
      //   successorParent->right = nullptr;
      //   leftIsDoubleBlack = false;
      // }
      nodeToDelete->parent == nullptr;
      fixDoubleBlack(successorParent, leftIsDoubleBlack);
    }
  }else{
    nodeToDelete = current;
    if(nodeToDelete->color == 'r'){
      if(parent->left == nodeToDelete->parent){
        parent->left = nullptr;
      }else{
        parent->right = nullptr;
      }
      nodeToDelete->parent == nullptr;
      return true;
    }else{
      bool deletedNodeHadChildren = false;
      if(isLeft){
        if(nodeToDelete->right != nullptr){
          parent->left = nodeToDelete->right;
          nodeToDelete->right->parent = parent;
          deletedNodeHadChildren = true;
        }else{
          parent->left = nullptr;
        }
      }else{
        if(nodeToDelete->right != nullptr){
          parent->right = nodeToDelete->right;
          nodeToDelete->right->parent = parent;
          deletedNodeHadChildren = true;
        }else{
          parent->right = nullptr;
        }
      }
      leftIsDoubleBlack = isLeft;
      TreeNode* deletersParent = nodeToDelete->parent;// for nodes by itself when it deleted its parent has the double black node
      nodeToDelete->parent = nullptr;
      if(deletedNodeHadChildren){
        // cout << "chill" << endl;
        // levelOrderPrint();
        // cout << "whatup" << endl;
        fixDoubleBlack(nodeToDelete->right, leftIsDoubleBlack);
      }else{
        fixDoubleBlack(deletersParent, leftIsDoubleBlack);
      }
    }
  }


}

TreeNode* RBT::getSuccessor(TreeNode* d){
  TreeNode* successor = d->left;
  while(successor->right != nullptr){
    successor = successor->right;
  }
  return successor;
}

void RBT::fixDoubleBlack(TreeNode* node, bool isLeft){
  if(isLeft){
    cout << "aaaaaa" << endl;
    if(node->right != nullptr){

      if(node->right->color == 'r'){
        leftRotation(node, node->right);
        node->switchColor();
        node->right->switchColor();
        fixDoubleBlack(node, isLeft);
      }else if(node->color == 'r' && node->right->color == 'b' && node->right->right == nullptr && node->right->left == nullptr){
        node->switchColor();
        node->right->switchColor();
      }else{
        bool rightNephewIsRed;
        bool leftNephewIsRed;

        if(node->right->right != nullptr){
          if(node->right->right->color == 'r'){
            rightNephewIsRed = true;
          }else{
            rightNephewIsRed = false;
          }
        }else{
          rightNephewIsRed = false;
        }

        if(node->right->left != nullptr){
          if(node->right->left->color == 'r'){
            leftNephewIsRed = true;
          }else{
            leftNephewIsRed = false;
          }
        }else{
          leftNephewIsRed = false;
        }

        if(rightNephewIsRed){
          leftRotation(node, node->right);
          node->switchColor();
          node->right->switchColor();
          if(node->right->right != nullptr){
            node->right->right->switchColor();
          }
        }else if(leftNephewIsRed){
          rightRotation(node->right, node->right->left);
          node->right->switchColor();
          node->left->switchColor();
          fixDoubleBlack(node, isLeft);
        }else{//left and right nephew are black
          if(node->color == 'r'){
            node->color == 'b';
            return;
          }else{// node is black so we will double black it
            node->right->color = 'r';
            if(node == root){
              return;
            }else if(node->parent->parent == nullptr){
              fixDoubleBlack(node->parent, true);
            }else if(node->parent->parent != nullptr){
              if(node->parent->parent->right == node->parent){
                isLeft = false;
              }else if(node->parent->parent->left == node->parent){
                isLeft = true;
              }
              fixDoubleBlack(node->parent, isLeft);
            }
          }
        }
      }
    }else{// does equal nullptr
      node->color = 'b';
    }

  }else{

    if(node->left != nullptr/* && node->left->left == nullptr && node->left->right == nullptr*/){

      if(node->left->color == 'r'){

        leftRotation(node, node->left);
        node->switchColor();
        node->left->switchColor();
        fixDoubleBlack(node, isLeft);
      }
      else if(node->color == 'r' && node->left->color == 'b' && node->left->right == nullptr && node->left->left == nullptr){
        node->switchColor();
        node->left->switchColor();
      }
      else{


        bool rightNephewIsRed;
        bool leftNephewIsRed;

        if(node->left->left != nullptr){
          if(node->left->left->color == 'r'){
            leftNephewIsRed = true;
          }else{
            leftNephewIsRed = false;
          }
        }else{
          leftNephewIsRed = false;
        }
        if(node->left->right != nullptr){
          if(node->left->right->color == 'r'){
            rightNephewIsRed = true;
          }else{
            rightNephewIsRed = false;
          }
        }else{
          rightNephewIsRed = false;
        }


        if(leftNephewIsRed){
          // cout << "asd" << endl;
          // levelOrderPrint();
          // cout << endl;
          // cout << node->data << " data" << endl;
          // // cout << rightNephewIsRed << " right red" << endl;
          // // cout << leftNephewIsRed << " left red" << endl;
          // cout << "asd" << endl;

          rightRotation(node->left, node);
          if(node->color == 'r'){
            node->switchColor();
            node->parent->left->switchColor();
            node->parent->switchColor();
          }else{
            node->parent->left->switchColor();
          }
          root->color = 'b';
          return;
        }else if(rightNephewIsRed){
          leftRotation(node->left->right, node->left);
          node->left->switchColor();
          if(node->left->left != nullptr){
            node->left->left->switchColor();
          }
          fixDoubleBlack(node, isLeft);
        }else{//left and right nephew are black
          if(node->color == 'r'){
            node->color == 'b';
            return;
          }else{// node is black so we will double black it
            node->left->color = 'r';
            if(node == root){
              return;
            }else if(node->parent->parent == nullptr){
              fixDoubleBlack(node->parent, true);
            }else if(node->parent->parent != nullptr){
              if(node->parent->parent->left == node->parent){
                isLeft = false;
              }else if(node->parent->parent->right == node->parent){
                isLeft = true;
              }
              fixDoubleBlack(node->parent, isLeft);
            }
          }
        }
      }
    }else{// does equal nullptr
      node->color = 'b';
    }



  }
}
