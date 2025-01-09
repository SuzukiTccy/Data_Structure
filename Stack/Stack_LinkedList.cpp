#include<iostream>
using namespace std;

template <class T>
struct Node{
    T data;
    Node<T> *next;
};

template <class T>
class Stack{
private:
    Node<T>* top; // top of the stack
    size_t size;
    size_t capacity;
public:
    Stack(size_t capacity):top(nullptr),size(0),capacity(capacity){}
    bool isEmpty() const{
        return size == 0;
    }
    bool isFull() const{
        return size == capacity;
    }

    void push(const T& data){
        if(isFull()){
            cout<<"Stack is full"<<endl;
            return;
        }
        Node<T>* temp = new Node<T>;
        temp->data = data;
        temp->next = top;
        top = temp;
        size++;
    }

    void pop(T& target){
        if(isEmpty()){
            cout<<"Stack is empty"<<endl;
            return;
        }
        target = top->data;
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    void print() const{
        Node<T>* temp = top;
        while(temp != nullptr){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
};


int main(){
    Stack<int> stack(5);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.print();

    stack.push(6);

    int target;
    stack.pop(target);
    cout<< "target = " << target <<endl;
    stack.print();

    cout << "<< ===== stack of string ==== >>" << endl;

    Stack<string> stack2(5);
    stack2.push("hello");
    stack2.push("world");
    stack2.push("stack");
    stack2.push("linked");
    stack2.push("list");
    stack2.print();

    stack2.push("overflow");

    string target2;
    stack2.pop(target2);
    cout << "target2 = " << target2 << endl;
    stack2.print();

    return 0;
}