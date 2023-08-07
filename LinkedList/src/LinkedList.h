#include <cstdint>
#include <iostream>

template <typename T>
class LinkedList
{
  struct Node
  {
    explicit Node(T valueIn)
        : value{valueIn}
    {}

    T     value;
    Node *next{nullptr};
  };

public:
  void print_list()
  {
    if (head == nullptr)
    {
      return;
    }

    Node *curr = head;
    while (curr != nullptr)
    {
      std::cout << "value: " << curr->value << ", address: " << curr << ", next: " << curr->next << std::endl;
      curr = curr->next;
    }
    std::cout << std::endl;
  }

  bool addElement(T &&value)
  {
    auto checkNewPointer = [](Node *ptr) {
      if (ptr == nullptr)
      {
        std::cout << "Error: Memory allocation failed, couldn't add element\n";
        return false;
      }
      return true;
    };

    if (head == nullptr)
    {
      head = new Node(value);
      return checkNewPointer(head) ? true : false;
    }

    Node *end = head;
    while (end->next != nullptr)
    {
      end = end->next;
    }

    end->next = new Node(value);
    return checkNewPointer(end->next) ? true : false;
  }

  /**
   * @brief Reverses the singly linked list and returns the new head
   *
   */
  bool reverseList()
  {
    if (head == nullptr || head->next == nullptr)
    {
      std::cout << "List is empty, hence cannot be reversed" << std::endl;
      return false;
    }

    Node *prev = head;
    Node *curr = head->next;
    Node *next = curr->next;

    head->next = nullptr;
    while (curr != nullptr)
    {
      // std::cout<<"Exchanginging the nodes"<<std::endl;
      Node *currNext = curr->next;
      curr->next     = prev;
      prev           = curr;
      curr           = currNext;
    }
    head = prev;
    return true;
  }

  /**
   * @brief Reverses the singly linked list and returns the new head
   *
   * @param head
   */
  bool deleteNodeGivenValue(int value)
  {
    if (head == nullptr)
    {
      std::cout << "List is empty, hence element cannot be deleted" << std::endl;
      return false;
    }

    if (head->value == value)
    {
      Node *newHead = head->next;
      free(head);
      head = newHead;
      return true;
    }

    Node *prev = head;
    Node *curr = head->next;

    while (curr != nullptr)
    {
      if (curr->value == value)
      {
        prev->next = curr->next;
        free(curr);
        return true;
      }
      prev = curr;
      curr = curr->next;
    }
    std::cout << "Element not found hence not deleted\n";
    return false;   // when element not found, hence cannot be deleted
  }

  // Bubble sort implementation
  bool sort()
  {
    if (head == nullptr || head->next == nullptr)
    {
      std::cout << "Empty list, sorting not needed\n";
      return false;
    }

    Node *curr1 = head;
    Node *curr2 = head;
    while (curr1 != nullptr)
    {
      while (curr2 != nullptr && curr2->next != nullptr)
      {
        if (curr2->value > curr2->next->value)
        {
          std::swap(curr2->value, curr2->next->value);
        }
        curr2 = curr2->next;
      }
      curr1 = curr1->next;
    }
    return false;
  }

private:
  Node *head;
};