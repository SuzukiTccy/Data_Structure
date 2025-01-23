#include<algorithm>
#include<iostream>
#include<queue>
#include<stack>

struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data): data(data), left(nullptr), right(nullptr){}
};


class BinaryTree{
private:
    TreeNode* root;
    int nodeCount;
public:
    BinaryTree(): root(nullptr), nodeCount(0){};
    virtual ~BinaryTree(){
        if (root == nullptr) return;
        std::queue<TreeNode*> q;
        q.push(root);
        TreeNode* temp = nullptr;
        while(!q.empty()){
            temp = q.front();
            q.pop();
            if (temp->right != nullptr) q.push(temp->right);
            if (temp->left != nullptr) q.push(temp->left);
            delete temp;
        }
    }

    virtual void insert(int data){};
    virtual void deleteNode(int data){};

    unsigned int treeHeight(TreeNode* root){
        if (root == nullptr) return 0;
        return std::max(treeHeight(root->left), treeHeight(root->right)) + 1;
    }

    void LevelOrderTraversal(TreeNode* root){
        if (root == nullptr) return;
        std::queue<TreeNode*> q;
        q.push(root);
        TreeNode* temp = nullptr;
        while(!q.empty()){
            temp = q.front();
            q.pop();
            std::cout << temp->data << " ";
            if (temp->right != nullptr) q.push(temp->right);
            if (temp->left != nullptr) q.push(temp->left);
        }
    }

    void PreOrderTraversal(TreeNode* root){
        if (root == nullptr) return;
        std::stack<TreeNode*> s;
        s.push(root);
        TreeNode* temp = nullptr;
        while(!s.empty()){
            temp = s.top();
            s.pop();
            std::cout << temp->data << " ";
            if (temp->right != nullptr) s.push(temp->right);
            if (temp->left != nullptr) s.push(temp->left);
        }
    }

    void InOrderTraversal(TreeNode* root){
        if (root == nullptr) return;
        std::stack<TreeNode*> s;
        TreeNode* temp = root;
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

            // 3. go to the right node
            temp = temp->right;
        }
    }

    void PostOrderTraversal(TreeNode* root){
        if (root == nullptr) return;
        if (root->left != nullptr) PostOrderTraversal(root->left);
        if (root->right != nullptr) PostOrderTraversal(root->right);
        std::cout << root->data << " ";
    }

};
