#include <iostream>
#include "Stack.h"

int main()
{
  Stack<int> stack;
  stack.printStack();
  std::cout << "stack isEmpty: " << stack.isEmpty() << std::endl;

  std::cout << "stack.front().has_value(): " << stack.top().has_value() << std::endl;

  stack.pop();

  stack.push(1);
  stack.printStack();
  stack.push(2);
  stack.printStack();

  std::cout << "stack.front().has_value(): " << stack.top().has_value() << std::endl;

  std::cout << "stack isEmpty: " << stack.isEmpty() << std::endl;

  stack.pop();
  stack.printStack();
  stack.push(3);
  stack.printStack();
  stack.pop();
  stack.printStack();
  stack.pop();
  std::cout << "stack isEmpty: " << stack.isEmpty() << std::endl;
  return 0;
}