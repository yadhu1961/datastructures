#include <iostream>
#include "BinaryTree.h"

int main()
{
  BinaryTree<int> binaryTree;

  binaryTree.addNode(10);
  binaryTree.addNode(11);
  binaryTree.addNode(12);
  binaryTree.addNode(13);
  binaryTree.addNode(14);
  binaryTree.addNode(15);
  binaryTree.addNode(16);
  binaryTree.addNode(17);
  binaryTree.addNode(18);
  binaryTree.addNode(19);
  binaryTree.addNode(20);
  binaryTree.addNode(21);
  binaryTree.addNode(22);
  binaryTree.addNode(23);
  binaryTree.addNode(24);
  binaryTree.addNode(25);

  binaryTree.printTree();

  std::cout << "Tree height: " << binaryTree.getTreeHeight() << std::endl;

  binaryTree.visualPrint();

  return 0;
}