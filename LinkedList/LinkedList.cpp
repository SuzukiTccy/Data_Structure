#include<iostream>
using namespace std;

template <class T>
struct LinkedListNode {
    T data;
    LinkedListNode<T>* next;
    LinkedListNode(T data, LinkedListNode<T>* next = nullptr):data(data), next(next){}
};

template <class T>
class LinkedList {
private:
    LinkedListNode<T>* sentinel; // Sentinel Node 

public:
    LinkedList(){
        sentinel = new LinkedListNode<T>(0, nullptr);
    }
    ~LinkedList(){
        LinkedListNode<T>* temp = sentinel;
        while(temp != nullptr){
            sentinel = sentinel->next;
            delete temp;
            temp = sentinel;
        }
        cout << "LinkedList release!" << endl;
    }
    bool isEmpty(){
        return sentinel->next == nullptr;
    }

    void insertAtHead(const T& data){
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data, sentinel->next);
        sentinel->next = newNode;
    }

    void insertAtTail(const T& data){
        if(isEmpty()){
            insertAtHead(data);
            return;
        }
        LinkedListNode<T>* temp = sentinel->next;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = new LinkedListNode<T>(data, nullptr);
    }

    // Insert at the pos position in the linked list, pos start from 0, no include the sentinel node
    void insertAtPos(const T& data, const int& pos){
        if(pos < 0){
            cout << "Invalid position" << endl;
            return;
        }
        int cur = -1; // -1 because we are starting from sentinel node
        LinkedListNode<T>* temp = sentinel;
        while(temp != nullptr && cur != pos - 1){
            temp = temp->next;
            cur++;
        }
        if(cur < pos - 1){ // if position is greater than length of list
            cout << "Invalid position" << endl;
            return;
        }
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data, temp->next);
        temp->next = newNode;
    }

    // delete the node at the pos position in the linked list, pos start from 0
    void deleteAtPos(const int& pos){
        if(pos < 0){
            cout << "Invalid position" << endl;
            return;
        }
        int cur = -1; // -1 because we are starting from sentinel node
        LinkedListNode<T>* temp = sentinel;
        while(temp != nullptr && cur != pos - 1){
            temp = temp->next;
            cur++;
        }
        if(cur < pos - 2){ // if position is greater than length of list
            cout << "Invalid position" << endl;
            return;
        }
        LinkedListNode<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }

    void deleteNodesWithVal(const T& data){
        LinkedListNode<T>* temp = sentinel;
        while(temp->next != nullptr && temp->next->data != data){
            temp = temp->next;
       }
       if(temp->next == nullptr){
           cout << "No nodes with value " << data << " found" << endl;
           return;
       }
       LinkedListNode<T>* toDelete = temp->next;
       temp->next = toDelete->next;
       delete toDelete;

       cout << "delete the first node with the given data: " << data << endl;
    }

    void reverseLinkedList(){
        LinkedListNode<T>* prev = nullptr;
        LinkedListNode<T>* curr = sentinel->next;
        LinkedListNode<T>* next = nullptr;
        while(curr != nullptr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        sentinel->next = prev;
    }

    void printList(){
        LinkedListNode<T>* temp = sentinel->next;
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main(){
    LinkedList<int> LKlist;
    LKlist.insertAtHead(1);
    LKlist.insertAtHead(2);
    LKlist.insertAtHead(3);
    LKlist.insertAtHead(4);
    LKlist.insertAtHead(5);

    cout << "LKlist.printList()" << endl;
    LKlist.printList();

    cout << "LKlist.insertAtTail(6)" << endl;
    LKlist.insertAtTail(6);
    LKlist.printList();

    cout << "LKlist.insertAtHead(0)" << endl;
    LKlist.insertAtHead(0);
    LKlist.printList();

    cout << "LKlist.insertAtPos(6, 2)" << endl;
    LKlist.insertAtPos(6, 2);
    LKlist.printList();

    cout << "LKlist.insertAtPos(7, 10)" << endl;
    LKlist.insertAtPos(7, 10); // except print "Invalid position"
    LKlist.printList();

    cout << "LKlist.deleteNodesWithVal(10)" << endl;
    LKlist.deleteNodesWithVal(10); // except print "The node with the given data does not exist"

    cout << "LKlist.deleteNodesWithVal(6)" << endl;
    LKlist.deleteNodesWithVal(6);
    LKlist.printList();


    cout << "LKlist.deleteAtPos(4)" << endl;
    LKlist.deleteAtPos(4);
    LKlist.printList();

    cout << "LKlist.reverseLinkedList()" << endl;
    LKlist.reverseLinkedList();
    LKlist.printList();

}
