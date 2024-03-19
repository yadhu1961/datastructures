#include <iostream>

// Input = 12345 decimal, Output - 54321 decimal
uint32_t reverse_digits(uint32_t input)
{
  uint32_t rev_num = 0;
  while (input)
  {
    rev_num = rev_num * 10 + input % 10;
    input   = input / 10;
  }
  return rev_num;
}

int main()
{
  uint32_t number = 12345;
  printf("reversedDigits of %d is %d\n", number, reverse_digits(number));
  return 0;
}