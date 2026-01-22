#include <iostream>

using namespace std;

// One pointer is singly linked list
// Two pointer is doubly linked list
// N pointer implied graph
struct Node
{
    //data stuff
    Node* next;
    int data;

    Node(int data): data(data), next(nullptr){};
    


};


class LL
{
    protected:
        Node* head;
        Node* tail;

    // push value to end of linked list
    void enpush(int x)
    {
        Node* temp = new Node(x);

        // Empty list
        if(!head)
            head = tail = temp;

        // List not empty
        // Appending node to end of list
        else
        {
            tail->next = temp;
            tail = tail->next;
        }
    }

    // push value to front of linked list
    void frontpush(int x)
    {
        Node* temp = new Node(x);

        if(!head)
            head = tail = temp;
        
        else
        {
            temp->next = head;
            head = temp;
        }
    }


    public:
        LL():head(nullptr), tail(nullptr){};





    void print()
    {
        Node* travel = head;
        
        while(travel)
        {
            cout << "[" << travel->data << "]";
            
            if(travel->next)
                cout << "->";

            travel = travel->next;
        }
    }


};



class Order: public LL
{
    public:
        void push(int x)
        {

            // Empty
            if(!head)
                frontpush(x);

            // Front push
            if(x <= head->data)
                frontpush(x);

            // End push
            else if(x >= tail->data)
                enpush(x);

            // In-Order Push
            else
            {
                Node *temp = new Node(x);
                Node* travel = head;

                while(temp->data > travel->next->data)
                {
                    travel = travel->next;
                }

                // Stop traversing and insert
                temp->next = travel->next;
                travel->next = temp;
            }
            
        }
};


int main(int argc, char** argv)
{
    Order l;

    //l.enpush(1);

    for(int i=0;i<20;i++)
    {
        l.push(rand()%100);
    }


   // l.enpush(100);
    l.print();
    cout << endl;
    return 0;
}