#include <iostream>
#include <string>
#include "LRUCache.h"
int main()
{
  int n, capacity, i;
  std::cin >> n >> capacity;
  LRUCache l(capacity);
  for (i = 0; i < n; i++)
  {
    std::string command;
    std::cin >> command;
    if (command == "get")
    {
      int key;
      std::cin >> key;
      std::cout << l.get(key) << std::endl;
    }
    else if (command == "set")
    {
      int key, value;
      std::cin >> key >> value;
      l.set(key, value);
    }
  }
  return 0;
}