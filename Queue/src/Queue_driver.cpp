#include <iostream>
#include "Queue.h"

int main()
{
  Queue<int> queue;
  queue.printQueue();
  std::cout << "queue isEmpty: " << queue.isEmpty() << std::endl;

  std::cout << "queue.front().has_value(): " << queue.front().has_value() << std::endl;

  queue.dequeue();

  queue.enque(1);
  queue.printQueue();
  queue.enque(2);
  queue.printQueue();

  std::cout << "queue.front().has_value(): " << queue.front().has_value() << std::endl;

  std::cout << "queue isEmpty: " << queue.isEmpty() << std::endl;

  queue.dequeue();
  queue.printQueue();
  queue.enque(3);
  queue.printQueue();
  queue.dequeue();
  queue.printQueue();
  queue.dequeue();
  std::cout << "queue isEmpty: " << queue.isEmpty() << std::endl;
  return 0;
}