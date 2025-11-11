#include<iostream>
using namespace std;


/*
    * 哈希表
    * 哈希函数：key % capacity
    * 冲突解决：链表
*/

struct Node{
    int key;
    int value;
    Node* next;

    Node(int key, int value, Node* next): key(key), value(value), next(next){};
};


class ChainedHashMap{
private:
    size_t size; // number of elements
    size_t capacity; // number of buckets
    float load_factor_threshold = 2.0 / 3.0; // size / capacity
    int extendRatio = 2; // ratio to extend capacity
    Node** table; // array of buckets
    typedef size_t (*HASH_FUNC)(size_t, int); // hash function type
    HASH_FUNC hashFunction; // hash function

public:
    ChainedHashMap(size_t capacity, HASH_FUNC hashFunction): size(0), capacity(capacity), \
    hashFunction(hashFunction){
        table = new Node*[capacity];
        for(int i = 0; i < capacity; i++) table[i] = nullptr;
    }
    
    ~ChainedHashMap(){
        for(int i = 0; i < capacity; i++){
            Node* node = table[i];
            while(node != nullptr){
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] table;
    }

    int search(int key){
        size_t hash_value = hashFunction(capacity, key);
        Node* node = table[hash_value];
        while(node != nullptr){
            if (node->key == key){
                cout << "key:" << key << " " << "value:" << node->value << endl;
                return node->value;
            }
            node = node->next;
        }
        cout << "Key not found" << endl;
        return -INT64_MAX;
    }

    void insert(int key, int value){
        if(search(key) == value){
            cout << "Key already exists" << endl;
            return;
        }
        size_t hash_value = hashFunction(capacity, key);
        if(table[hash_value] == nullptr) table[hash_value] = new Node(key, value, nullptr);
        else{
            Node* node = table[hash_value];
            while(node->next != nullptr) node = node->next;
            node->next = new Node(key, value, nullptr);
        }
        size++;
        extendMap();
    }

/**
 * 扩展哈希表容量的函数
 * 当当前负载因子超过阈值时，创建一个新的更大的哈希表，
 * 并将所有元素从旧表重新哈希到新表中
 */
    void extendMap(){
    // 计算当前负载因子（元素数量与容量的比值）
        float load_factor = static_cast<float>(size) / capacity;
        if(load_factor < load_factor_threshold) return;

        size_t new_capacity = capacity * extendRatio;
        Node** new_table = new Node*[new_capacity];
        for(int i = 0; i < new_capacity; i++) new_table[i] = nullptr;

        for(int i = 0; i < capacity; i++){
            Node* node = table[i];
            while(node != nullptr){
                size_t hash_value = hashFunction(new_capacity, node->key);
                if(new_table[hash_value] == nullptr) new_table[hash_value] = new Node(node->key, node->value, nullptr);
                else{
                    Node* new_node = new_table[hash_value];
                    while(new_node->next != nullptr) new_node = new_node->next;
                    new_node->next = new Node(node->key, node->value, nullptr);
                }
                node = node->next;
            }
        }

        delete[] table;
        table = new_table;
        capacity = new_capacity;
        cout << "size:" << size << " new capacity:" << capacity << endl;
    }

    void remove(int key){
        size_t hash_value = hashFunction(capacity, key);
        Node* node = table[hash_value];
        Node* prev = nullptr;
        while(node != nullptr){
            if(node->key == key){
                if(prev == nullptr) table[hash_value] = node->next; // 代表着要删除的是第一个节点
                else prev->next = node->next; // 代表着要删除的是中间或者最后节点

                delete node;
                size--;
                cout << "key:" << key << " removed" << endl;
                return;      
            }
            prev = node;
            node = node->next;
        }
        cout << "Key not found" << endl;
    }

    void print(){
        for(int i = 0; i < capacity; i++){
            Node* node = table[i];
            while(node != nullptr){
                cout << "(" <<node->key << ", " << node->value << ")" << "\t";
                node = node->next;
            }
            cout << endl;
        }
    }
};

size_t hashFunction(size_t capacity, int key){
    return key % capacity;
};


int main(){
    size_t capacity = 10;
    size_t (*hashFunc)(size_t, int) = hashFunction;
    ChainedHashMap map(capacity, hashFunc);
    cout << "map.insert()" << endl;
    map.insert(1, 1);
    map.insert(2, 2);
    map.insert(3, 3);
    map.insert(10, 10);
    map.insert(13, 13);
    map.print();

    cout << endl;
    cout << "map.search(13)" << endl;
    map.search(13);

    cout << "map.remove(2)" << endl;
    map.remove(2);
    map.print();
    cout << "map.remove(5)" << endl;
    map.remove(5);

    cout << "map.search(3)" << endl;
    map.search(3);

    map.insert(4, 5);
    map.insert(5, 6);
    map.insert(6, 7);
    map.insert(7, 8);
    map.insert(8, 9);
    map.print();

    cout << "map.extendMap()" << endl;
    map.extendMap();
    map.print();

    return 0;

}