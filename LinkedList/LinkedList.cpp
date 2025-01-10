#include<iostream>
using namespace std;

template <class T>
struct LinkedList
{
    T data;
    LinkedList<T>* next;
};

template <class T>
class LinkedListClass{
private:
    LinkedList<T>* head; // Sentinel Node 
public:
    LinkedListClass(){
        head = new LinkedList<T>;
        head->next = nullptr;
    }
    ~LinkedListClass(){
        LinkedList<T>* temp = head;
        while(temp){
            head = head->next;
            delete temp;
            temp = head;
        }
    }
    void InsertAtHead(const T& data){

        LinkedList<T>* temp = new LinkedList<T>;
        temp->data = data;
        temp->next = head->next;
        head->next = temp;
    }

    void InsertAtTail(const T& data){
        if (!head->next){
            InsertAtHead(data);
            return;
        }
        LinkedList<T>* temp = head;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = new LinkedList<T>;
        temp->next->data = data;
    }

    // Insert at the pos position in the linked list, pos start from 0, no include the sentinel node
    void InsertAtPosition(const T& data, const int& pos){
        if (pos < 0){
            cout << " Invalid position " << endl;
            return;
        }
        int i = -1; // i is the position of the current node
        LinkedList<T>* temp = head;
        while(temp->next && i != pos - 1){ // i > 1 because we need to insert at the pos position, so we need to find the position before pos
            temp = temp->next;
            i++;
        }
        if (i < pos - 1){
            cout << " Invalid position " << endl;
            return;
        }
        LinkedList<T>* newNode = new LinkedList<T>;
        newNode->data = data;
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // delete the node at the pos position in the linked list, pos start from 0
    void DeleteAtPosition(const int& pos){
        if (pos < 0){
            cout << " Invalid position " << endl;
            return;
        }
        if (!head->next){
            cout << " The linked list is empty " << endl;
            return;
        }
        int i = -1; // i is the position of the current node
        LinkedList<T>* temp = head;
        while(temp->next && i != pos - 1){ // i > 1 because we need to delete at the pos position, so we need to find the position before pos
            temp = temp->next;
            i++;
        }
        if (i < pos - 1){ // if the position is greater than the length of the linked list or the position is the last node
            cout << " Invalid position " << endl;
            return;
        }
        LinkedList<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }

    // delete the first node with the given data in the linked list
    void DeleteNodeWithValue(const T& target){
        if (!head->next){
            cout << " The linked list is empty " << endl;
            return;
        }
        LinkedList<T>* temp = head;
        while(temp->next && temp->next->data != target){
            temp = temp->next;
        }
        if (!temp->next){
            cout << " The node with the given data does not exist " << endl;
            return;
        }

        LinkedList<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;

        cout << "delete the first node with the given data: " << target << endl;

    }

    void ReverseList(){
        if (!head->next) return;
        LinkedList<T>* prev = nullptr;
        LinkedList<T>* curr = head->next;
        LinkedList<T>* next = nullptr;
        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head->next = prev; // update the head->next to the last node
    }

    void PrintList(){
        LinkedList<T>* temp = head->next;
        while(temp){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

};

int main(){
    LinkedListClass<int> LKlist;
    LKlist.InsertAtHead(1);
    LKlist.InsertAtHead(2);
    LKlist.InsertAtHead(3);
    LKlist.InsertAtHead(4);
    LKlist.InsertAtHead(5);
    LKlist.PrintList();

    cout << "LKlist.InsertAtTail(6)" << endl;
    LKlist.InsertAtTail(6);
    LKlist.PrintList();

    cout << "LKlist.InsertAtHead(0)" << endl;
    LKlist.InsertAtHead(0);
    LKlist.PrintList();

    cout << "LKlist.InsertAtPosition(6, 2)" << endl;
    LKlist.InsertAtPosition(6, 2);
    LKlist.PrintList();

    cout << "LKlist.InsertAtPosition(7, 10)" << endl;
    LKlist.InsertAtPosition(7, 10); // except print "Invalid position"
    LKlist.PrintList();

    cout << "LKlist.DeleteNodeWithValue(10)" << endl;
    LKlist.DeleteNodeWithValue(10); // except print "The node with the given data does not exist"

    cout << "LKlist.DeleteNodeWithValue(6)" << endl;
    LKlist.DeleteNodeWithValue(6);
    LKlist.PrintList();


    cout << "LKlist.DeleteAtPosition(4)" << endl;
    LKlist.DeleteAtPosition(4);
    LKlist.PrintList();

    cout << "LKlist.ReverseList()" << endl;
    LKlist.ReverseList();
    LKlist.PrintList();

}
