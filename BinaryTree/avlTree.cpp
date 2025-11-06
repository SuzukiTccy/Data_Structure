#include "avlTree.h"



int main() {
    avlTree tree(new avlNode(10));
    tree.insertNode(11);
    tree.PrintTree();

    tree.insertNode(12);
    tree.PrintTree();

    tree.insertNode(12);
    tree.PrintTree();

    tree.insertNode(8);
    tree.PrintTree();

    tree.insertNode(9);
    tree.PrintTree();

    tree.insertNode(4);
    tree.PrintTree();

    tree.insertNode(6);
    tree.PrintTree();
    
    tree.insertNode(7);
    tree.PrintTree();

    tree.deleteNode(4);
    tree.PrintTree();
    tree.insertNode(14);
    tree.PrintTree();
    tree.insertNode(13);
    tree.PrintTree();

    tree.searchNode(14);
    tree.searchNode(10);
    tree.searchNode(100);
    tree.searchNode(4);
    return 0;
}