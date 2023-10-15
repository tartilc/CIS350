#ifndef MyLinkedBinaryTree_h
#define MyLinkedBinaryTree_h

#include <list>

template <typename Elem>					// Base element type
class MyLinkedBinaryTree {
protected:
  // insert Node declaration here...
  
  struct Node {					// a node of the tree
    Elem    elt;					// element value
    Node*   par;					// parent
    Node*   left;					// left child
    Node*   right;					// right child
    Node() : elt(), par(NULL), left(NULL), right(NULL) { } // constructor
  };
  
public:
  // insert Position declaration here...
  
  class Position {					// position in the tree
  private:
    Node* v;						// pointer to the node
  public:
    Position(Node* _v = NULL) : v(_v) { }		// constructor
    Elem& operator*()					// get element
    { return v->elt; }
    Elem& getElement() const 
    { return v->elt; }
    Elem* getElementPtr() const 
    { return &(v->elt); }
    Position left() const				// get left child
    { return Position(v->left); }
    Position right() const				// get right child
    { return Position(v->right); }
    Position parent() const				// get parent
    { return Position(v->par); }
    bool isRoot() const				// root of the tree?
    { return v->par == NULL; }
    bool isExternal() const				// an external node?
    { return v->left == NULL && v->right == NULL; }
    bool isInternal() const				// an internal node?
    { return !isExternal(); }
    bool operator==(const Position& p) const { return (v == p.v); }  // overloading ==
    //bool operator ==(const Position &p1, const Position &p2) const { return (p1.v == p2.v); }  // overloading ==
    bool isNodeNULL() const
    { return (v == NULL); }
    friend class MyLinkedBinaryTree;			// give tree access
  };
  typedef std::list<Position> PositionList;		// list of positions
  
public:
  MyLinkedBinaryTree();					// constructor
  int size() const;					// number of nodes
  bool empty() const;					// is tree empty?
  Position root() const;				// get the root
  PositionList positions() const;  			// list of nodes
  void addRoot();					// add root to empty tree
  void expandExternal(const Position& p);		// expand external node
  Position removeAboveExternal(const Position& p);	// remove p and parent
  void rotate(const Position& p);   // rotate p above parent
  // housekeeping functions omitted...
  ~MyLinkedBinaryTree(); // destructor
protected: 						// local utilities
  void preorder(Node* v, PositionList& pl) const;	// preorder utility
  void relink(Node* parent, Node* child, bool make_left_child);  // relink utility
private:
  Node* _root;					// pointer to the root
  int n;						// number of nodes
  void deleteTree(Node *n); // delete subtree rooted at node pointed by n
};


template <typename Elem>
MyLinkedBinaryTree<Elem>::MyLinkedBinaryTree()			// constructor
  : _root(NULL), n(0) { }

template <typename Elem>
void MyLinkedBinaryTree<Elem>::deleteTree(Node *n) // delete subtree rooted at node pointed by n
{
  if (n == NULL) return;

  deleteTree(n->left);
  deleteTree(n->right);
}
template <typename Elem>
MyLinkedBinaryTree<Elem>::~MyLinkedBinaryTree()			// destructor
{
  deleteTree(_root->par);
  deleteTree(_root);
}

template <typename Elem>
int MyLinkedBinaryTree<Elem>::size() const			// number of nodes
{ return n; }

template <typename Elem>
bool MyLinkedBinaryTree<Elem>::empty() const			// is tree empty?
{ return size() == 0; }

template <typename Elem>
typename MyLinkedBinaryTree<Elem>::Position MyLinkedBinaryTree<Elem>::root() const // get the root
{ return Position(_root); }

template <typename Elem>
void MyLinkedBinaryTree<Elem>::addRoot()			// add root to empty tree
{ _root = new Node; n = 1; }

// expand external node
template <typename Elem>
void MyLinkedBinaryTree<Elem>::expandExternal(const Position& p) {
  Node* v = p.v;					// p's node
  v->left = new Node;					// add a new left child
  v->left->par = v;					// v is its parent
  v->right = new Node;				// and a new right child
  v->right->par = v;					// v is its parent
  n += 2;						// two more nodes
}

template <typename Elem>
typename MyLinkedBinaryTree<Elem>::Position				// remove p and parent
MyLinkedBinaryTree<Elem>::removeAboveExternal(const Position& p) {
  Node* w = p.v;  Node* v = w->par;			// get p's node and parent
  Node* sib = (w == v->left ?  v->right : v->left);
  if (v == _root) {					// child of root?
    _root = sib;					// ...make sibling root
    sib->par = NULL;
  }
  else {
    Node* gpar = v->par;				// w's grandparent
    if (v == gpar->left) gpar->left = sib; 		// replace parent by sib
    else gpar->right = sib;
    sib->par = gpar;
  }
  delete w; delete v;					// delete removed nodes
  n -= 2;						// two fewer nodes
  return Position(sib);
}

// list of all nodes
template <typename Elem>
typename MyLinkedBinaryTree<Elem>::PositionList MyLinkedBinaryTree<Elem>::positions() const {
  PositionList pl;
  preorder(_root, pl);					// preorder traversal
  return PositionList(pl);				// return resulting list
}  

// preorder traversal
template <typename Elem>
void MyLinkedBinaryTree<Elem>::preorder(Node* v, PositionList& pl) const {
  pl.push_back(Position(v));				// add this node
  if (v->left != NULL)					// traverse left subtree
    preorder(v->left, pl);
  if (v->right != NULL)					// traverse right subtree
    preorder(v->right, pl);
}

// Rotate Position p above its parent
template <typename Elem>
void MyLinkedBinaryTree<Elem>::rotate(const Position& p) {
  Node* x = p.v;  
  Node *y = x->par;  // we assume this exists
  Node *z = y->par;  // grandparent (possibly NULL)

  if (z == NULL) {
    _root = x;  // x becomes root
    x->par = NULL;
  }
  else relink(z, x, y == z->left);  // x becomes a direct child of z
  // now rotate x and y, including transfer of middle subtree
  if (x == y->left) {
    relink(y, x->right, true);  // x->right becomes left child of y
    relink(x, y, false);  // y becomes right child of x
  }
  else {
    relink(y, x->left, false);  // x->left becomes right child of y
    relink(x, y, true);  // y becomes left child of x
  }
}

// Relink parent node with child node (we allow the child to be NULL).
template <typename Elem>
void MyLinkedBinaryTree<Elem>::relink(Node* parent, Node* child, bool make_left_child){  // relink utility

  if (make_left_child)
    parent->left = child;
  else
    parent->right = child;
  if (child != NULL)
    child->par = parent;
}

#endif
