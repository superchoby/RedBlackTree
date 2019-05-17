#include "RedBlackTree.h"
// #include "BST.cpp"
#include <iostream>
int main(){
  RBT* tree = new RBT();


  tree->insert(30);
  tree->insert(40);
  tree->insert(20);
  tree->insert(10);
  tree->insert(25);
  tree->insert(15);
  tree->insert(67);
  tree->insert(98);
  tree->deleter(20);
  tree->deleter(67);
  tree->insert(234);
  tree->deleter(234);
  tree->insert(54);
  tree->insert(34);
  tree->deleter(54);
  tree->deleter(34);
  tree->deleter(98);
  tree->insert(342);

  tree->deleter(30);
  tree->deleter(25);
  tree->deleter(40);
  tree->deleter(10);

  tree->insert(20);
  tree->insert(10);
  tree->insert(25);
  tree->insert(15);
  tree->insert(67);
  tree->insert(98);
  tree->deleter(20);
  tree->deleter(67);
  tree->insert(234);
  tree->deleter(234);
  tree->insert(54);
  tree->insert(34);
  tree->deleter(54);
  tree->deleter(34);
  tree->deleter(98);
  tree->insert(342);

  tree->deleter(25);
  tree->deleter(10);
  //
  //

  tree->levelOrderPrint();
}
