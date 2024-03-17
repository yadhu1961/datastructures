#include <iostream>
#include <cstdint>
#include <array>
#include <cassert>

static constexpr uint8_t size0 = 3;
static constexpr uint8_t size1 = 2;

/**
 * For debugging purposes
 */
template <typename T>
void printArray(const T& array, int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", array[i]);
  printf("\n");
}

int merge(std::array<uint32_t, size0 + size1>& result,
          std::array<uint32_t, size0>&         array0,
          std::array<uint32_t, size1>&         array1)
{
  uint16_t array0_idx = 0;
  uint16_t array1_idx = 0;
  uint16_t result_idx = 0;

  while (array0_idx < size0 && array1_idx < size1)
  {
    if (array0[array0_idx] < array1[array1_idx])
    {
      result[result_idx] = array0[array0_idx];
      array0_idx++;
    }
    else
    {
      result[array1_idx] = array1[array1_idx];
      array1_idx++;
    }
    result_idx++;
  }

  if (array0_idx < size0)
  {
    // memcpy(result + result_idx, arra + subarray0_idx, (size0 - array0_idx) * sizeof(uint32_t));
    std::copy(array0.begin() + array0_idx, array0.end(), result.begin() + result_idx);
  }

  if (array1_idx < size1)
  {
    // memcpy(array + array_idx, subarray1 + subarray1_idx, (size1 - array1_idx) * sizeof(uint32_t));
    std::copy(array1.begin() + array1_idx, array1.end(), result.begin() + result_idx);
  }

  return 0;
}

int main()
{
  std::array<uint32_t, size0> array0 = {2, 3, 5};
  std::array<uint32_t, size1> array1 = {1, 2};

  std::array<uint32_t, size0 + size1> merged;

  merge(merged, array0, array1);

  printArray(merged, size0 + size1);

  return 0;
}