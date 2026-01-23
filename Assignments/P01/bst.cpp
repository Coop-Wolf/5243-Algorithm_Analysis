#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    // Parameterized Constructor
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class GraphvizBST {
public:
    static void saveDotFile(const std::string &filename, const std::string &dotContent) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << dotContent;
            outFile.close();
            std::cout << "DOT file saved: " << filename << std::endl;
        } else {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }
    }

    static std::string generateDot(const Node *root) {
        std::string dot = "digraph BST {\n";
        dot += "    node [fontname=\"Arial\"];\n";
        dot += generateDotHelper(root);
        dot += "}\n";
        return dot;
    }

private:
    static std::string generateDotHelper(const Node *node) {
        if (!node)
            return "";
        std::string result;
        if (node->left) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->left->data) + " [label=\"L\"];\n";
            result += generateDotHelper(node->left);
        } else {
            std::string nullNode = "nullL" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        if (node->right) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->right->data) + " [label=\"R\"];\n";
            result += generateDotHelper(node->right);
        } else {
            std::string nullNode = "nullR" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        return result;
    }
};

class Bst {

    // member variable root (Node)
    Node *root;

    // print method
    void _print(Node *subroot)
    {
        // Base case
        if (!subroot)
            return;

        // Recursivly print tree
        else
        {
            _print(subroot->left);
            cout << subroot->data << " ";
            _print(subroot->right);
        }
    }

    // Insert node into tree
    void _insert(Node *&subroot, int x)
    {
        // subroot is null, place node there
        if (!subroot)
            subroot = new Node(x);
        
        else
        {
            // if new node is less than current node, go left
            if (x < subroot->data)
                _insert(subroot->left, x);

            // if new node is greater than current node, go right
            else
                _insert(subroot->right, x);
        }
    }

    /**
     * Remove a leaf node (node with no children) from the BST
     * 
     * @param current Reference to pointer of the node to be removed
     * @param trail Reference to pointer of the parent of the node to be removed
     * 
     * Process:
     * 1. Determine if the leaf is the left or right child of its parent
     * 2. Delete the leaf node
     * 3. Set the parent's appropriate pointer (left or right) to nullptr
     */
    void rmLeaf(Node* &current, Node* &trail)
    {
        if(trail->right == current)
        {
            // Delete desired node
            delete current;
            trail->right = nullptr;
        }

        else if(trail->left == current)
        {
            // Delete desired node
            delete current;
            trail->left = nullptr;
        }
    }


    /**
     * Remove a node with exactly one child from the BST
     * 
     * @param current Reference to pointer of the node to be removed
     * @param trail Reference to pointer of the parent of the node to be removed
     * 
     * Process:
     * 1. Identify which child (left or right) exists
     * 2. Connect the parent (trail) directly to the grandchild
     * 3. Delete the current node, effectively bypassing it in the tree
     */
    void rmOneChild(Node* &current, Node* &trail)
    {
        // Variable pointing to child (single leave)
        Node* child;

        // Point child to correct node
        if(current->left)
            child = current->left;
        if(current->right)
            child = current->right;

        // Delete current and connect trail to child
        if(trail->data > child->data)
        {
            delete current;
            trail->left = child;
        }

        if(trail->data < child->data)
        {
            delete current;
            trail->right = child;
        }
    }


    /**
     * Remove a node with two children from the BST
     * 
     * @param current Reference to pointer of the node to be removed
     * 
     * Process:
     * 1. Find the in-order successor (leftmost node in right subtree)
     * 2. Replace current node's data with successor's data
     * 3. Delete the successor node (which has at most one child)
     * 
     * Strategy: Instead of physically removing current, we replace its value
     * with its successor and delete the successor instead.
     */
    void rmTwoChildren(Node* &current)
    {
        // Keep track of successor and parent node
        Node* parent = current;
        Node* successor = current->right;

        // Get successor
        while(successor->left)
        {
            parent = successor;
            successor = successor->left;
        }

        // copy successor value to current value
        current->data = successor->data;

        // link parent to successors left child
        if(parent->left == successor)
            parent->left = successor->right;
        else
            parent->right = successor->right;

        delete successor;
    }


    /**
     * Remove a node with the specified value from the BST
     * 
     * @param subroot Reference to pointer to the root of the tree/subtree
     * @param x The value to be removed from the tree
     * 
     * Process:
     * 1. Handle edge cases (empty tree, single node)
     * 2. Search for the node to be removed while keeping track of its parent
     * 3. Determine which removal case applies (leaf, one child, two children)
     * 4. Call the appropriate helper function to perform the removal
     */
    void _remove(Node *&subroot, int x)
    {

        Node* current = subroot;
        Node* trail = subroot;

        // Return if subroot is null
        if(!subroot)
        {
            cout << endl << "ERROR: Tree is empty" << endl;
            return;
        }

        // Removing the only node in the tree
        if(subroot->data == x && !subroot->left && !subroot->right)
        {
            delete subroot;
            subroot = nullptr;
            return;
        }

        // Traverse tree until node is found or reached end
        while(current && current->data != x)
        {
            trail = current;

            if(x > current->data)
                current = current->right;

            else
                current = current->left;
        }

        // Error if value is not in tree
        if(!current)
        {
            cout << endl << "ERROR: " << x << " Is not in the tree" << endl;
            return;
        }

        // If match is found
        if(current && current->data == x)
        {

            // If node has two children
            if(current->left && current->right)
                rmTwoChildren(current);

            // If node only has one child
            else if(current->left || current->right)
                rmOneChild(current, trail);
            
            // If node has no children
            else
                rmLeaf(current, trail);
                
        }
    }


    // Return sum of depts of all nodes in the tree
    int _ipl(Node *root, int depth = 0)
    {
        if (!root)
            return 0; // Base case: Empty subtree contributes 0 to IPL
        return depth + _ipl(root->left, depth + 1) + _ipl(root->right, depth + 1);
    }

public:

    // Default Constructor
    Bst() { root = nullptr; }

    // Insert node into tree
    void insert(int x) {_insert(root, x);}

    // Remove node from tree
    void remove(int x) {_remove(root, x);}

    // Search for node in tree
    bool search(int key) { return 0; }

    // Print tree
    void print() { _print(root); }

    // IDK
    void saveDotFile(const std::string &filename)
    {
        std::string dotContent = GraphvizBST::generateDot(root);
        GraphvizBST::saveDotFile(filename, dotContent);
    }

    /**
     * Computes the Internal Path Length (IPL) of a Binary Search Tree (BST).
     *
     * Definition:
     * The Internal Path Length (IPL) of a BST is the sum of the depths of all nodes in the tree.
     * The depth of a node is the number of edges from the root to that node.
     *
     * Example:
     *        10
     *       /  \
     *      5    15
     *     / \     \
     *    2   7    20
     *
     * IPL = (depth of 10) + (depth of 5) + (depth of 15) + (depth of 2) + (depth of 7) + (depth of 20)
     *     = 0 + 1 + 1 + 2 + 2 + 2 = 8
     *
     * @param root Pointer to the root node of the BST.
     * @param depth Current depth of the node (default is 0 for the root call).
     * @return The sum of depths of all nodes (Internal Path Length).
     */
    int ipl() {
        return _ipl(root);
    }
};



// Determine if value is duplicate to any value in vector
bool unique_value(int *arr, int size, int x)
{
    // Loop through array and check every value for copy
    for (int i = 0; i < size; i++)
    {
        // If copy, return false
        if (arr[i] == x)
            return false;
    }

    // return true if no copies
    return true;
}


// Test Case 1: Attempt to remove a node from an empty BST
// -------------------------------------------------------
// Expected behavior: The tree should handle the operation safely
// and report an error indicating that the tree is empty.
// This test verifies that remove() does not crash or modify the tree
// when called on an empty BST.
void testCase1(Bst tree1)  {tree1.remove(1);}


// Test Case 2: Insert and remove a single node from the BST
// ---------------------------------------------------------
// Expected behavior: After inserting one node, removing that same
// node should result in an empty tree.
// This test verifies that remove() correctly handles deleting
// the root node when it is the only node in the tree.
void testCase2(Bst tree2);


// Test Case 3: Remove a leaf node from the BST
// Expected behavior: The specified leaf node should be removed
// without affecting the rest of the tree structure.
// This test verifies that remove() correctly handles deleting
// a node with no children (leaf node).
void testCase3(Bst tree3);


// Test Case 4: Remove a node with one child
// Expected behavior: The node should be removed and its single child
// should take its place in the tree.
// This test verifies that remove() correctly reconnects the parent
// to the child when deleting a node with exactly one child.
void testCase4(Bst tree4);


// Test Case 5: Remove a node with two children
// Expected behavior: The node should be removed and replaced by
// its in-order successor (or predecessor), preserving BST properties.
// This test verifies that remove() correctly handles the most complex
// deletion case involving two children.
void testCase5(Bst tree5);


// Test Case 6: Attempt to remove a node that is not in the BST
// Expected behavior: The tree should remain unchanged and report
// an error indicating that the value is not in the tree.
// This test verifies that remove() safely handles invalid input
// without modifying the tree or causing a crash.
void testCase6(Bst tree6);


// Test Case 7: Multiple insertions and deletions with BST validation
// Expected behavior: After performing a sequence of insertions and
// deletions, the tree should still maintain the Binary Search Tree
// ordering property.
// This test serves as an integration/stress test to ensure that
// repeated operations do not corrupt the tree structure.
// The tree is printed to visually verify that the BST property
// is preserved after all operations.
void testCase7(Bst tree7);


int main()
{
    // Create tree object
    Bst tree1;
    Bst tree2;
    Bst tree3;
    Bst tree4;
    Bst tree5;
    Bst tree6;
    Bst tree7;


    cout << endl << "Test Case 1: Empty Tree.\n";
    cout <<         "------------------------";
    testCase1(tree1);

    cout << endl << "\nTest Case 2: Single Node in Tree.\n";
    cout <<         "---------------------------------\n\n";
    testCase2(tree2);

    cout << endl << "\nTest Case 3: Removing node from Tree.\n";
    cout <<         "-------------------------------------\n\n";
    testCase3(tree3);

    cout << endl << "\nTest Case 4: Removing node with one child.\n";
    cout <<         "------------------------------------------\n\n";
    testCase4(tree4);

    cout << endl << "\nTest Case 5: Removing node with two children.\n";
    cout <<         "---------------------------------------------\n\n";
    testCase5(tree5);

    cout << endl << "\nTest Case 6: Removing node that doesn't exist in tree.\n";
    cout <<         "------------------------------------------------------\n\n";
    testCase6(tree6);

    cout << endl << "\nTest Case 7: Inserting and Removing nodes continuously.\n";
    cout <<         "-------------------------------------------------------\n\n";
    testCase7(tree7);
}


// Function Definitions

void testCase2(Bst tree2)
{
    tree2.insert(1);

    cout << "Tree before removing node:\n";
    tree2.print();

    tree2.remove(1);

    cout << "\nTree after removing node:\n";
    tree2.print();
}

void testCase3(Bst tree3)
{
    tree3.insert(50);
    tree3.insert(70);
    tree3.insert(40);
    tree3.insert(30);

    cout << "Tree before removing node 30:\n";
    tree3.print();

    tree3.remove(30);

    cout << "\nTree after removing node 30:\n";
    tree3.print();
}


void testCase4(Bst tree4)
{
    tree4.insert(50);
    tree4.insert(70);
    tree4.insert(40);
    tree4.insert(30);

    cout << "Tree before removing node 40:\n";
    tree4.print();

    tree4.remove(40);

    cout << "\nTree after removing node 40:\n";
    tree4.print();
}


void testCase5(Bst tree5)
{
    tree5.insert(50);
    tree5.insert(70);
    tree5.insert(40);
    tree5.insert(30);
    tree5.insert(45);

    cout << "Tree before removing node 40:\n";
    tree5.print();

    tree5.remove(40);

    cout << "\nTree after removing node 40:\n";
    tree5.print();
}


void testCase6(Bst tree6)
{
    tree6.insert(50);
    tree6.insert(70);
    tree6.insert(40);
    tree6.insert(30);
    tree6.insert(45);
    tree6.print();

    cout << "\nAttempting to remove node 100 from the tree.";
    tree6.remove(100);
}


void testCase7(Bst tree7)
{
    int root = 5000;
    int max = 10000;

    // Create vector of ints
    vector<int> arr;

    // append root to vector
    arr.push_back(root);

    // insert root into tree
    tree7.insert(root);

    // insert 5000 nodes into tree and vector
    for (int i = 1; i < 5000; i++)
    {
        // Generate random number
        int r = rand() % max;

        // Generate random number until its not a duplicate
        while (!unique_value(arr.data(), arr.size(), r))
            r = rand() % max;
        
        // Insert value into tree and vector
        tree7.insert(r);
        arr.push_back(r);

        // Every 5 iterations, remove a random node
        if(i % 5==0 && !arr.empty())
        {
            // Getting random index and value from vector.
            // Had help from Chat with random implementation.
            int index = rand() % arr.size();
            int randNode = arr[index];

            // Removing node from tree and vector
            tree7.remove(randNode);
            arr.erase(arr.begin() + index);
        }
    }

    tree7.saveDotFile("bst_snapshot.dot");
}