#include "RedBlackTree.h"
// #include "BST.cpp"
#include <iostream>
int main(){
  RBT* tree = new RBT();
  tree->insert(5);
  tree->insert(3);
  tree->insert(7);
  // tree->deleter(50);
  tree->insert(1);
  tree->insert(200);
  tree->insert(25);
  // tree->insert(250);
  // tree->deleter(200);

  // tree->printTree();
}
