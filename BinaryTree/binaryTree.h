#include<algorithm>
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<iomanip>

struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data): data(data), left(nullptr), right(nullptr){}
};

template<class T>
class BinaryTree{
public:
    T* root;
public:
    BinaryTree(T* root = nullptr):root(root){};
    virtual ~BinaryTree(){
        if (root == nullptr) return;
        std::queue<T*> q;
        q.push(root);
        T* temp = nullptr;
        while(!q.empty()){
            temp = q.front();
            q.pop();
            if (temp->right != nullptr) q.push(temp->right);
            if (temp->left != nullptr) q.push(temp->left);
            delete temp;
        }
    }

    virtual void searchNode(const int& target){};
    virtual void insertNode(const int& data){};
    virtual void deleteNode(const int& data){};

    unsigned int treeHeight(T* node){
        if (node == nullptr) return -1;
        // int _height = std::max(treeHeight(node->left), treeHeight(node->right)) + 1;  // 无法得到正确高度 原因未知
        int _lheight = treeHeight(node->left);
        int _rheight = treeHeight(node->right);
        return (_lheight > _rheight) ? _lheight + 1 : _rheight + 1;
    }

    unsigned int treeHeight(){
        return treeHeight(this->root);
    }

    void LevelOrderTraversal(T* root){
        if (root == nullptr) return;
        std::queue<T*> q;
        T* temp = nullptr;
        while(!q.empty()){
            temp = q.front();
            q.pop();
            std::cout << temp->data << " ";
            if (temp->right != nullptr) q.push(temp->right);
            if (temp->left != nullptr) q.push(temp->left);
        }
    }

    void LevelOrderTraversal(){
        LevelOrderTraversal(this->root);
    }

    void PreOrderTraversal(T* root){
        if (root == nullptr) return;
        std::stack<T*> s;
        s.push(root);
        T* temp = nullptr;
        while(!s.empty()){
            temp = s.top();
            s.pop();
            std::cout << temp->data << " ";
            if (temp->right != nullptr) s.push(temp->right);
            if (temp->left != nullptr) s.push(temp->left);
        }
    }

    void PreOrderTraversal(){
        PreOrderTraversal(this->root);
    }

    void InOrderTraversal(T* root){
        if (root == nullptr) return;
        std::stack<T*> s;
        T* temp = root;
        while(temp != nullptr || !s.empty()){
            while(temp != nullptr){
                // 1. push all the left nodes
                s.push(temp);
                temp = temp->left;
            }

            // 2. pop the top node and print it
            temp = s.top();
            s.pop();
            std::cout << temp->data << " ";

            // 3. go to the right node, the node temp does not have left child, and it is the parent of the right node
            temp = temp->right;
        }
    }

    void InOrderTraversal(){
        InOrderTraversal(this->root);
    }

    void PostOrderTraversal(T* root){
        if (root == nullptr) return;
        if (root->left != nullptr) PostOrderTraversal(root->left);
        if (root->right != nullptr) PostOrderTraversal(root->right);
        std::cout << root->data << " ";
    }

    void PostOrderTraversal(){
        PostOrderTraversal(this->root);
    }

    void PrintTree(T* root){
        if (root == nullptr) return;
        unsigned int height = treeHeight() + 1;

        unsigned int level = 0; // current level
        std::queue<T*> q;
        q.push(root);
        T* temp = nullptr;
        unsigned int count = 0; // number of nodes in the current level
        unsigned int space_between = 0; // number of spaces between nodes in the current level
        unsigned int space_before = 0; // number of spaces before the current node in the current level
        // std::vector<T*> vec; // store the nodes in the current level
        while(!q.empty() && level < height){
            ++level;
            count = q.size();
            // vec.clear();

            space_before = (unsigned int)pow(2, height - level) - 1;
            space_between = (unsigned int)pow(2, height - level + 1) - 1;

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
            // space_between = (unsigned int)pow(2, height - level) - 2;
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
        PrintTree(this->root); // overload, use the root node of the tree
    }
};