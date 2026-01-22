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

    void rmLeaf(Node* &current, Node* &trail)
    {
        if(trail->right == current)
        {
            // Delete desired node
            delete current;
            trail->right = nullptr;
        }

        if(trail->left == current)
        {
            // Delete desired node
            delete current;
            trail->left = nullptr;
        }
    }

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

    // NEED COMMENTS
    // ALSO NEED TO CREATE 3 SEPARETE FUNCTIONS FOR EACH CASE (NO CHILDREN, ONE CHILD, TWO CHILDREN)
    void _remove(Node *&subroot, int x)
    {

        // Return is subroot is null
        if(!subroot)
            return;

        Node* current = subroot;
        Node* trail = subroot;

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

int main()
{
    // Create tree object
    Bst tree;

    // set root to 16384
    // set max to 32767
    // int root = pow(2, 15) / 2;
    // int max = pow(2, 15) - 1;

    int root = 5000;
    int max = 10000;

    // Create vector of ints
    vector<int> arr;

    // append root to vector
    arr.push_back(root);

    // insert root into tree
    tree.insert(root);

    // insert 5000 nodes into tree and vector
    for (int i = 1; i < 100; i++) {
        int r = rand() % max;

        // Generate random number until its not a duplicate
        while (!unique_value(arr.data(), arr.size(), r))
            r = rand() % max;
        
        // Insert value into tree and vector
        tree.insert(r);
        arr.push_back(r);
    }


    tree.print();
    cout << endl << endl;

    tree.saveDotFile("bst_snapshot.dot");

    Bst tree2;
    tree2.insert(10);
    tree2.insert(5);
    tree2.insert(15);
    tree2.insert(2);
    tree2.insert(7);
    tree2.insert(20);
    cout << "Internal Path Length: " << tree2.ipl() << endl;
}
