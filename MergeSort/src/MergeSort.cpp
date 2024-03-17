#include <iostream>
#include <cstdint>
#include <cstring>

/**
 * For debugging purposes
 */
void printArray(int A[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", A[i]);
  printf("\n");
}

void merge(int array[], const int16_t left, const int16_t mid, const int16_t right)
{
  const int16_t subarray0_size = mid - left + 1;
  const int16_t subarray1_size = right - mid;

  int subarray0[subarray0_size], subarray1[subarray1_size];

  memcpy(subarray0, &array[left], subarray0_size * sizeof(int));
  memcpy(subarray1, &array[mid + 1], subarray1_size * sizeof(int));

  int16_t subarray0_idx = 0;
  int16_t subarray1_idx = 0;
  int16_t array_idx     = left;

  while (subarray0_idx < subarray0_size && subarray1_idx < subarray1_size)
  {
    if (subarray0[subarray0_idx] < subarray1[subarray1_idx])
    {
      array[array_idx] = subarray0[subarray0_idx];
      subarray0_idx++;
    }
    else
    {
      array[array_idx] = subarray1[subarray1_idx];
      subarray1_idx++;
    }
    array_idx++;
  }

  if (subarray0_idx < subarray0_size)
  {
    memcpy(array + array_idx, subarray0 + subarray0_idx, (subarray0_size - subarray0_idx) * sizeof(int));
  }

  if (subarray1_idx < subarray1_size)
  {
    memcpy(array + array_idx, subarray1 + subarray1_idx, (subarray1_size - subarray1_idx) * sizeof(int));
  }
}

void mergeSort(int array[], const int16_t l, const int16_t r)
{
  if (l >= r)
    return;

  const int16_t mid = l + (r - l) / 2;

  mergeSort(array, l, mid);
  mergeSort(array, mid + 1, r);

  merge(array, l, mid, r);
}

int main()
{
  int arr[]    = {15, 12, 11, 13, 5};
  int arr_size = sizeof(arr) / sizeof(arr[0]);

  printf("Given array is \n");
  printArray(arr, arr_size);

  mergeSort(arr, 0, arr_size - 1);

  printf("\nSorted array is \n");
  printArray(arr, arr_size);
  return 0;
}