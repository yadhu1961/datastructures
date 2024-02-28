#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <cstddef>
#include <new>
#include <iostream>

struct UnalignedA
{
  int mInt = 0;
};

struct alignas(64) AlignedA
{
  int mInt = 0;
};

template <typename T>
static void counter(T* arr)
{
  printf("address of arr: %p\n", arr);

  // Increment the variable repeatedly
  auto process = [](int* num) {
    for (int i = 0; i < 100000000; i++)
      *num = *num + std::rand();
  };

  // Starting time
  auto startTime = std::chrono::high_resolution_clock::now();

  // Spawn and wait for threads to finish
  std::thread t1(process, &arr[0].mInt);
  std::thread t2(process, &arr[1].mInt);
  t1.join();
  t2.join();

  // Finish time
  auto endTime = std::chrono::high_resolution_clock::now();

  std::string logString = (alignof(T) == 64) ? "Aligned" : "Unaligned";

  // Get results
  std::cout << std::string(logString + std::string(" duration: ")).c_str()
            << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.f << " ms" << std::endl;
}

int main()
{
  // Initialise array
  UnalignedA* arrUnaligned = new UnalignedA[2];
  AlignedA*   arrAligned   = new AlignedA[2];

  // Seed rand
  std::srand(std::time(nullptr));

  std::cout << "max alignment size " << alignof(std::max_align_t) << std::endl;

  printf("address of arrUnaligned: %p, alignof(arrUnaligned): %ld\n", arrUnaligned, alignof(UnalignedA));
  printf("address of arrAligned: %p, alignof(arrAligned): %ld\n", arrAligned, alignof(AlignedA));

  // unaligned processor
  counter(arrUnaligned);

  // aligned processor
  // counter(arrAligned);

  // Deallocate
  delete[] arrUnaligned;
  delete[] arrAligned;

  return 0;
}