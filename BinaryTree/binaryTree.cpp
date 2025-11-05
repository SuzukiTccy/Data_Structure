#include "binaryTree.h"

int main(){
    BinaryTree<TreeNode> tree(new TreeNode(10));
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

    tree.levelOrder();
    cout << endl;

    tree.preOrder();
    cout << endl;

    tree.inOrder();
    cout << endl;
    
    tree.postOrder();
}