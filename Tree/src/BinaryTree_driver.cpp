#include <iostream>
#include "BinaryTree.h"

int main()
{
  BinaryTree<int> binaryTree;

  binaryTree.addNode(10);
  binaryTree.addNode(1);
  binaryTree.addNode(20);
  binaryTree.addNode(2);
  binaryTree.addNode(14);
  binaryTree.addNode(0);
  binaryTree.addNode(30);
  binaryTree.addNode(3);
  binaryTree.addNode(13);
  binaryTree.addNode(-1);
  binaryTree.addNode(20);
  binaryTree.addNode(4);
  binaryTree.addNode(22);
  binaryTree.addNode(-2);
  binaryTree.addNode(24);
  binaryTree.addNode(3);

  binaryTree.printTree();

  std::cout << "Tree height: " << binaryTree.getTreeHeight() << std::endl;

  binaryTree.visualPrint();

  int searchValue = 24;
  std::cout << "Searching for value: " << searchValue << std::endl;
  binaryTree.searchNode(24);

  return 0;
}