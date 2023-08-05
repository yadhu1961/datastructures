#include <iomanip>
#include <iostream>
#include <memory>

template <typename T>
class BinaryTree
{
  struct Node
  {
    Node(const T& info)
        : data{info}
    {}
    T     data;
    Node* left{nullptr};
    Node* right{nullptr};
  };

public:
  bool addNode(const T& data)
  {
    if (root == nullptr)
    {
      root = new Node(data);
      return true;
    }

    return addNodeImpl(data, *root);
  }

  bool removeNode(const T& data) {}

  bool searchNode(const T& data) const {}

  void printTree() const
  {
    if (root == nullptr)
    {
      std::cout << "Tree empty\n";
      return;
    }

    printTreeImpl(root);
  }

  void visualPrint()
  {
    displayImpl(root, 0);
    std::cout << "\n\n";
  }

  std::size_t size() const {}

  std::size_t getTreeHeight() const
  {
    if (root == nullptr)
    {
      return 0;
    }

    return std::max(getTreeHeightImpl(root->left), getTreeHeightImpl(root->right));
  }

  std::size_t nodeLevel() const {}

private:
  void visualPrintImpl(Node* p, int indent = 0)
  {
    if (p != NULL)
    {
      if (p->left)
        visualPrintImpl(p->left, indent + 4);
      if (p->right)
        visualPrintImpl(p->right, indent + 4);
      if (indent)
      {
        std::cout << std::setw(indent) << ' ';
      }
      std::cout << p->data << "\n ";
    }
  }

  void displayImpl(Node* node, int level)
  {
    int i;
    if (node != NULL)
    {
      displayImpl(node->right, level + 1);
      std::cout << std::endl;
      // if (node == root)
      //   std::cout << "Root -> ";
      for (i = 0; i < level && node != root; i++)
        std::cout << "   ";
      std::cout << node->data;
      displayImpl(node->left, level + 1);
    }
  }

  bool addNodeImpl(const T& data, Node& node)
  {
    if (node.left == nullptr)
    {
      node.left = new Node(data);
      return true;
    }

    if (node.right == nullptr)
    {
      node.right = new Node(data);
      return true;
    }

    Node* leftNode  = node.left;
    Node* rightNode = node.right;

    Node* nextNode = leftNode->left != nullptr && leftNode->right != nullptr ? leftNode : rightNode;

    addNodeImpl(data, *(nextNode));
  }

  void printTreeImpl(Node* node) const
  {
    if (node == nullptr)
    {
      return;
    }

    std::cout << "address: " << node << ", data: " << node->data << std::endl;
    if (node->left != nullptr)
    {
      printTreeImpl(node->left);
    }

    if (node->right != nullptr)
    {
      printTreeImpl(node->right);
    }
  }

  size_t getTreeHeightImpl(Node* node) const
  {
    if (node == nullptr)
    {
      return 0;
    }

    return std::max(1 + getTreeHeightImpl(node->left), 1 + getTreeHeightImpl(node->right));

    // if (node->left != nullptr || node->right != nullptr)
    // {
    //   ++level;
    // }

    // getTreeHeightImpl(node->left);
    // getTreeHeightImpl(node->right);

    // return level;
  }

  Node* root{nullptr};
};