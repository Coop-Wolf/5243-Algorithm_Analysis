## Week 3

### Implemented a Binary Search Tree

### Terms

#### Balance
##### A tree is balanced if the height of the left subtree minus the height of the right subtree is no larger than 1 for every node.

#### Height
##### The length of the longest path from a node to a leaf, or the total number of levels in the tree.

#### Complete
##### A tree where all levels are completely filled except possibly the last level, and all nodes in the last level are as far left as possible.

#### Full/Perfect
##### A tree where every node has either 0 or 2 children (no nodes with only one child).

#### Ancestor
##### Any node that lies on the path from the root to a given node (excluding the node itself).

#### Parents
##### The node directly above a given node that has a reference to it.

#### Descendents
##### All nodes that can be reached by moving downward from a given node (children, grandchildren, etc.).

#### Siblings
##### Nodes that share the same parent.

#### In-Order Successor
##### The next node visited after a given node during an in-order traversal of the tree.

#### In-Order Predecessor
##### The node visited immediately before a given node during an in-order traversal of the tree.

#### O(LogN) search time

---

### Discussing Binary search on Array

---

### Array filled with binary search tree

#### Left Child  - 2* i + 2
#### Right Child - 2* i + 1
#### Parent      - i/ 2 - 1

---

### Binary Heap == Priority Queue

#### Parent < children