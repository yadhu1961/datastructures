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

    return addNodeImpl(data, root);
  }

  bool removeNode(const T& data) { return false; }

  bool searchNode(const T& data) const { return searchNodeImpl(data, root); }

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

  std::size_t size() const { return -1; }

  std::size_t getTreeHeight() const
  {
    if (root == nullptr)
    {
      return 0;
    }

    return std::max(getTreeHeightImpl(root->left), getTreeHeightImpl(root->right));
  }

  std::size_t nodeLevel() const { return -1; }

  ~BinaryTree()
  {
    if (root == nullptr)
    {
      return;
    }
    clearTree(root);
  }

private:
  void clearTree(Node* node)
  {
    if (node == nullptr)
      return;

    if (node->right == nullptr && node->left == nullptr)
    {
      std::cout << "Freeing leaf node, address " << node << ", data: " << node->data << std::endl;
      delete node;
    }
    else
    {
      clearTree(node->right);
      clearTree(node->left);
      std::cout << "Freeing parent node, address " << node << ", data: " << node->data << std::endl;
      delete node;
    }
  }

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
      for (i = 0; i < level && node != root; i++)
        std::cout << "   ";
      std::cout << node->data;
      displayImpl(node->left, level + 1);
    }
  }

  bool addNodeImpl(const T& data, Node* node)
  {
    if (data <= node->data)
    {
      if (node->left == nullptr)
      {
        node->left = new Node(data);
        return true;
      }
      else
      {
        return addNodeImpl(data, node->left);
      }
    }
    else
    {
      if (node->right == nullptr)
      {
        node->right = new Node(data);
        return true;
      }
      else
      {
        return addNodeImpl(data, node->right);
      }
    }
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

  bool searchNodeImpl(T data, Node* node) const
  {
    if (node == nullptr)
    {
      return false;
    }

    if (node->data == data)
    {
      std::cout << "Found at address: " << node << std::endl;
      return true;
    }

    if (data < node->data)
    {
      return searchNodeImpl(data, node->left);
    }
    else
    {
      return searchNodeImpl(data, node->right);
    }
  }

  size_t getTreeHeightImpl(Node* node) const
  {
    if (node == nullptr)
    {
      return 0;
    }

    return std::max(1 + getTreeHeightImpl(node->left), 1 + getTreeHeightImpl(node->right));
  }

  Node* root{nullptr};
};