#include<iostream>
#include "binaryTree.h"


template <class T>
class BST : public BinaryTree<T>{
public:
    BST(T* root = nullptr): BinaryTree<T>(root){}
    ~BST(){}

    void searchNode(const int &target){
        if (this->root == nullptr){
            std::cout << "empty tree" << std::endl;
            return;
        }
        T* temp = this->root;
        while(true){
            if (target == temp->data){
                std::cout << "the data: " << target << " has been found" << std::endl;
                return;
            }
            if (target < temp->data){
                if (temp->left == nullptr){
                    std::cout << "the data: " << target << " has not been found" << std::endl;
                    return;
                }else temp = temp->left;
            }
            if (target > temp->data){
                if (temp->right == nullptr){
                    std::cout << "the data: " << target << " has not been found" << std::endl;
                    return;
                }else temp = temp->right;
            }

        }
    }

    void insertNode(const int &data){
        if (this->root == nullptr){
            std::cout << "empty tree" << std::endl;
            return;
        }
        T* newNode = new T(data);
        T* temp = this->root;
        while(true){
            if (data == temp->data){
                std::cout << "the data: " << data << " already exists" << std::endl;
                return;
            }
            if (data < temp->data){
                if (temp->left == nullptr){
                    temp->left = newNode;
                    break;
                }
                temp = temp->left;
                continue;
            }
            if (data > temp->data){
                if (temp->right == nullptr){
                    temp->right = newNode;
                    break;
                }
                temp = temp->right;
                continue;
            }
        }
        std::cout << "the data: " << data << " has been inserted" << std::endl;
    }

    void deleteNode(const int &target){
        if (this->root == nullptr){
            std::cout << "empty tree" << std::endl;
            return;
        }
        // if the root node is the target node
        if (this->root->data == target){
            // if the root node is a leaf node
            if (this->root->left == nullptr && this->root->right == nullptr){
                delete this->root;
                this->root = nullptr;
                return;
            }
            // if the root node have only right child
            if (this->root->left == nullptr){
                T* temp = this->root;
                this->root = temp->right;
                delete temp;
                temp = nullptr;
                return;
            }
            // if the root node have only left child
            if (this->root->right == nullptr){
                T* temp = this->root;
                this->root = temp->left;
                delete temp;
                temp = nullptr;
                return;
            }
        }

        T* temp = this->root;
        T* parent = nullptr;
        while(true){
            if (target == temp->data){
                // if the node to be deleted is a leaf node
                if (temp->left == nullptr && temp->right == nullptr){
                    if (parent->left == temp){
                        parent->left = nullptr;
                    }else parent->right = nullptr;
                    delete temp;
                    temp = nullptr;
                    break;
                }
                // find the largest node in the left subtree
                if (temp->left != nullptr){
                    T* largestNodeParent = temp;
                    T* largestNode = temp->left;
                    while(largestNode->right != nullptr){
                        largestNodeParent = largestNode;
                        largestNode = largestNode->right;
                    }
                    // if the largest node have a left child
                    if (largestNode->left){
                        // if the largest node is the left child of temp
                        if (largestNode == temp->left){
                            largestNodeParent->left = largestNode->left; // the largest node's left child becomes the left child of its parent
                        }else largestNodeParent->right = largestNode->left; // if the largest node is the right child of its parent
                    }else largestNodeParent->right = nullptr;
                    temp->data = largestNode->data;
                    delete largestNode;
                    largestNode = nullptr;
                    break;
                }else{
                    if (parent->left == temp){
                        parent->left = temp->right;
                    }else parent->right = temp->right;
                    delete temp;
                    temp = nullptr;
                }
            }
            if (target < temp->data){
                if (temp->left == nullptr){
                    std::cout << "data " << target <<  " not found" << std::endl;
                    return;
                }else{
                    parent = temp;
                    temp = temp->left;
                    continue;
                }
            }
            if (target > temp->data){
                if (temp->right == nullptr){
                    std::cout << "data " << target <<  " not found" << std::endl;
                    return;
                }else{
                    parent = temp;
                    temp = temp->right;
                    continue;
                }
            }
        }
        std::cout << "the data:" << target << " has been deleted" << std::endl;
    }
};