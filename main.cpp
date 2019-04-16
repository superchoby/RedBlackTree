#include "PracticeBST.cpp"

int main(){
  BST* tree = new BST();
  tree->insert(5);
  tree->insert(3);
  tree->insert(7);
  // tree->deleter(50);
  tree->insert(1);
  tree->insert(200);
  tree->insert(2);
  tree->insert(25);
  tree->insert(250);

  tree->printTree();
}
