#include<iostream>
using namespace std;

template <class T>
struct Node{
    T data;
    Node<T>* next = nullptr;
};

template <class T>
class Queue{
private:
    Node<T>* front;
    Node<T>* rear;
    size_t capacity;
    size_t size;
public:
    Queue(size_t capacity):front(nullptr), rear(nullptr), capacity(capacity), size(0){}
    ~Queue(){
        while(front){
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isFull(){
        if (size == capacity) return true;
        return false;
    }

    bool isEmpty(){
        if (size == 0) return true;
        return false;
    }

    void enqueue(const T& data){
        if(isFull()){
            cout << "Queue is full" << endl;
            return;
        }
        Node<T>* temp = new Node<T>;
        temp->data = data;
        if(isEmpty()){
            front = temp;
            rear = temp;
            size++;
            return;
        }
        rear->next = temp;
        rear = temp;
        size++;
    }

    void dequeue(T& target){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            target = T(); // set target to default value
            return;
        }
        target = front->data;
        Node<T>* temp = front;
        front = front->next;
        delete temp;
        size--;
    }

    void peek(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return;
        }
        cout << front->data << endl;
    }

    void print(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
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
    q.print();

    q.enqueue(6);
    q.print();

    int target;
    q.dequeue(target);
    cout << "target = " << target << endl;
    q.print();
    q.peek();

    q.enqueue(6);
    q.print();
    
    cout << "<< ===== Queueu of string ==== >>" << endl;
    Queue<string> q2(3);
    q2.enqueue("Hello");
    q2.enqueue("World");
    q2.enqueue("!");
    q2.print();

    q2.enqueue("Hi");
    q2.print();

    string target2;
    q2.dequeue(target2);
    cout << "target2 = " << target2 << endl;
    q2.print();
    q2.peek();

    q2.enqueue("Good");
    q2.enqueue("Bye");
    q2.print();

    return 0;
}