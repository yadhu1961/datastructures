
#include <iostream>
#include "Vector.h"

int main()
{
  auto customVector{CustomVector<int, 0, 0>(10)};

  customVector.pushBack(int{10});
  customVector.pushBack(int{11});

  customVector.emplaceBack(int{12});
  customVector.emplaceBack(int{13});

  std::cout << customVector.at(0) << std::endl;
  std::cout << customVector.at(1) << std::endl;

  std::cout << customVector.at(2) << std::endl;
  std::cout << customVector.at(3) << std::endl;

  return 0;
}