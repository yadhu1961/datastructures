#include <assert.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Implement memmove().
 * Should return dest. Must not fail, assumes enough memory is allocated at destination.
 * Naive implementation, copies data byte by byte
 */
void *mem_move(void *dest, const void *src, size_t n)
{
  const uint8_t *uint8Src = (uint8_t *)src;

  uint8_t *uint8Dest = (uint8_t *)dest;

  // If source and destination are same, just return.
  if (src == dest)
  {
    return dest;
  }

  // beginning of destination overlaps ends of source
  // 00        11
  // src[0]  src[1]
  //         dest[0]  dest[1]
  if ((uint8Dest + n) > uint8Src + n)
  {
    for (int8_t index = n - 1; index >= 0; --index)
    {
      uint8Dest[index] = uint8Src[index];
    }
  }
  else
  {
    // end of destination overlaps with beginning of source
    //            0x1    0x2
    //            src[0] src[1]
    // dst[0]    dst[1]
    for (int8_t index = 0; index < n; index++)
    {
      uint8Dest[index] = uint8Src[index];
    }
  }

  return dest;
}

void dump_mem(uint8_t *buffer, size_t len)
{
  assert(buffer != NULL);
  for (uint8_t index = 0; index < len; ++index)
  {
    printf("%d ", buffer[index]);
  }
  printf("\n");
}

// To execute C, please define "int main()"
int main()
{
  uint8_t  mem[10] = {0, 0, 25, 31, 52, 43, 0, 0, 0, 0};
  uint8_t *source  = mem + 2;
  dump_mem(source, 4);
  source = mem_move(source, source, 4);   // exactly overlapping memory
  dump_mem(source, 4);
  source = mem_move(mem, source, 4);   // end of dest overlaps with beginning of source, source = mem
  dump_mem(source, 4);
  source = mem_move(mem + 4, source, 4);   // non overlapping memory, source = mem+4
  dump_mem(source, 4);
  source = mem_move(mem + 6, source, 4);   // beginning of dest overlaps with source end.
  dump_mem(source, 4);

  return 0;
}