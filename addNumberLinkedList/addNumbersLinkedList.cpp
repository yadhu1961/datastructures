// C++ program to add two numbers
// represented by linked list
#include <iostream>

using namespace std;

/* Linked list node */
class Node
{
public:
  int   data;
  Node* next;
};

/* Function to create a
new node with given data */
Node* newNode(int data)
{
  Node* new_node = new Node();
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

/* Function to insert a node at the
beginning of the Singly Linked List */
void push(Node** head_ref, int new_data)
{
  /* allocate node */
  Node* new_node = newNode(new_data);

  /* link the old list off the new node */
  new_node->next = (*head_ref);

  /* move the head to point to the new node */
  (*head_ref) = new_node;
}

/* Adds contents of two linked lists and
return the head node of resultant list */
Node* addTwoLists(Node* first, Node* second)
{
  Node*   firstListEle  = first;
  Node*   secondListEle = second;
  Node*   result        = nullptr;
  uint8_t carry         = 0;
  while (firstListEle != nullptr || secondListEle != nullptr)
  {
    int firstListData  = firstListEle != nullptr ? firstListEle->data : 0;
    int secondListData = secondListEle != nullptr ? secondListEle->data : 0;
    int sum            = firstListData + secondListData + carry;
    push(&result, sum % 10);
    carry         = sum / 10;
    firstListEle  = firstListEle != nullptr ? firstListEle->next : nullptr;
    secondListEle = secondListEle != nullptr ? secondListEle->next : nullptr;
  }

  if (carry)
  {
    push(&result, carry);
  }

  return result;
}

Node* reverse(Node* head)
{
  if (head == NULL || head->next == NULL)
    return head;

  /* reverse the rest list and put
    the first element at the end */
  Node* rest       = reverse(head->next);
  head->next->next = head;

  head->next = NULL;

  /* fix the head pointer */
  return rest;
}

// A utility function to print a linked list
void printList(Node* node)
{
  while (node != NULL)
  {
    cout << node->data << " ";
    node = node->next;
  }
  cout << endl;
}

/* Driver code */
int main(void)
{
  Node* res    = NULL;
  Node* first  = NULL;
  Node* second = NULL;

  // create first list 7->5->9->4->6
  push(&first, 6);
  push(&first, 4);
  push(&first, 9);
  push(&first, 5);
  push(&first, 7);
  printf("First List is ");
  printList(first);

  // create second list 8->4
  push(&second, 4);
  push(&second, 8);
  cout << "Second List is ";
  printList(second);

  // reverse both the lists
  first  = reverse(first);
  second = reverse(second);
  // printList(first);
  // printList(second);
  // Add the two lists
  res = addTwoLists(first, second);

  // reverse the res to get the sum
  res = reverse(res);
  cout << "Resultant list is ";
  printList(res);

  return 0;
}
