class TreeNode{
  Node();
  Node(int d);
  ~Node();
private:
  Treenode* left;
  Treenode* right;
  int data;
}

Node::Node(){
  left = nullptr;
  right = nullptr;
}

Node::Node(int d){
  data = d;
  left = nullptr;
  right = nullptr;
}

class BST{
public:
  BST();
  virtual ~BST();
  void insert(TreeNode* node, int value);
  bool contains(TreeNode* node, int value); //AKA search
  bool deleteNode(int value);
  TreeNode* getSuccessor(TreeNode* d);
  bool deleteRec();
  bool deleter(int k);
  TreeNode* getMin();
  TreeNode* getMax();
  void printTree();
  void recPrint(TreeNode* node);

private:
  TreeNode* root;
}

BST::BST(){
  root = nullptr;
}

BST::~BST(){
  delete root;
}

BST::insert(TreeNode* node, int value){
  if(root == nullptr){
    root->data = value;
  }else if(value <= root->data){
    insert(node->left, data);
  }else{
    insert(node->right, data);
  }
}

BST::contains(TreeNode* node, int value){
  if(root->data == value){

  }
}
