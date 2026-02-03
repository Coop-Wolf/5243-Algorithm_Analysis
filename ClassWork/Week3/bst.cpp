#include <iostream>
#include <ctime>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(): data(0), left(nullptr), right(nullptr) {}
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Bst
{

private:
    Node* root;

    void _insert(Node* &subroot, Node* &temp)
    {
        if(!subroot)
        {
            subroot = temp;
            return;
        }
        if(temp->data < subroot->data)
            _insert(subroot->left, temp);
        else
            _insert(subroot->right, temp);
    }

    void _print(Node* subroot)
    {
        if(!subroot)
        {
            return;
        }
        else
        {
            // Pre-order print
            _print(subroot->left);
            // In-order print
            cout << subroot->data << " ";
            _print(subroot->right);
            // Post-order print
        }
    }

public:

    Bst():root(nullptr) {}

    void insert(int x)
    {
        Node* temp = new Node(x);
        if(!root)
        {
            root = temp;
        }
        else
            _insert(root, temp);

        return;
    }

    int search()
    {
        return 0;
    }

    void print()
    {
        _print(root);
    }


};


int main(int argc, char** argv)
{
    srand(time(0));
    Bst b;
    b.insert(500);
    b.insert(8);
    b.insert(7);

    for(int i=0;i<10;i++)
    {
        int r = rand()%1000;
        b.insert(r);
    }

    b.print();
    cout << endl;
    return 0;
}