#include<iostream>
using namespace std;


template <class T>
class Queue{
private:
    T *arr;
    size_t front;
    size_t rear;
    size_t size;
    size_t capacity;

public:
    Queue(size_t capacity):front(0), rear(0), size(0), capacity(capacity){
        arr = new T[capacity];
    }

    ~Queue(){
        delete [] arr;
    }

    bool isFull(){
        return size == capacity;
    }

    bool isEmpty(){
        return size == 0;
    }

    void enqueue(const T& data){
        if(isFull()){
            cout << "Queue is full! " << endl;
            return;
        }
        if(isEmpty()){
            arr[front] = data;
            size++;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = data;
        size++;
    }
    T dequeue(){
        if(isEmpty()){
            cout << "Queue is empty! " << endl;
            return T();
        }
        size--;
        T data = arr[front];
        front = (front + 1) % capacity;
        return data;
    }

    T peek(){
        if(isEmpty()){
            cout << "Queue is empty! " << endl;
            return T();
        }
        return arr[front];
    }

    void print(){
        if(isEmpty()){
            cout << "Queue is empty! " << endl;
            return;
        }
        for(int i = 0; i < size; i++){
            cout << arr[(front + i) % capacity] << " ";
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

    target = 6;
    q.enqueue(target);
    q.print(); // 2 3 4 5 6
    
    cout << endl;

    cout << "<< ========Queue of strings======== >>" << endl;
    Queue<string> q2(5);
    q2.enqueue("Hello");
    q2.enqueue("World");
    q2.enqueue("!");
    q2.print(); // Hello World !

    string target2 = q2.dequeue();
    cout << "target2 = " << target2 << endl; // target2 = Hello
    q2.print(); // World !

    target2 = "Hello";
    q2.enqueue(target2);
    q2.print(); // World ! Hello
}