#include <iostream>
#include <optional>

template <typename T>
class Queue
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
  bool isEmpty() const { return m_rear == nullptr && m_front == nullptr; }

  std::optional<T> front() const
  {
    if (isEmpty())
    {
      return std::nullopt;
    }
    return m_front->data;
  }

  bool enque(T&& x)
  {
    Node* newNode = new Node(x);
    if (newNode == nullptr)
    {
      std::cout << "enqueuing failed\n";
      return false;
    }

    if (m_rear == nullptr && m_front == nullptr)
    {
      m_rear = m_front = newNode;
    }
    else
    {
      m_rear->next = newNode;
      m_rear       = newNode;
    }
    return true;
  }

  bool dequeue()
  {
    if (isEmpty())
    {
      std::cout << "dequeing failed, queue empty\n";
      return false;
    }
    Node* temp = m_front;
    m_front    = m_front->next;
    delete temp;   // free the memory
    return true;
  }

  void printQueue() const
  {
    if (isEmpty())
    {
      std::cout << "queue empty\n";
      return;
    }

    std::cout << "Queue from front to tail\n";

    Node* curr = m_front;
    // Free all the memory allocated for the queue
    while (curr != nullptr)
    {
      std::cout << "address: " << curr << ", "
                << "data: " << curr->data << std::endl;
      curr = curr->next;
    }
  }

  ~Queue()
  {
    // Free all the memory allocated for the queue
    while (m_front != nullptr)
    {
      Node* temp = m_front;
      m_front    = m_front->next;
      delete temp;
    }
  }

private:
  Node* m_rear{nullptr};    // tail of a linked list inserting in tail, removing in head
  Node* m_front{nullptr};   // head of a linked list
};