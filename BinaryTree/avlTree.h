#include<iostream>
#include<stack>
#include "binarySearchTree.h"
using namespace std;


struct avlNode{
    int data;
    avlNode* left;
    avlNode* right;
    int height;
    avlNode(int data, avlNode* left = nullptr, avlNode* right = nullptr, int height = 0)
    :data(data), left(left), right(right), height(height){}
};


class avlTree : public BST<avlNode>{
public:
    avlTree(avlNode* root = nullptr): BST<avlNode>(root){};
    ~avlTree(){};

    int treeHeight() const{
        if(this->root == nullptr) return -1;
        return this->root->height;
    }

    // 更新节点的高度
    int _updateNodeHeight(avlNode* node){
        if(node == nullptr) return -1;
        int leftHeight = _updateNodeHeight(node->left);
        int rightHeight = _updateNodeHeight(node->right);
        node->height = max(leftHeight, rightHeight) + 1;
        return node->height;
    }

    // 更新树的高度
    int _updateAllNodeHeight(){
        _updateNodeHeight(this->root);
        return this->root->height;
    }

    // 获取节点的平衡因子
    int _getBalanceFactor(avlNode* node){
        if(node == nullptr){
            cerr << "getBalanceFactor(): node is nullptr!!" << endl;
            return 0; 
        }
        if(node->left == nullptr && node->right == nullptr) return 0;
        if(node->left == nullptr) return -(node->right->height + 1);
        if(node->right == nullptr) return node->left->height + 1;
        return node->left->height - node->right->height;
    }

    // 右旋, 用于解决左左失衡
    // @param: 
    //      node : 失衡节点
    //      parent : 失衡节点的父节点
    // @return: 旋转后子树的根节点
    avlNode* _rightRotate(avlNode* node, avlNode* parent){
        if(node == nullptr){
            cerr << "rightRotate(): node is nullptr!!" << endl;
            return nullptr;
        }
        avlNode* leftchild = node->left;
        avlNode* grandrightchild = leftchild->right;

        leftchild->right = node;
        node->left = grandrightchild;
        
        // 根节点，意味着parent == nullptr
        if(node == this->root){
            this->root = leftchild;
            return this->root;
        }

        // 更新父节点的指针
        if(parent->left == node) parent->left = leftchild;
        else parent->right = leftchild;

        _updateAllNodeHeight();
        return leftchild;
    }

    // 左旋, 用于解决右右失衡
    // @param: 
    //      node : 失衡节点
    //      parent : 失衡节点的父节点
    // @return: 旋转后子树的根节点
    avlNode* _leftRotate(avlNode* node, avlNode* parent){
        if(node == nullptr){
            cerr << "leftRotate(): node is nullptr!!" << endl;
            return nullptr;
        }
        avlNode* rightchild = node->right;
        avlNode* grandleftchild = rightchild->left;

        rightchild->left = node;
        node->right = grandleftchild;

        // 根节点，意味着parent == nullptr
        if(node == this->root){
            this->root = rightchild;
            return this->root;
        }
        
        // 更新父节点的指针
        if(parent->left == node) parent->left = rightchild;
        else parent->right = rightchild;
        
        _updateAllNodeHeight();
        return rightchild;
    }

    // 左右旋, 用于解决左右失衡
    // @param: 
    //      node : 失衡节点
    //      parent : 失衡节点的父节点
    // @return: 旋转后子树的根节点
    avlNode* _leftRightRotate(avlNode* node, avlNode* parent){
        if(node == nullptr){
            cerr << "leftRightRotate(): node is nullptr!!" << endl;
            return nullptr;
        }
        avlNode* leftchild = node->left;

        _leftRotate(leftchild, node);
        _rightRotate(node, parent);

        _updateAllNodeHeight();
        return leftchild;
    }

    // 右左旋, 用于解决右左失衡
    // @param: 
    //      node : 失衡节点
    //      parent : 失衡节点的父节点
    // @return: 旋转后的子树的根节点
    avlNode* _rightLeftRotate(avlNode* node, avlNode* parent){
        if(node == nullptr){
            cerr << "rightLeftRotate(): node is nullptr!!" << endl;
            return nullptr;
        }
        avlNode* rightchild = node->right;

        _rightRotate(rightchild, node);
        _leftRotate(node, parent);
        
        _updateAllNodeHeight();
        return rightchild;
    }

    // 平衡节点
    // @param: 
    //      node : 需要平衡的节点
    //      parent : 需要平衡的节点的父节点
    // @return: 旋转后的根节点
    avlNode* rebalanceNode(avlNode* node, avlNode* parent){
        if(node == nullptr){
            cerr << "rebalanceNode(): node is nullptr!!" << endl;
            return nullptr;
        }
        int balanceFactor = _getBalanceFactor(node);
        if(balanceFactor > 1){
            if(_getBalanceFactor(node->left) > 0) return _rightRotate(node, parent); // 左左失衡, 右旋
            else return _leftRightRotate(node, parent); // 左右失衡, 左右旋
        }
        else if(balanceFactor < -1){
            if(_getBalanceFactor(node->right) < 0) return _leftRotate(node, parent); // 右右失衡, 左旋
            else return _rightLeftRotate(node, parent); // 右左失衡, 右左旋
        }
        return node;
    }

    // 平衡树
    //1. 在插入或删除节点时，记录从根节点的父节点到该节点的路径（例如用栈保存）
    //2. 然后从该节点开始向上回溯（即从栈中弹出节点），对每个节点检查平衡因子，并进行旋转调整
    //3. 旋转可能会改变树的结构，因此需要更新父节点的指针
    avlNode* rebalanceTree(stack<avlNode*> &s){
        avlNode* node = nullptr;
        avlNode* parent = nullptr;
        avlNode* newroot = nullptr;
        while(!s.empty()){
            node = s.top();
            s.pop();
            parent = s.empty() ? nullptr : s.top(); // 栈顶元素为空，说明node为根节点
            newroot = rebalanceNode(node, parent);
            if(newroot != node) break; // 如果旋转改变了树的结构，则更新根节点
        }
        return newroot;
    }

    void insertNode(const int& target){
        stack<avlNode*> s = BST<avlNode>::insertNode(target);
        _updateAllNodeHeight();
        rebalanceTree(s);
    }

    // 找到节点，并该节点到根节点的路径保存到栈中
    // 栈顶元素为找到的节点，栈底元素为根节点
    stack<avlNode*> _searchNode(const int& target){
        if(this->root == nullptr) {
            cerr << "searchNode(): tree is empty!!" << endl;
            return stack<avlNode*>();
        }
        avlNode* curr = this->root;
        stack<avlNode*> s;
        while(curr != nullptr){
            s.push(curr);
            if(curr->data == target){
                cout << "searchNode(): the data: " << target << " has been found!!" << endl;
                return s;
            }
            curr = curr->data > target ? curr->left : curr->right;
        }

        cout << "searchNode(): the data: " << target << " has not been found!!" << endl;
        return stack<avlNode*>();
    }

    void deleteNode(const int& data) {
        if(this->root == nullptr) {
            cout << "Tree is empty!!" << endl;
            return;
        }

        stack<avlNode*> s_toDelete = _searchNode(data);

        avlNode* toDelete = s_toDelete.top();
        // 1. 未找到节点
        if(toDelete == nullptr){
            cout << "deleteNode(): the data: " << data << " has not been found!!" << endl;
            return;
        }

        // 获取父节点，并判断是被删除节点是父节点的左子节点还是右子节点
        avlNode* parent = searchPrant(data);
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
            avlNode* child = toDelete->left ? toDelete->left : toDelete->right;
            if(toDeleteNodeType == ROOT_NODE) this->root = child;
            else if(toDeleteNodeType == LEFT_NODE) parent->left = child;
            else parent->right = child;
        }

        // 4. 删除的是有两个子节点的节点
        // 把toDelect的左子树放到toDelect的右子树的最左节点上
        // 把toDelect的父节点指向toDelect的右节点
        else {
            // 4.1 找到被删除节点右子树的最左边节点
            avlNode* toDelectRightTree_left_node = toDelete->right;
            while(toDelectRightTree_left_node->left != nullptr) \
            toDelectRightTree_left_node = toDelectRightTree_left_node->left;
            
            // 4.2 把被删除节点的左子树放到被删除节点的右子树的最左边节点上
            toDelectRightTree_left_node->left = toDelete->left;

            // 4.3 被删除节点的父节点指向被删除节点的右子树
            if(toDeleteNodeType == ROOT_NODE) this->root = toDelete->right;
            else if(toDeleteNodeType == LEFT_NODE) parent->left = toDelete->right;
            else parent->right = toDelete->right;
        }

        delete toDelete;
        cout << "the data: " << data << " has been deleted" << endl;
        rebalanceTree(s_toDelete);
    }
};


