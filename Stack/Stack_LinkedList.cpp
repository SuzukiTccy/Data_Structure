#include<iostream>
using namespace std;

template <class T>
struct Node{
    T data;
    Node<T> *next;
};

template <class T>
class LinkedStack{
private:
    Node<T> *top;
    size_t size;
    size_t capacity;
public:
    LinkedStack(size_t capacity):top(nullptr), size(0), capacity(capacity){}

    ~LinkedStack(){
        Node<T> *temp = top;
        while(temp != nullptr){
            top = top->next;
            delete temp;
            temp = top;
        }
    }

    bool isEmpty() const{
        return size == 0;
    }

    bool isFull() const{
        return size == capacity;
    }

    void push(const T &data){
        if(isFull()){
            cout << "LinkedStack is full!" << endl;
            return;
        }
        Node<T> *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop(T& target){
        if(isEmpty()){
            cout << "LinkedStack is empty!" << endl;
            return;
        }
        target = top->data;
        Node<T> *temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    void print() const{
        Node<T> *temp = top;
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


int main(){
    LinkedStack<int> LS1(5);
    LS1.push(1);
    LS1.push(2);
    LS1.push(3);
    LS1.push(4);
    LS1.push(5);
    LS1.print();

    LS1.push(6);

    int target;
    LS1.pop(target);
    cout<< "target = " << target <<endl;
    LS1.print();

    cout << "<< ===== LinkedStack of string ==== >>" << endl;

    LinkedStack<string> LS2(5);
    LS2.push("hello");
    LS2.push("world");
    LS2.push("LinkedStack");
    LS2.push("linked");
    LS2.push("list");
    LS2.print();

    LS2.push("overflow");

    string target2;
    LS2.pop(target2);
    cout << "target2 = " << target2 << endl;
    LS2.print();

    return 0;
}