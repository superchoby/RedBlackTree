#include "RedBlackTree.h"
// #include "BST.cpp"
#include <iostream>
int main(){
  RBT* tree = new RBT();
  tree->insert(8);
  tree->insert(5);
  tree->insert(15);
  // tree->deleter(50);
  tree->insert(12);
  tree->insert(19);
  tree->insert(9);
  tree->insert(13);
  tree->insert(23);
  tree->insert(10);
  // tree->insert(4);
  // tree->insert(3);
  // tree->insert(3);
  // tree->insert(250);
  // tree->deleter(200);

  tree->levelOrderPrint();
}
