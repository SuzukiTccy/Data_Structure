#include<iostream>
using namespace std;

template <class T>
struct Node{
    T data;
    Node<T>* next;
    Node(T data, Node<T>* next = nullptr):data(data), next(next){}
};


template <class T>
class Queue{
private:
    Node<T>* front;
    Node<T>* rear;
    size_t size;
    size_t capacity;

public:
    Queue(size_t capacity):front(nullptr), rear(nullptr), size(0), capacity(capacity){}
    ~Queue(){
        while(front){
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        cout << "Queue release!" << endl;
    }

    bool isFull(){
        return size == capacity;
    }

    bool isEmpty(){
        return size == 0;
    }

    void enqueue(const T& data){
        if(isFull()){
            cout << "Queue is full!" << endl;
            return;
        }
        if(isEmpty()){
            front = rear = new Node<T>(data, nullptr);
            size++;
            return;
        }
        rear->next = new Node<T>(data, nullptr);
        rear = rear->next;
        size++;
    }

    T dequeue(){
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            return T();
        }
        T data = front->data;
        Node<T>* temp = front;
        front = front->next;
        delete temp;
        size--;
        return data;
    }

    T peek(){
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            return T();
        }
        cout << front->data << endl;
        return front->data;
    }

    void print(){
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            return;
        }
        Node<T>* temp = front;
        while(temp){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main(){
    Queue<int> q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.print(); // 1 2 3 4 5

    q.enqueue(6); // Queue is full!
    q.print(); // 1 2 3 4 5

    int target = q.dequeue();
    cout << "target = " << target << endl; // target = 1
    q.print(); // 2 3 4 5

    cout << "q.peek()" << endl;
    q.peek(); // 2

    q.enqueue(6);
    q.print(); // 2 3 4 5 6
    
    cout << "<< ===== Queueu of string ==== >>" << endl;
    Queue<string> q2(3);
    q2.enqueue("Hello");
    q2.enqueue("World");
    q2.enqueue("!");
    q2.print(); // Hello World !

    q2.enqueue("Hi"); // Queue is full!
    q2.print(); // Hello World !

    string target2 = q2.dequeue();
    cout << "target2 = " << target2 << endl; // target2 = Hello
    q2.print(); // World !

    cout << "q2.peek()" << endl;
    q2.peek(); // World

    q2.enqueue("Good");
    q2.enqueue("Bye"); // Queue is full!
    q2.print(); // World ! Good

    return 0;
}