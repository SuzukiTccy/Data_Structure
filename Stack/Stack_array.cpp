#include<iostream>
using namespace std;

template <class T>
class Stack{
private:
    T *arr;
    int top;
    size_t size;
    size_t capacity;
public:
    Stack(size_t capacity): top(0), size(0), capacity(capacity){
        arr = new T[capacity];
    }
    ~Stack(){
        delete[] arr;
    }

    bool isEmpty(){
        return size == 0;
    }

    bool isFull(){
        return size == capacity;
    }

    void push(const T& data){
        if(isFull()){
            cout << "Stack is full" << endl;
            return;
        }
        if(isEmpty()){
            arr[top] = data;
            size++;
            return;
        }
        top++;
        arr[top] = data;
        size++;
    }

    void pop(T& target){
        if(isEmpty()){
            cout << "Stack is empty" << endl;
            return;
        }
        target = arr[top];
        top--;
        size--;
    }
    void print(){
        for(int i = size - 1; i >= 0; i--){
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    Stack<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.print();

    s.push(6); // Stack is full

    int target;
    s.pop(target);
    cout << "target = " << target << endl;
    s.print();

    cout << "<< ===== Stack of string ==== >>" << endl;

    Stack<string> s2(5);
    s2.push("Hello");
    s2.push("World");
    s2.push("Stack");
    s2.push("Array");
    s2.push("Example");
    s2.print();

    s2.push("Test"); // Stack is full

    string target2;
    s2.pop(target2);
    cout << "target2 = " << target2 << endl;
    s2.print();

    return 0;

}