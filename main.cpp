#include "RedBlackTree.h"
// #include "BST.cpp"
#include <iostream>
int main(){
  RBT* tree = new RBT();


  tree->insert(30);
  tree->insert(40);
  tree->insert(20);
  //
  tree->insert(45);
  tree->redBlackTreeDelete(20);
  // tree->insert(77);
  // tree->insert(435);
  // tree->insert(38);
  // //
  // tree->insert(8);
  // tree->insert(5);
  // tree->insert(15);
  // tree->insert(12);
  // tree->insert(19);
  // tree->insert(9);
  // tree->insert(13);
  // tree->insert(23);
  // tree->insert(10);
  tree->levelOrderPrint();
}
