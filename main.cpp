#include "RedBlackTree.cpp"
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
  tree->insert(2);
  tree->insert(25);
  tree->insert(250);
  // tree->deleter(2);
  // tree->deleter(250);
  // tree->deleter(5);
  // tree->deleter(1);
  // tree->deleter(7);
  // tree->deleter(3);
  // tree->deleter(25);
  tree->deleter(200);
  // tree->deleter(250);
  // tree->deleter(2);
  // tree->deleter(5);

  tree->printTree();
  // tree->deleter(7);
  // std::cout << "lskdf" << std::endl;
  // std::cout << "lskdf" << std::endl;
  // std::cout << "lskdf" << std::endl;
  // tree->printTree();
}
