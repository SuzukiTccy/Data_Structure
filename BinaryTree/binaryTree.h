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

            // 3. go to the right node, the node temp does not have left child, and it is the parent of the right node
            temp = temp->right;
        }
    }

    void PostOrderTraversal(TreeNode* root){
        if (root == nullptr) return;
        if (root->left != nullptr) PostOrderTraversal(root->left);
        if (root->right != nullptr) PostOrderTraversal(root->right);
        std::cout << root->data << " ";
    }

    void PrintTree(TreeNode* root){
        if (root == nullptr) return;
        unsigned int height = treeHeight(root);

        unsigned int level = 0; // current level
        std::queue<TreeNode*> q;
        q.push(root);
        TreeNode* temp = nullptr;
        unsigned int count = 0; // number of nodes in the current level
        unsigned int space_between = 0; // number of spaces between nodes in the current level
        unsigned int space_before = 0; // number of spaces before the current node in the current level
        std::vector<TreeNode*> vec; // store the nodes in the current level
        while(!q.empty() && level < height){
            ++level;
            count = q.size();
            vec.clear();

            space_before = (unsigned int)pow(2, height - level) - 1;
            space_between = (unsigned int)pow(2, height - level + 1) - 1;

            std::cout << std::string(space_before * 2, ' ');
            while(count--){
                temp = q.front();
                q.pop();
                vec.push_back(temp);

                if (temp){
                    std::cout << std::setw(2) << temp->data;
                    q.push(temp->left);
                    q.push(temp->right);
                }else std::cout << "  ";

                if (count > 0) std::cout << std::string(space_between * 2, ' ');
            }
            std::cout << std::endl << std::endl;

            // 每一层左右连接线之前的宽度，是下一层节点之间宽度减去2
            // 每一层连接线的前置空格，是父节点前置空格减1
            // space_between = (unsigned int)pow(2, height - level) - 2;
            // if (level < height){
            //     std::cout << std::string(space_before * 2 - 1, ' '); // print the spaces before the first node in the next level
            //     for(TreeNode* node : vec){
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
};


int main(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    BinaryTree{}.PrintTree(root);
}