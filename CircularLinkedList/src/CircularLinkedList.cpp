#include <iostream>

struct Node
{
  explicit Node(int valueIn)
      : value{valueIn}
  {}

  int   value;
  Node* next{nullptr};
};

void printList(Node* node)
{
  std::cout << "The circular list contains\n";
  if (node == nullptr)
    return;

  // Single node case
  if (node->next == node)
  {
    std::cout << "Node = ( value : " << node->value << ", next: " << node->next << ")" << std::endl << std::endl;
    return;
  }

  Node* firstNode = node;
  Node* curr      = node;
  while (1)
  {
    std::cout << "Node = ( value : " << curr->value << ", next: " << curr->next << ")" << std::endl;
    if (curr->next == firstNode)
      break;
    curr = curr->next;
  }

  std::cout << std::endl;
}

int addNode(Node** head, int value)
{
  Node* newNode = new Node(value);

  if (newNode == nullptr)   // when allocation failed
    return -1;

  if ((*head) == nullptr)
  {
    *head         = newNode;
    (*head)->next = *head;
    return 0;
  }

  newNode->next = (*head)->next;
  (*head)->next = newNode;
  return 0;
}

int main()
{
  Node* circularListAcs = nullptr;
  addNode(&circularListAcs, 5);
  printList(circularListAcs);
  addNode(&circularListAcs, 6);
  printList(circularListAcs);
  addNode(&circularListAcs, 7);
  printList(circularListAcs);

  return 0;
}