#include <iostream>
#include "string"
#include <bits/stdc++.h>
#include <queue>

using namespace std;

template <class T>
class TreeNode{
public:
  TreeNode();
  TreeNode(T d);
  ~TreeNode();
  bool isRed();
  bool isBlack();
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  bool isDoubleBlack;
  bool isNULL;
  char color;
  T data;
  void switchColor();
};

template <class T>
TreeNode<T>::TreeNode(){
  left = nullptr;
  right = nullptr;
  color = 'b';
  parent = nullptr;
  isDoubleBlack = false;
  isNULL = true;
}

template <class T>
void TreeNode<T>::switchColor(){
  if(color == 'b'){
    color = 'r';
  }else{
    color = 'b';
  }
}

template <class T>
TreeNode<T>::~TreeNode(){
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

template <class T>
TreeNode<T>::TreeNode(T d){
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  data = d;
  color = 'r';
  isDoubleBlack = false;
  isNULL = false;
}

template <class T>
bool TreeNode<T>::isRed(){
  return color == 'r';
}

template <class T>
bool TreeNode<T>::isBlack(){
  return color == 'b';
}

template <class T>
class RBT{
public:
  RBT();
  virtual ~RBT();
  void insert(T value);
  bool contains(T value); //AKA search
  // bool deleteNode(int value);
  TreeNode<T>* getSuccessor(TreeNode<T>* d);
  // bool deleteRec();
  bool deleter(T k);
  void rightRotation(TreeNode<T>* child, TreeNode<T>* parent);
  void leftRotation(TreeNode<T>* child, TreeNode<T>* parent);
  void fixInsert(TreeNode<T>* node);
  TreeNode<T>* getMin();
  TreeNode<T>* getMax();
  void swapValue(TreeNode<T>* node1, TreeNode<T>* node2);
  void redBlackTreeDelete(T k);
  void recPrint(TreeNode<T>* node);
  void traverse(TreeNode<T>* root);
  void levelOrder(TreeNode<T>* root);
  void levelOrderPrint();
  void fixDoubleBlack(TreeNode<T>* node, bool isLeft);

private:
  TreeNode<T>* root;
};

template <class T>
RBT<T>::RBT(){
  root = nullptr;
}

template <class T>
RBT<T>::~RBT(){

}

template <class T>
void RBT<T>::levelOrderPrint(){
  levelOrder(root);
}

template <class T>
void RBT<T>::swapValue(TreeNode<T>* node1, TreeNode<T>* node2){
  T tempValue1 = node1->data;
  node1->data = node2->data;
  node2->data = tempValue1;
}
// A Binary Tree Node
// Function to do level order
// traversal line by line
template <class T>
void RBT<T>::levelOrder(TreeNode<T>* root)
{
    if (root == NULL) return;
    queue<TreeNode<T>*> q;
    TreeNode<T>* curr;
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
    cout << endl;
}

template <class T>
void RBT<T>::insert(T value){

  if(root == nullptr){
    TreeNode<T>* temp = new TreeNode<T>(value);
    root = temp;
    return;
  }
  bool isLeft;
  TreeNode<T>* current = root;
  TreeNode<T>* parent = current;
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
  TreeNode<T>* temp = new TreeNode<T>(value);
  if(isLeft){
    parent->left = temp;
  }else{
    parent->right = temp;
  }
  temp->parent = parent;

  fixInsert(temp);
}

template <class T>
void RBT<T>::fixInsert(TreeNode<T>* node){
  while(root != node){

    TreeNode<T>* parent = node->parent;
    if(parent->parent == nullptr){
      break;
    }
    TreeNode<T> *grandpa = parent->parent;

    if(grandpa->left != nullptr && grandpa->right != nullptr){
      if(grandpa->left->color == 'r' && grandpa->right->color == 'r' && node->color == 'r'){
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
    TreeNode<T> *greatGrandpa;
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

template <class T>
void RBT<T>::rightRotation(TreeNode<T>* child, TreeNode<T>* parent){
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

template <class T>
void RBT<T>::leftRotation(TreeNode<T>* child, TreeNode<T>* parent){
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



template <class T>
TreeNode<T>* RBT<T>::getMin(){
  TreeNode<T>* current = root;
  TreeNode<T>* parent = current;
  while(current != nullptr){
    parent = current;
    current = current->left;
  }
  // delete current;
  return parent;
}

template <class T>
TreeNode<T>* RBT<T>::getMax(){
  TreeNode<T>* current = root;
  TreeNode<T>* parent = current;
  while(current != nullptr){
    parent = current;
    current = current->right;
  }
  // delete current;
  return parent;
}

template <class T>
bool RBT<T>::contains(T value){
  TreeNode<T>* current = root;
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

template <class T>
bool RBT<T>::deleter(T k){
  TreeNode<T>* current = root;
  TreeNode<T>* parent = current;
  TreeNode<T>* nodeToDelete = nullptr;
  bool isLeft;//checks if node is a left or right child
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
  bool leftIsDoubleBlack;
  if(current->left != nullptr){//check if there is a left value so we know there is a successor
    nodeToDelete = getSuccessor(current);
    bool doubleBlackExists = false;
    TreeNode<T>* successorParent = nodeToDelete->parent;
    swapValue(current, nodeToDelete);
    if(nodeToDelete->color == 'r'){
      if(successorParent->left == nodeToDelete){
        successorParent->left = nullptr;
      }else{
        successorParent->right = nullptr;
      }
      nodeToDelete->parent == nullptr;
      return true;
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
      }else{
        successorParent->left = nodeToDelete->left;
        nodeToDelete->left->parent = successorParent;
        successorParent = successorParent->left;
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
      if(parent->left == nodeToDelete){
        parent->left = nullptr;
      }else if(parent->right == nodeToDelete){
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
      TreeNode<T>* deletersParent = nodeToDelete->parent;// for nodes by itself when it deleted its parent has the double black node
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

template <class T>
TreeNode<T>* RBT<T>::getSuccessor(TreeNode<T>* d){
  TreeNode<T>* successor = d->left;
  while(successor->right != nullptr){
    successor = successor->right;
  }
  return successor;
}

template <class T>
void RBT<T>::fixDoubleBlack(TreeNode<T>* node, bool isLeft){
  if(isLeft){
    if(node->right != nullptr){

      if(node->right->color == 'r'){
        leftRotation(node->right, node);
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
          leftRotation(node->right, node);
          node->switchColor();
          node->right->switchColor();
          if(node->right->right != nullptr){
            node->right->right->switchColor();
          }
        }else if(leftNephewIsRed){
          rightRotation(node->right->left, node->right);
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

  }else{//is right
    if(node->left != nullptr){
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
          // cout << "asd" << endl;
          // levelOrderPrint();
          // cout << endl;
          // cout << node->data << " data" << endl;
          // // cout << rightNephewIsRed << " right red" << endl;
          // // cout << leftNephewIsRed << " left red" << endl;
          // cout << "asd" << endl;

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
