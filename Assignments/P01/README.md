## Deletion Implementation in a BST


In this program, I was tasked with implementing the deletion operation for a Binary Search Tree. The deletion operation must handle three different cases: deleting a leaf node, deleting a node with one child, and deleting a node with two children. Deleting a leaf node involves simply removing the node and updating its parent’s connection to null. Deleting a node with one child requires removing the node and connecting its parent directly to its child, preserving the structure of the tree. Deleting a node with two children is more complex. The two approaches are replacing the node with its in-order successor or its in-order predecessor. I chose to use the in-order successor, which is the smallest node in the right subtree, because this is the most commonly used approach.

The process of removing a node with two children involves first locating the node to delete, then finding its replacement. To find the in-order successor, I traverse to the right child of the node and continue left until reaching the leftmost node. This node becomes the successor and replaces the deleted node, maintaining the Binary Search Tree property.

Some challenges I encountered included deciding whether to implement the deletion recursively or iteratively, constantly debugging segmentation faults, as well as ensuring that all cases were properly handled when deleting nodes in the BST.



## Files:
| Files                 | Description                                         |
|-----------------------|-----------------------------------------------------|
| bst.cpp               | Main c++ code.                                      |
| bst                   | Executable code.                                    |
| bst_snapshop.dot      | Visual output of Binary Search Tree.                |


## Instruction

1. Clone the repository or connect through GitHub Codespaces in VS Code.
2. Locate the directory where the program exists:
   - `/workspaces/5243-Algorithm_Analysis/Assignments/P01`
3. Compile the code:
   - `g++ bst.cpp -o bst`
4. Run the code:
   - `./bst`
5. View the output in the terminal and in the `bst_snapshot.dot` file.
