#include<iostream>
#include<algorithm>
#include<stack>
#include "binarySearchTree.h"
using namespace std;


struct avlNode{
    int data;
    avlNode *left;
    avlNode *right;
    int height;  // -1 decleared as nullptr
    explicit avlNode(int data):data(data),left(nullptr),right(nullptr),height(0) {};
};


class avlTree: public BST<avlNode> {
public:
    avlTree(avlNode *root = nullptr):BST<avlNode>(root) {}
    ~avlTree(){}

    int get_tree_height() const{
        if (this->root == nullptr) return -1;
        return root->height;
    }

    int update_node_height(avlNode* node) {
        if (node == nullptr) return -1;
        node->height = max(update_node_height(node->left), update_node_height(node->right)) + 1;
        return node->height;
    }
    
    int update_tree_height() {
        return update_node_height(this->root);
    }

    int get_balance_factor(avlNode *node) {
        if (node == nullptr) return -1;
        int left_height  = node->left != nullptr ? node->left->height : -1;
        int right_height = node->right != nullptr ? node->right->height : -1;
        return left_height - right_height;
    }

    // 右旋组件
    avlNode *rotate_right(avlNode *node, avlNode *parent = nullptr) {
        if (node == nullptr) return nullptr;
        avlNode *child = node->left;
        avlNode *grand_child = child->right;

        // 以 child 为圆心，将 node 向右旋转
        node->left = grand_child;
        child->right = node;

        if (node == root) root = child;

        if (parent != nullptr){
            if (parent->left == node) parent->left = child;
            else parent->right = child;
        }

        return child; // 返回旋转后的根节点
    }

    // 左旋组件
    // TODO: 旋转后，node的父节点的右子节点也需要更换
    avlNode *rotate_left(avlNode *node, avlNode *parent = nullptr){
        avlNode *child = node->right;
        avlNode *grand_child = child->left;

        // 以 child 为圆心，将 node 向左旋转
        node->right = grand_child;
        child->left = node;

        if (node == root) root = child;

        if (parent != nullptr){
            if (parent->left == node) parent->left = child;
            else parent->right = child;
        }

        return child; // 返回旋转后的根节点
    }

    // 左右旋组建件
    avlNode *rotate_left_right(avlNode *node, avlNode *parent){
        if (node == nullptr) return nullptr;
        avlNode *child = node->left;
        rotate_left(child, node);
        rotate_right(node, parent);
        return child;
    }

    // 右左旋组建件
    avlNode *rotate_right_left(avlNode *node, avlNode *parent){
        if (node == nullptr) return nullptr;
        avlNode *child = node->right;
        rotate_right(child, node);
        rotate_left(node, parent);
        return child;
    }

    // rotate the unbalanced node
    avlNode* rotate(avlNode *node, avlNode *parent) {
        if (node == nullptr) return nullptr;
        int balance_factor = get_balance_factor(node);
        if (balance_factor > 1) {
            if (get_balance_factor(node->left) >= 0) {
                rotate_right(node, parent);
            }else{
                rotate_left_right(node, parent);
            }
            return node->left;
        }
        if (balance_factor < -1) {
            if (get_balance_factor(node->right) <= 0) {
                rotate_left(node, parent);
            }else{
                rotate_right_left(node, parent);
            }
            return node->right;
        }
        return node;
    }

    // check and rotate the whole tree
    avlNode* check_and_rotate(stack<avlNode*> &s) {
        avlNode *node = nullptr;
        avlNode *parent = nullptr;
        avlNode *temp = nullptr;
        while(!s.empty()){
            node = s.top();
            s.pop();
            temp = node;
            parent = s.empty() ? nullptr : s.top();
            node = rotate(node, parent); // s.top() is the parent of node
            if (node != temp) break;
        }
        update_tree_height();
        return node;
    }


    void insertNode(const int &data){
        if (this->root == nullptr){
            cout << "empty tree" << endl;
            return;
        }
        stack<avlNode*> s;
        s.push(this->root);
        avlNode* newNode = new avlNode(data);
        avlNode* temp = this->root;
        while(true){
            if (data == temp->data){
                cout << "the data: " << data << " already exists" << endl;
                return;
            }
            if (data < temp->data){
                if (temp->left == nullptr){
                    temp->left = newNode;
                    break;
                }
                temp = temp->left;
            }else{
                if (temp->right == nullptr){
                    temp->right = newNode;
                    break;
                }
                temp = temp->right;
            }
            s.push(temp);
        }
        cout << "the data: " << data << " has been inserted" << endl;
        update_tree_height();
        check_and_rotate(s);
    }

    void deleteNode(const int &target){
        if (this->root == nullptr){
            cout << "empty tree" << endl;
            return;
        }
        stack<avlNode*> s;
        s.push(this->root);
        avlNode* temp = this->root;
        avlNode* parent = nullptr;
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
                    avlNode* largestNodeParent = temp;
                    avlNode* largestNode = temp->left;
                    s.push(largestNode);
                    while(largestNode->right != nullptr){
                        largestNodeParent = largestNode;
                        largestNode = largestNode->right;
                        s.push(largestNode);
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
                    break;
                }
            }
            if (target < temp->data){
                if (temp->left == nullptr){
                    cout << "data " << target <<  " not found" << endl;
                    return;
                }else{
                    parent = temp;
                    temp = temp->left;
                }
            }else{
                if (temp->right == nullptr){
                    cout << "data " << target <<  " not found" << endl;
                    return;
                }else{
                    parent = temp;
                    temp = temp->right;
                }
            }
            s.push(temp);
        }
        cout << "the data:" << target << " has been deleted" << endl;
        update_tree_height();
        check_and_rotate(s);
    }
};



