#include <iostream>
#include <map>

struct Node
{
  Node* next;
  Node* prev;
  int   value;
  int   key;
  Node(Node* p, Node* n, int k, int val)
      : prev(p)
      , next(n)
      , key(k)
      , value(val){};
  Node(int k, int val)
      : prev(NULL)
      , next(NULL)
      , key(k)
      , value(val){};
};

class Cache
{
protected:
  std::map<int, Node*> mp;                  // map the key to the node in the linked list
  int                  cp;                  // capacity
  Node*                tail;                // double linked list tail pointer
  Node*                head;                // double linked list head pointer
  virtual void         set(int, int) = 0;   // set function
  virtual int          get(int)      = 0;   // get function
};

class LRUCache : public Cache
{
public:
  LRUCache(const int capacity)
  {
    // std:cout<<"Setting capacity: "<<capacity<<std::endl;
    cp   = capacity;
    tail = nullptr;
    head = nullptr;
  }

  void printList(const bool dumpMap = false)
  {
    std::cout << "Dumping cache: " << std::endl;
    std::cout << "head: " << head << std::endl;
    Node* curr = head;
    while (curr != nullptr)
    {
      std::cout << "key: " << curr->key << ", val: " << curr->value << ", curr:" << curr << ", curr->next: " << curr->next
                << ", curr->prev: " << curr->prev << std::endl;
      curr = curr->next;
    }
    std::cout << "tail: " << tail << std::endl;
    if (dumpMap)
    {
      std::cout << "Dumping map:\n";
      for (const auto& element : mp)
      {
        std::cout << "key: " << element.first << ", value: " << element.second->value << ", addr:" << element.second
                  << ", next: " << element.second->next << ", prev: " << element.second->prev << std::endl;
        curr = curr->next;
      }
    }
  }

  virtual void set(int key, int value) override final
  {
    if (cp <= 0)
    {
      return;
    }

    auto result = mp.find(key);
    if (result == mp.end())
    {
      if (cp == mp.size())
      {
        // Remove the tail element to make space for new element;
        if (tail != nullptr)
        {
          mp.erase(tail->key);
        }
        Node* tailPrev = tail->prev;
        if (tailPrev != nullptr)
        {
          tailPrev->next = nullptr;
        }
        if (head == tail)
        {
          head = nullptr;
        }
        delete tail;
        tail = tailPrev;
      }
      Node* nodeAddr = new Node(nullptr, head, key, value);
      mp.insert({key, nodeAddr});
      if (tail == nullptr)
      {
        tail = nodeAddr;
      }
      if (head == nullptr)
      {
        head = nodeAddr;
      }
      else
      {
        head->prev = nodeAddr;
      }
      head = nodeAddr;
    }
    else
    {
      result->second->value = value;
      get(key);   // If the key is already present, then it behaves just like an access.
      return;
    }
    // printList();
  }

  virtual int get(int key) override final
  {
    auto result = mp.find(key);
    if (result == mp.end() || head == nullptr)
    {
      return -1;
    }
    Node* nodeAddr{result->second};

    // std::cout << "Found value: " << nodeAddr << ", value: " << nodeAddr->value << ", nodeAddr->next: " << nodeAddr->next
    //           << ", nodeAddr->prev: " << nodeAddr->prev << std::endl;

    // Make recently accessed key as head, so it is easily found in cache
    if (nodeAddr != head)
    {
      // Disconnect the node from the list
      Node* nodePrev = nodeAddr->prev;
      Node* nodeNext = nodeAddr->next;
      // Update next and previous nodes
      if (nodeNext != nullptr)
      {
        nodeNext->prev = nodePrev;
      }
      if (nodePrev != nullptr)
      {
        nodePrev->next = nodeNext;
      }

      // std::cout<<"nodePrev: "<<nodePrev <<", nodeNext: "<<nodeNext<<std::endl;

      // Update tail if necessary
      if (nodeAddr == tail)
      {
        tail = nodePrev;
      }

      nodeAddr->next = head;
      nodeAddr->prev = nullptr;
      head->prev     = nodeAddr;
      head           = nodeAddr;
    }
    // printList();
    return nodeAddr->value;
  }
};