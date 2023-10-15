#ifndef AVLTreeMap_h
#define AVLTreeMap_h

#include "AVLTree.h"

template <typename E>  // an AVL Tree (Ordered) Map
class AVLTreeMap : public AVLTree<E> {
public:
  typedef AVLTree<E> AVLTree;
  typedef typename AVLTree::ST ST;
  typedef typename AVLTree::TPos TPos;
  typedef typename AVLTree::Iterator Iterator;
  typedef typename E::Key K;
  typedef typename E::Value V;
public:
  AVLTreeMap();  // default constructor
  ~AVLTreeMap(); // default destructor

  Iterator put(const K& k, const V& v);	// insert/replace pair (k,v)
  Iterator firstEntry(); // iterator to smallest key value entry
  Iterator lastEntry(); // iterator to largest key value entry
  Iterator ceilingEntry(const K& k); // iterator to entry with least key value >= k
  Iterator floorEntry(const K& k); // iterator to entry with greatest key value <= k
  Iterator lowerEntry(const K& k); // iterator to entry with greatest key value < k
  Iterator higherEntry(const K& k); // iterator to entry with least key value > k
  
};

template <typename E>					// constructor
AVLTreeMap<E>::AVLTreeMap() : AVLTree() { }

template <typename E>					// destructor
AVLTreeMap<E>::~AVLTreeMap() { }


template <typename E>
typename AVLTree<E>::Iterator AVLTreeMap<E>::put(const K& k, const V& v) {
  TPos w = AVLTree::finder(k, ST::root());
  if (w.isExternal()) return AVLTree::insert(k,v);
  w.getElement().setValue(v);
  return Iterator(w);
}

template <typename E>
typename AVLTree<E>::Iterator AVLTreeMap<E>::firstEntry() {
  if (ST::empty()) return ST::end();
  return ST::begin();
}

template <typename E>
typename AVLTree<E>::Iterator AVLTreeMap<E>::lastEntry() {
  if (ST::empty()) return ST::end();
  return --Iterator(ST::end());
}

template <typename E>
typename AVLTree<E>::Iterator AVLTreeMap<E>::ceilingEntry(const K& k) {
  if (ST::empty()) return ST::end();
  TPos w = finder(k, ST::root());
  if (w.isExternal()) {
    if (w.parent().left() == w) return Iterator(w.parent());
    return ++Iterator(w.parent());
  }
  return Iterator(w);
}

template <typename E>
typename AVLTree<E>::Iterator AVLTreeMap<E>::floorEntry(const K& k) {
  if (ST::empty()) return ST::end();
  TPos w = finder(k, ST::root());
  if (w.isExternal()) {
    if (w.parent().right() == w) return Iterator(w.parent());
    return --Iterator(w.parent());
  }
  return Iterator(w);
}

template <typename E>
typename AVLTree<E>::Iterator AVLTreeMap<E>::lowerEntry(const K& k) {
  Iterator i = floorEntry(k);
  if (i.key() == k) --i;
  return i;
}

template <typename E>
typename AVLTree<E>::Iterator AVLTreeMap<E>::higherEntry(const K& k) {
  Iterator i = ceilingEntry(k);
  if (i.key() == k) ++i;
  return i;
}


#endif
