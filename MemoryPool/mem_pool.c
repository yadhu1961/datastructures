#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct memory_pool_t
{
  char  memory[4096];
  char* ptr;
};
typedef struct memory_pool_t mem_pool_t;

// Allocate memory for pool
mem_pool_t mem_pool;

void init_mem_pool(mem_pool_t* mem_pool) { mem_pool->ptr = mem_pool->memory; }

void* allocate(size_t mem_size)
{
  // printf("Size of memory pool %llu and curr ptr %p, last ptr %p\n", sizeof mem_pool.memory, mem_pool.ptr, mem_pool.memory + sizeof
  // mem_pool.memory);
  // assert(mem_pool.memory + sizeof mem_pool.memory >= mem_pool.ptr + mem_size && "Memory pool exhausted");

  if ((mem_pool.memory + sizeof mem_pool.memory < mem_pool.ptr + mem_size))
  {
    printf("Memory Pool exhausted\n");
    return NULL;
  }

  void* alloc = mem_pool.ptr;
  mem_pool.ptr += mem_size;
  return alloc;
}

int main()
{
  init_mem_pool(&mem_pool);
  for (uint8_t count = 0; count < 6; ++count)
  {
    void* ptr = allocate(1024);
    if (ptr != NULL)
    {
      printf("Memory block successfully allocated: %p\n", ptr);
    }
  }
  return EXIT_SUCCESS;
}