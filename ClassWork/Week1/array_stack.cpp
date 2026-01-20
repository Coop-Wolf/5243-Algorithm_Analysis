#include <iostream>

using namespace std;


struct node
{


};


class Stack
{

    private:
        int* stack;
        int top;
        int size;

        bool full()
            {return top <= size-1;}
        bool empty()
            {return top >= 0;}
        
    public:

        // Init list | Constructors
        Stack():stack(new int[10]), top(-1), size(10){}
        Stack(int size):stack(new int(size)), top(-1), size(size){}


        void push(int x)
        {
            if(!full())
            {
                top++;
                stack[top] = x;
            }
        }


        int pop()
        {
            if(!empty())
            {
                int x = stack[top];
                top--;
                return x;
            }
            else
                cout << "Empty";
                return -99999;
        }


        void print()
        {
            for(int i=top;i>=top;i--)
                {
                    cout << stack[i] << " ";
                }
            cout << endl;
        }
};


class ListStack{};


int main(int args, char** argv)
{
    Stack stack;
    stack.push(4);
    stack.push(11);
    stack.push(76);
    stack.print();
}