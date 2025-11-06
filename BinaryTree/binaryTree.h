#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<iomanip>
using namespace std;

//二叉树
struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* l = nullptr, TreeNode* r = nullptr):data(x), left(nullptr), right(nullptr){}
};

template <class T>
class BinaryTree{
public:
    T* root;
    BinaryTree(T* root = nullptr):root(root){}
    virtual ~BinaryTree() noexcept{
        if(root == nullptr) return;
        queue<T*> q;
        q.push(root);
        T* cur = nullptr;
        while(!q.empty()){
            cur = q.front();
            q.pop();
            if(cur->left != nullptr) q.push(cur->left);
            if(cur->right != nullptr) q.push(cur->right);
            delete cur;
        }
        cout << "BinaryTree release!" << endl;
    }

    void searchNode(const int& target){};
    void insertNode(const int& data){};
    void deleteNode(const int& target){};

    //节点高度
    int nodeHeight(const T* node){
        if(node == nullptr) return -1;
        int leftheight = nodeHeight(node->left);
        int rightheight = nodeHeight(node->right);
        return leftheight > rightheight ? leftheight + 1: rightheight + 1;
    }

    // 树高度
    int treeHeight(){
        return nodeHeight(this->root);
    }

    // 层序遍历
    void levelOrder(T* root){
        if(root == nullptr) return;
        queue<T*> q;
        q.push(root);
        T* cur = nullptr;
        while(!q.empty()){
            cur = q.front();
            q.pop();
            cout << cur->data << " ";
            if(cur->left != nullptr) q.push(cur->left);
            if(cur->right != nullptr) q.push(cur->right);
        }
        cout << endl;
    }

    void levelOrder(){
        levelOrder(this->root);
    }


    // 前序遍历
    void preOrder(T* root){
        if(root == nullptr) return;
        stack<T*> s;
        s.push(root);
        T* cur = nullptr;
        while(!s.empty()){
            cur = s.top();
            s.pop();
            cout << cur->data << " ";
            if(cur->right != nullptr) s.push(cur->right);
            if(cur->left != nullptr) s.push(cur->left);
        }
        cout << endl;
    }

    void preOrder(){
        preOrder(this->root);
    }


    // 中序遍历
    void inOrder(T* root){
        if(root == nullptr) return;
        stack<T*> s;
        T* cur = root;
        while(cur != nullptr || !s.empty()){
            // 1. push all left node
            while(cur != nullptr){
                s.push(cur);
                cur = cur->left;
            }

            // 2. pop and print
            cur = s.top();
            s.pop();
            cout << cur->data << " ";

            // 3. turn to right node
            // In this part, the cur dont have left node
            cur = cur->right;
        }
        cout << endl;
    }

    void inOrder(){
        inOrder(this->root);
    }


    // 后序遍历
    void postOrder(T* root){
        if(root == nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }

    void postOrder(){
        postOrder(this->root);
        cout << endl;
    }


    void PrintTree(T* root){
        if (root == nullptr) return;
        size_t height = treeHeight() + 1;

        size_t level = 0; // current level
        std::queue<T*> q;
        q.push(root);
        T* temp = nullptr;
        size_t count = 0; // number of nodes in the current level
        size_t space_between = 0; // number of spaces between nodes in the current level
        size_t space_before = 0; // number of spaces before the current node in the current level
        // std::vector<T*> vec; // store the nodes in the current level
        while(!q.empty() && level < height){
            ++level;
            count = q.size();
            // vec.clear();

            space_before = (size_t)pow(2, height - level) - 1;
            space_between = (size_t)pow(2, height - level + 1) - 1;

            std::cout << std::string(space_before * 2, ' ');
            while(count--){
                temp = q.front();
                q.pop();
                // vec.push_back(temp);

                if (temp){
                    std::cout << std::setw(2) << temp->data;
                    q.push(temp->left);
                    q.push(temp->right);
                }
                else{
                    std::cout << "  ";
                    q.push(nullptr);
                    q.push(nullptr);
                }

                if (count > 0) std::cout << std::string(space_between * 2, ' ');
            }
            std::cout << std::endl << std::endl;

            // 每一层左右连接线之前的宽度，是下一层节点之间宽度减去2
            // 每一层连接线的前置空格，是父节点前置空格减1
            // space_between = (size_t)pow(2, height - level) - 2;
            // if (level < height){
            //     std::cout << std::string(space_before * 2 - 1, ' '); // print the spaces before the first node in the next level
            //     for(T* node : vec){
            //         if (node){
            //             std::cout << std::setw(2) << (node->left ? "/" : " ");
            //             std::cout << std::string((space_between * 2 - 2), ' ');
            //             std::cout << (node->right ? "\\" : " ");
            //         }else{
            //             std::cout << "  "; // Placeholding
            //             std::cout << std::string((space_between * 2 - 2), ' ');
            //             std::cout << "  "; // Placeholding
            //         }
            //     }
            //     std::cout << std::endl;
            // }
        }
    }

    void PrintTree(){
        PrintTree(this->root);
    }

};