#include<iostream>
#include "binaryTree.h"
using namespace std;


enum deleteNodeType{
    LEFT_NODE,
    RIGHT_NODE,
    ROOT_NODE
};

template <class T>
class BST : public BinaryTree<T> {
public:
    BST(T* root = nullptr) : BinaryTree<T>(root) {}
    ~BST() {}

    T* searchNode(const int& target) {
        if(this->root == nullptr) {
            std::cout << "Tree is empty!!" << std::endl;
            return nullptr;
        }
        T* curr = this->root;
        while(curr != nullptr) {
            if(curr->data == target) {
                std::cout << "the data: " << target << " has been found" << std::endl;
                return curr;
            }
            if(curr->data > target) curr = curr->left;
            else curr = curr->right;
        }
        std::cout << "searchNode(): the data: " << target << " has not been found!!" << std::endl;
        return nullptr;
    }

    void insertNode(const int& data) {
        if(this->root == nullptr){
            this->root = new T(data);
            return;
        }
        T* curr = this->root;
        T* prev = nullptr;
        while(curr != nullptr) {
            if(curr->data == data) {
                cout << "the data: " << data << " already exists!!" << endl;
                return;
            }
            prev = curr;
            if(curr->data > data) curr = curr->left;
            else curr = curr->right;
        }

        T* newNode = new T(data);
        if(prev->data > data) prev->left = newNode;
        else prev->right = newNode;

        cout << "the data: " << data << " has been inserted" << endl;
    }

    T* searchPrant(const int& target) {
        if(this->root == nullptr) {
            cout << "Tree is empty!!" << endl;
            return nullptr;
        }
        T* curr = this->root;
        T* prev = nullptr;
        while(curr != nullptr) {
            if(curr->data == target) return prev;
            prev = curr;
            if(curr->data > target) curr = curr->left;
            else curr = curr->right;
        }
        cout << "searchPrant(): the data: " << target << " has not been found!!" << endl;
        return nullptr;
    }

    void deleteNode(const int& data) {
        if(this->root == nullptr) {
            cout << "Tree is empty!!" << endl;
            return;
        }

        T* toDelete = searchNode(data);

        // 1. 未找到节点
        if(toDelete == nullptr){
            cout << "deleteNode(): the data: " << data << " has not been found!!" << endl;
            return;
        }

        // 获取父节点，并判断是被删除节点是父节点的左子节点还是右子节点
        T* parent = searchPrant(data);
        deleteNodeType toDeleteNodeType;
        if(parent == nullptr) toDeleteNodeType = ROOT_NODE;
        else if(parent->left == toDelete) toDeleteNodeType = LEFT_NODE;
        else if(parent->right == toDelete) toDeleteNodeType = RIGHT_NODE;

        // 2. 删除的是叶子节点
        if(toDelete->left == nullptr && toDelete->right == nullptr) {
            if(toDeleteNodeType == ROOT_NODE) this->root = nullptr;
            else if(toDeleteNodeType == LEFT_NODE) parent->left = nullptr;
            else parent->right = nullptr;
        }

        // 3. 删除的是只有一个子节点的节点
        else if(toDelete->left == nullptr || toDelete->right == nullptr) {
            T* child = toDelete->left ? toDelete->left : toDelete->right;
            if(toDeleteNodeType == ROOT_NODE) this->root = child;
            else if(toDeleteNodeType == LEFT_NODE) parent->left = child;
            else parent->right = child;
        }

        // 4. 删除的是有两个子节点的节点
        // 把toDelect的左子树放到toDelect的右子树的最左节点上
        // 把toDelect的父节点指向toDelect的右节点
        else {
            // 4.1 被删除节点右子树的最左边节点
            T* toDelectRightTree_left_node = toDelete->right;
            while(toDelectRightTree_left_node->left != nullptr) \
            toDelectRightTree_left_node = toDelectRightTree_left_node->left;
            
            // 4.2 被删除节点的左子树放到被删除节点的右子树的最左边节点上
            toDelectRightTree_left_node->left = toDelete->left;

            // 4.3 被删除节点的父节点指向被删除节点的右子树
            if(toDeleteNodeType == ROOT_NODE) this->root = toDelete->right;
            else if(toDeleteNodeType == LEFT_NODE) parent->left = toDelete->right;
            else parent->right = toDelete->right;
        }

        delete toDelete;
        cout << "the data: " << data << " has been deleted" << endl;
    }
};









// #include<iostream>
// #include "binaryTree.h"


// template <class T>
// class BST : public BinaryTree<T>{
// public:
//     BST(T* root = nullptr): BinaryTree<T>(root){}
//     ~BST(){}

//     void searchNode(const int &target){
//         if (this->root == nullptr){
//             std::cout << "empty tree" << std::endl;
//             return;
//         }
//         T* temp = this->root;
//         while(true){
//             if (target == temp->data){
//                 std::cout << "the data: " << target << " has been found" << std::endl;
//                 return;
//             }
//             if (target < temp->data){
//                 if (temp->left == nullptr){
//                     std::cout << "the data: " << target << " has not been found" << std::endl;
//                     return;
//                 }else temp = temp->left;
//             }
//             if (target > temp->data){
//                 if (temp->right == nullptr){
//                     std::cout << "the data: " << target << " has not been found" << std::endl;
//                     return;
//                 }else temp = temp->right;
//             }

//         }
//     }

//     void insertNode(const int &data){
//         if (this->root == nullptr){
//             std::cout << "empty tree" << std::endl;
//             return;
//         }
//         T* newNode = new T(data);
//         T* temp = this->root;
//         while(true){
//             if (data == temp->data){
//                 std::cout << "the data: " << data << " already exists" << std::endl;
//                 return;
//             }
//             if (data < temp->data){
//                 if (temp->left == nullptr){
//                     temp->left = newNode;
//                     break;
//                 }
//                 temp = temp->left;
//                 continue;
//             }
//             if (data > temp->data){
//                 if (temp->right == nullptr){
//                     temp->right = newNode;
//                     break;
//                 }
//                 temp = temp->right;
//                 continue;
//             }
//         }
//         std::cout << "the data: " << data << " has been inserted" << std::endl;
//     }

//     void deleteNode(const int &target){
//         if (this->root == nullptr){
//             std::cout << "empty tree" << std::endl;
//             return;
//         }
//         // if the root node is the target node
//         if (this->root->data == target){
//             // if the root node is a leaf node
//             if (this->root->left == nullptr && this->root->right == nullptr){
//                 delete this->root;
//                 this->root = nullptr;
//                 return;
//             }
//             // if the root node have only right child
//             if (this->root->left == nullptr){
//                 T* temp = this->root;
//                 this->root = temp->right;
//                 delete temp;
//                 temp = nullptr;
//                 return;
//             }
//             // if the root node have only left child
//             if (this->root->right == nullptr){
//                 T* temp = this->root;
//                 this->root = temp->left;
//                 delete temp;
//                 temp = nullptr;
//                 return;
//             }
//         }

//         T* temp = this->root;
//         T* parent = nullptr;
//         while(true){
//             if (target == temp->data){
//                 // if the node to be deleted is a leaf node
//                 if (temp->left == nullptr && temp->right == nullptr){
//                     if (parent->left == temp){
//                         parent->left = nullptr;
//                     }else parent->right = nullptr;
//                     delete temp;
//                     temp = nullptr;
//                     break;
//                 }
//                 // find the largest node in the left subtree
//                 if (temp->left != nullptr){
//                     T* largestNodeParent = temp;
//                     T* largestNode = temp->left;
//                     while(largestNode->right != nullptr){
//                         largestNodeParent = largestNode;
//                         largestNode = largestNode->right;
//                     }
//                     // if the largest node have a left child
//                     if (largestNode->left){
//                         // if the largest node is the left child of temp
//                         if (largestNode == temp->left){
//                             largestNodeParent->left = largestNode->left; // the largest node's left child becomes the left child of its parent
//                         }else largestNodeParent->right = largestNode->left; // if the largest node is the right child of its parent
//                     }else largestNodeParent->right = nullptr;
//                     temp->data = largestNode->data;
//                     delete largestNode;
//                     largestNode = nullptr;
//                     break;
//                 }else{
//                     if (parent->left == temp){
//                         parent->left = temp->right;
//                     }else parent->right = temp->right;
//                     delete temp;
//                     temp = nullptr;
//                 }
//             }
//             if (target < temp->data){
//                 if (temp->left == nullptr){
//                     std::cout << "data " << target <<  " not found" << std::endl;
//                     return;
//                 }else{
//                     parent = temp;
//                     temp = temp->left;
//                     continue;
//                 }
//             }
//             if (target > temp->data){
//                 if (temp->right == nullptr){
//                     std::cout << "data " << target <<  " not found" << std::endl;
//                     return;
//                 }else{
//                     parent = temp;
//                     temp = temp->right;
//                     continue;
//                 }
//             }
//         }
//         std::cout << "the data:" << target << " has been deleted" << std::endl;
//     }
// };