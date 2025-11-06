#include "binarySearchTree.h"

int main(){
    BST<TreeNode> tree(new TreeNode(10));
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

    // 删除根节点
    tree.deleteNode(10);
    tree.PrintTree();

    // 删除根节点
    tree.deleteNode(15);
    tree.PrintTree();

    // 删除不存在的节点
    tree.deleteNode(15);
    tree.PrintTree();

    // 删除右叶子节点
    tree.deleteNode(4);
    tree.PrintTree();

    // 删除左叶子节点
    tree.deleteNode(6);
    tree.PrintTree();

    // 删除只有左子树的节点
    tree.deleteNode(3);
    tree.PrintTree();

    // 删除只有左子树的节点
    tree.deleteNode(7);
    tree.PrintTree();

    // 插入已有节点
    tree.insertNode(20);
    tree.PrintTree();

    // 插入没有的节点
    tree.insertNode(9);
    tree.PrintTree();
}