# Analysis of Data Structure Comparisons

Based on four different workload types and six input sizes (100, 1,000, 5,000, 10,000, 20,000, and 40,000), we analyzed the number of comparisons performed by each data structure under varying conditions. The goal was to evaluate how each structure behaves as both workload type and input size scale.

---

## Workload A: Random Inserts and Contains

In the analysis of Workload A, the linked list structure has the highest number of comparisons by a significant margin, followed by arrays. This behavior is expected because linked lists require linear traversal for both insertions and lookups, resulting in a large number of comparisons.

Arrays also perform poorly in this workload due to the need for linear searches when the data is not ordered. In contrast, data structures such as binary search trees, hash tables, and heaps avoid full traversal for most operations, leading to fewer comparisons overall.

---

## Workload B: Ordered Inserts Followed by Contains

In Workload B, the binary search tree (BST) exhibits the highest number of comparisons, followed by the linked list. This is primarily due to the ordered nature of the inserts.

When elements are inserted in sorted order, the BST becomes unbalanced and effectively degrades into a linear structure (similar to a linked list). As a result, each insertion requires traversing deeper into the tree, increasing the number of comparisons. Additionally, even though all nodes are inserted to the right, comparisons are still required at each step to determine placement.

This demonstrates a worst-case scenario for BSTs, where their expected logarithmic performance degrades to linear time.

---

## Workload C: 50% Contains, 25% Inserts, 25% Deletes

In Workload C, the linked list again produces the highest number of comparisons, followed by arrays and BSTs. This workload includes a mix of operations, with a heavy emphasis on lookups.

Linked lists perform poorly due to the linear cost of searching. However, they benefit slightly from efficient deletions, which require minimal restructuring once the target node is found.

Binary search trees perform worse than expected due to the complexity of deletion operations. When deleting a node with two children, additional comparisons are required to locate a suitable replacement (such as the in-order successor), increasing overall cost.

Arrays also struggle in this workload because searches are performed on unsorted data, forcing linear traversal. Additionally, insertions and deletions may require shifting elements, contributing to increased operation costs.

---

## Workload D: n Inserts, 5n Lookups

In Workload D, the linked list performs the worst by a wide margin. This is due to the heavy emphasis on lookup operations.

Since each lookup in a linked list requires linear traversal, the large number of lookups (5n) results in a dramatic increase in total comparisons. This highlights the inefficiency of linked lists in read-heavy scenarios.

In contrast, data structures optimized for fast lookup operations, such as hash tables and balanced trees, perform significantly better under this workload.

---