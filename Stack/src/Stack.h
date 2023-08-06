#include <iostream>
#include <optional>

template <typename T>
class Stack
{
private:
  // struct for storing the data and links
  struct Node
  {
    Node()
        : data(0)
        , next(nullptr)
    {}

    Node(T x)
        : data(x)
        , next(nullptr)
    {}
    Node(T x, Node* next)
        : data(x)
        , next(next)
    {}

    T     data;
    Node* next;
  };

public:
  bool isEmpty() const { return m_top == nullptr; }

  std::optional<T> top() const
  {
    if (isEmpty())
    {
      return std::nullopt;
    }
    return m_top->data;
  }

  bool push(T&& x)
  {
    Node* newNode = new Node(x);
    if (newNode == nullptr)
    {
      std::cout << "push failed\n";
      return false;
    }

    if (m_top == nullptr)
    {
      m_top = newNode;
    }
    else
    {
      newNode->next = m_top;
      m_top         = newNode;
    }
    return true;
  }

  bool pop()
  {
    if (isEmpty())
    {
      std::cout << "pop failed, stack empty\n";
      return false;
    }
    Node* temp = m_top;
    m_top      = m_top->next;
    delete temp;   // free the memory
    return true;
  }

  void printStack() const
  {
    if (isEmpty())
    {
      std::cout << "stack empty\n";
      return;
    }

    std::cout << "Stack from top to bottom\n";

    Node* curr = m_top;
    // Free all the memory allocated for the queue
    while (curr != nullptr)
    {
      std::cout << "address: " << curr << ", "
                << "data: " << curr->data << std::endl;
      curr = curr->next;
    }
  }

  ~Stack()
  {
    // Free all the memory allocated for the queue
    while (m_top != nullptr)
    {
      Node* temp = m_top;
      m_top      = m_top->next;
      delete temp;
    }
  }

private:
  Node* m_top{nullptr};   // head of a linked list
};