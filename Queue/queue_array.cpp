#include<iostream>
using namespace std;


template <class T>
class Queue{
private:
    T *array;
    int front;
    int rear; // points to the last element in the queue
    int capacity; // size of the array
    int size;

public:
    Queue(size_t capacity): front(0), rear(0), size(0), capacity(capacity){
        if(capacity < 1){
            throw "Invalid capacity";
        }
        array = new T[capacity];
    }

    ~Queue(){
        delete[] array;
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
        if (isFull()){
            cout << "Queue is full" << endl;
            return;
        }
        if (isEmpty()){
            array[front] = data;
            size++;
            return;
        }
        rear = (rear + 1) % capacity;
        array[rear] = data;
        size++;
    }

    void dequeue(T& target){
        if (isEmpty()){
            cout << "Queue is empty" << endl;
            return;
        }
        target = array[front];
        front = (front + 1) % capacity;
        size--;
    }

    bool peek(T& target){
        if (isEmpty()){
            cout << "Queue is empty" << endl;
            target = T();
            return false;
        }
        target = array[front];
        return true;
    }

    void print(){
        if (isEmpty()){
            cout << "Queue is empty" << endl;
            return;
        }
        for (int i = 0; i < size; ++i){
            cout << array[(front + i) % capacity] << " ";
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

    target = 6;
    q.enqueue(target);
    q.print();

    cout << "<< ========Queue of strings======== >>" << endl;
    Queue<string> q2(5);
    q2.enqueue("Hello");
    q2.enqueue("World");
    q2.enqueue("!");
    q2.print();

    string target2;
    q2.dequeue(target2);
    cout << "target2 = " << target2 << endl;
    q2.print();

    target2 = "Hello";
    q2.enqueue(target2);
    q2.print();
}