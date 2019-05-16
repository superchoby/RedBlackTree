// #include "RedBlackTree.h"
#include "BST.cpp"
#include <iostream>
int main(){
  BST* tree = new BST();


  tree->insert(30);
  tree->insert(40);
  tree->insert(20);
  tree->insert(10);
  tree->insert(25);
  tree->insert(15);
  tree->printTree();
}
