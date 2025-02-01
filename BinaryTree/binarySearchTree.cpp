#include<iostream>
#include "binaryTree.cpp"

class BST : public BinaryTree{
public:
    BST(TreeNode* root = nullptr): BinaryTree(root){}
    ~BST(){}

    void searchNode(const int &target){
        if (this->root == nullptr){
            std::cout << "empty tree" << std::endl;
            return;
        }
        TreeNode* temp = this->root;
        while(true){
            if (target == temp->data){
                std::cout << "the data:" << target << "has been found" << std::endl;
                return;
            }
            if (target < temp->data){
                if (temp->left == nullptr){
                    std::cout << "the data:" << target << "has not been found" << std::endl;
                    return;
                }else temp = temp->left;
            }else if (target > temp->data){
                if (temp->right == nullptr){
                    std::cout << "the data:" << target << "has not been found" << std::endl;
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
        TreeNode* newNode = new TreeNode(data);
        TreeNode* temp = this->root;
        while(true){
            if (data == temp->data){
                std::cout << "data already exists" << std::endl;
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

        TreeNode* temp = this->root;
        TreeNode* parent = nullptr;
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
                    TreeNode* largestNodeParent = temp;
                    TreeNode* largestNode = temp->left;
                    while(largestNode->right != nullptr){
                        largestNodeParent = largestNode;
                        largestNode = largestNode->right;
                    }
                    if (largestNode->left){
                        if (largestNodeParent->left == largestNode){
                            largestNodeParent->left = largestNode->left;
                        }else largestNodeParent->right = largestNode->left;
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

int main(){
    BST tree(new TreeNode(10));
    tree.insertNode(5);
    tree.insertNode(15);
    tree.insertNode(3);
    tree.insertNode(7);
    tree.insertNode(12);
    tree.insertNode(17);
    tree.insertNode(1);
    tree.insertNode(4);
    tree.insertNode(6);
    tree.insertNode(8);
    tree.insertNode(11);
    tree.insertNode(20);

    tree.PrintTree();

    tree.searchNode(10);
    tree.searchNode(20);
    tree.searchNode(12);
    tree.searchNode(18);

    tree.deleteNode(10);
    tree.PrintTree();

    tree.deleteNode(15);
    tree.PrintTree();

    tree.deleteNode(15);
    tree.PrintTree();

    tree.deleteNode(4);
    tree.PrintTree();

    tree.deleteNode(20);
    tree.PrintTree();

    tree.deleteNode(8);
    tree.PrintTree();

    tree.insertNode(20);
    tree.PrintTree();

    tree.insertNode(9);
    tree.PrintTree();


}