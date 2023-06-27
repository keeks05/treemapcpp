#ifndef TREEMAP_H_
#define TREEMAP_H_
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <utility>

template <typename K, typename V>
class Treemap {
 public:
  //
  // @@@ The class's public API below should _not_ be modified @@@
  //

  // * Capacity
  // Returns number of key-value mappings in map --O(1)
  size_t Size();
  // Returns true if map is empty --O(1)
  bool Empty();

  // * Modifiers
  // Inserts @key in map --O(log N) on average
  // Throws exception if key already exists
  void Insert(const K &key, const V &value);
  // Remove @key from map --O(log N) on average
  // Throws exception if key doesn't exists
  void Remove(const K &key);

  // * Lookup
  // Return value corresponding to @key --O(log N) on average
  // Throws exception if tree is empty or key doesn't exists
  const V& Get(const K &key);

  // Return greatest key less than or equal to @key --O(log N) on average
  // Throws exception if tree is empty or no floor exists for key
  const K& FloorKey(const K &key);
  // Return least key greater than or equal to @key --O(log N) on average
  // Throws exception if tree is empty or no ceil exists for key
  const K& CeilKey(const K &key);

  // Return whether @key is found in map --O(log N) on average
  bool ContainsKey(const K& key);
  // Return whether @value is found in map --O(N)
  bool ContainsValue(const V& value);

  // Return max key in map --O(log N) on average
  // Throws exception if tree is empty
  const K& MaxKey();
  // Return min key in map --O(log N) on average
  // Throws exception if tree is empty
  const K& MinKey();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  // ...To be completed...
  struct Node {
    K key;
    V value;
    std::unique_ptr<Node> right;
    std::unique_ptr<Node> left;
  };
  std::unique_ptr<Node> root;
  size_t size = 0;

  // Private constants
  // ...To be completed (if any)...

  // Private methods
  // ...To be completed (if any)...
  Node* Min(Node *n);
  void Insert(std::unique_ptr<Node> &n, const K& key, const V& value);
  void Remove(std::unique_ptr<Node> &n, const K& key);
};

// Return member size - keep track of size of map
template <typename K, typename V>
size_t Treemap<K, V>::Size() {
  return size;
}

// Check if map is empty by comapring size of treemap
template <typename K, typename V>
bool Treemap<K, V>::Empty() {
  if (!size)
    return true;
  return false;
}

// Public API method
template <typename K, typename V>
void Treemap<K, V>::Insert(const K &key, const V &value) {
  // Recursive helper
  Insert(root, key, value);
}

// Recusive helper method
template <typename K, typename V>
void Treemap<K, V>::Insert(std::unique_ptr<Node> &n,
const K& key, const V& value) {
  // Gotten from lecture code BST
  // Error handling
  if (ContainsKey(key))
    throw std::logic_error("Duplicate key");
  // Create new node and increase size
  if (!n) {
    n = std::unique_ptr<Node>(new Node{key, value});
    size++;

  // Determine where to go based on the key (recurse right or left)
  } else if (key < n->key) {
    Insert(n->left, key, value);
  } else if (key > n->key) {
    Insert(n->right, key, value);
  } else {
    throw std::logic_error("Duplicate key");
  }
}

// Recursive helper method to get the min of a subtree
template <typename K, typename V>
typename Treemap<K, V>::Node* Treemap<K, V>::Min(Node *n) {
  // Gotten from lecture code BST
  if (n->left)
    return Min(n->left.get());
  else
    return n;
}

template <typename K, typename V>
void Treemap<K, V>::Remove(const K &key) {
  // Recursive helper
  if (!ContainsKey(key))
    throw std::invalid_argument("Invalid key");
  if (Empty())
    throw std::underflow_error("Empty tree");

  Remove(root, key);
}

template <typename K, typename V>
void Treemap<K, V>::Remove(std::unique_ptr<Node> &n, const K& key) {
  // Gotten from BST lecture code
  if (!n) return;

  if (key < n->key) {
    Remove(n->left, key);
  } else if (key > n->key) {
    Remove(n->right, key);
  } else {
    if (n->left && n->right) {
      n->key = Min(n->right.get())->key;
      Remove(n->right, n->key);
    } else {
      n = std::move((n->left) ? n->left : n->right);
      size--;
    }
  }
}

template <typename K, typename V>
const V& Treemap<K, V>::Get(const K &key) {
  // Error handling
  if (Empty())
    throw std::underflow_error("Empty tree");
  if (!ContainsKey(key))
    throw std::invalid_argument("Invalid key");
  // Start at the root node
  Node *n = root.get();

  // Iterate through the root node and find the key
  while (n) {
    if (key == n->key)
      return n->value;
    if (key < n->key)
      n = n->left.get();
    if (key > n->key)
      n = n->right.get();
  }
  throw std::logic_error("Key doesn't exist");
}

template <typename K, typename V>
const K& Treemap<K, V>::FloorKey(const K &key) {
  // Throw if empty
  if (Empty())
    throw std::underflow_error("Empty tree");
  if (key < MinKey())
    throw std::logic_error("No floor");
  // Edge case
  if (ContainsKey(key))
    return key;
  // Start at root
  Node *n = root.get();
  Node *temp = root.get();

  // Iterate through tree
  while (n->left && n->right) {
    if (n->key > key)
      n = n->left.get();
    else if (n->key < key)
      n = n->right.get();
    if (n->key <= key) {
      temp = n;
    }
  }
  return temp->key;
}

template <typename K, typename V>
const K& Treemap<K, V>::CeilKey(const K &key) {
// Throw if empty
  if (Empty())
    throw std::underflow_error("Empty tree");
  if (key > MaxKey())
    throw std::logic_error("No ceil");
  // Edge case
  if (ContainsKey(key))
    return key;

  // Start at root
  Node *n = root.get();
  Node *temp = root.get();
  // Iterate through tree
  while (n->left && n->right) {
    if (n->key > key)
      n = n->left.get();
    else if (n->key < key)
      n = n->right.get();
    if (n->key >= key) {
      temp = n;
    }
  }
  return temp->key;
}

template <typename K, typename V>
bool Treemap<K, V>::ContainsKey(const K& key) {
  // Get the root node and traverse through tree comaparing keys
  // Gotten from lecture slide code for BST
  Node *n = root.get();
  while (n) {
    if (key == n->key)
      return true;
    if (key < n->key)
      n = n->left.get();
    else
      n = n->right.get();
  }
  return false;
}

template <typename K, typename V>
bool Treemap<K, V>::ContainsValue(const V& value) {
  /* Create a stack to go through nodes one by one and check the value
     Gotten from discussion #5 through the use of a stack */
  std::stack<Node*> nodes;
  Node* copyRoot = root.get();
  nodes.push(copyRoot);
  while (!nodes.empty()) {
    Node *item = nodes.top();
    nodes.pop();
    if (value == item->value)
      return true;
    if (item->right)
      nodes.push(item->right.get());
    if (item->left)
      nodes.push(item->left.get());
  }
  return false;
}

template <typename K, typename V>
const K& Treemap<K, V>::MaxKey() {
  // Error handling
  if (Empty())
    throw std::underflow_error("Tree is empty");
  // Iterate through the right and find max key
  // Lecture slide code BST
  Node *n = root.get();
  while (n->right)
    n = n->right.get();
  return n->key;
}

template <typename K, typename V>
const K& Treemap<K, V>::MinKey() {
  // Error handling
  if (Empty())
    throw std::underflow_error("Tree is empty");
  // Iterate through the left and find min key
  // Lecture slide code BST
  Node *n = root.get();
  while (n->left)
    n = n->left.get();
  return n->key;
}

#endif  // TREEMAP_H_
