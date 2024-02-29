#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void* aligned_malloc(int size, unsigned int alignment)
{
  printf("size %d, alignment %d\n", size, alignment);
  void* ptr = malloc(size + alignment + 1);   // One extra byte to store the offset;

  printf("Allocated ptr %p, mask %x\n", ptr, (alignment - 1));

  uint16_t offset = (uint64_t)ptr & (alignment - 1);

  printf("calculated offset to aligned address %x\n", offset);

  void* ptrToReturn = ptr + (offset == 0 ? alignment : (alignment - offset));

  *(uint8_t*)(ptrToReturn - 1) = ptrToReturn - ptr;

  printf("ptrToReturn %p, offset from allocated address to aligned address %x\n", ptrToReturn, *((uint8_t*)ptrToReturn - 1));

  return ptrToReturn;
}

/*
4 bytes, 8 byte aligned + 1 byte ==> 13 bytes
offset = 7
X           o X
1 2 3 4 5 6 7 8 9 10 11 12 13

4 bytes, 8 byte aligned, + 1 byte ==> 13 bytes
offset = 0.
X             o X
0 1 2 3 4 5 6 7 8  9 10 11 12

8 bytes, 4 byte aligned + 1 byte ==> 13 bytes
X           o X
1 2 3 4 5 6 7 8 9 10 11 12 13

8 bytes, 4 byte aligned, + 1 byte ==> 13 bytes
offset = 0.
X     o X
0 1 2 3 4 5 6 7 8 9 10 11 12

*/

void aligned_free(void* ptr)
{
  printf("aligned_free: ptr %p\n", ptr);
  void* ptrToRelease = ptr - *((uint8_t*)ptr - 1);
  printf("aligned_free: ptrToRelease %p\n", ptrToRelease);
  free(ptrToRelease);
}

int main()
{
  void* ptr = aligned_malloc(20, 16);
  aligned_free(ptr);

  printf("######################################################\n");

  ptr = aligned_malloc(10, 4);
  aligned_free(ptr);

  printf("######################################################\n");

  ptr = aligned_malloc(10, 8);
  aligned_free(ptr);

  printf("######################################################\n");

  ptr = aligned_malloc(30, 32);
  aligned_free(ptr);

  printf("######################################################\n");

  ptr = aligned_malloc(40, 64);
  aligned_free(ptr);

  printf("######################################################\n");

  ptr = aligned_malloc(50, 128);
  aligned_free(ptr);

  printf("######################################################\n");

  ptr = aligned_malloc(50, 256);
  aligned_free(ptr);

  printf("######################################################\n");
}