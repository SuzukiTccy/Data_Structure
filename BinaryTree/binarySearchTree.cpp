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