#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define QUEUE_SIZE 16

// Visibility is only inside this function, always load the value from memory.
static volatile int8_t writeIdx = -1;   // works till queue size is 128
static volatile int8_t readIdx  = -1;   // works till queue size is 128
/**
 * Queue containing the data generated by producer
 */
uint8_t queue[QUEUE_SIZE] = {0};

void printBytes(uint8_t data[], uint8_t len, char mode[])
{
  if (len == 0)
  {
    return;
  }
  printf("%s bytes", mode);
  for (uint8_t dataIdx = 0; dataIdx < len; ++dataIdx)
  {
    printf(" %2d, ", data[dataIdx]);
  }
  printf("\n");
}

uint8_t read_queue(uint8_t output[], const uint8_t outputSize)
{
  uint8_t       numberOfBytesCopied = 0;
  const int16_t localWriteIdx       = writeIdx;
  printf("read_queue: readIdx %d, writeIdx: %d, numBytesToRead %d\n", readIdx, localWriteIdx, outputSize);
  if (readIdx == -1)
  {
    // Indicates the queue is empty.
    printf("queue is empty, readIdx %d, writeIdx: %d\n", readIdx, localWriteIdx);
    return numberOfBytesCopied;
  }

  if (readIdx < localWriteIdx)
  {
    // outputSize = 5
    // 0 1 2 3 4 5 6 7
    //     R       W
    const uint8_t numberOfBytesInQueue = localWriteIdx - readIdx;
    numberOfBytesCopied                = outputSize >= numberOfBytesInQueue ? numberOfBytesInQueue : outputSize;
    memcpy(output, queue + readIdx, numberOfBytesCopied);
    readIdx = (readIdx + numberOfBytesCopied) & (QUEUE_SIZE - 1);
  }
  else
  {
    uint8_t numBytesToCopyTillQueueEnd = outputSize >= (QUEUE_SIZE - readIdx) ? (QUEUE_SIZE - readIdx) : outputSize;
    memcpy(output, queue + readIdx, numBytesToCopyTillQueueEnd);
    if (numBytesToCopyTillQueueEnd < outputSize)
    {
      readIdx             = readIdx + numBytesToCopyTillQueueEnd;
      numberOfBytesCopied = numBytesToCopyTillQueueEnd;
    }
    else
    {
      const uint8_t numBytesToCopyFromQueueStart =
          (outputSize - numBytesToCopyTillQueueEnd) < (localWriteIdx) ? (outputSize - numBytesToCopyTillQueueEnd) : localWriteIdx;
      memcpy(output + numBytesToCopyTillQueueEnd, queue, numBytesToCopyFromQueueStart);
      readIdx             = (readIdx + numBytesToCopyFromQueueStart + numBytesToCopyTillQueueEnd) & (QUEUE_SIZE - 1);
      numberOfBytesCopied = numBytesToCopyFromQueueStart + numBytesToCopyTillQueueEnd;
    }
  }
  if (readIdx == writeIdx)
  {
    readIdx = writeIdx = -1;
  }
  return numberOfBytesCopied;
}

uint8_t write_queue(uint8_t input[], const uint8_t inputSize)
{
  printf("write_queue: readIdx %d, writeIdx: %d, inputSize %d\n", readIdx, writeIdx, inputSize);
  if (readIdx == 0 && writeIdx == (QUEUE_SIZE - 1) || ((writeIdx == readIdx) && writeIdx != -1))
  {
    printf("Queue is full readIdx %d, writeIdx: %d, inputSize %d\n", readIdx, writeIdx, inputSize);
    return 0;
  }

  if (inputSize == 0)
  {
    printf("Input data size is zero\n");
    return 0;
  }

  // printBytes(input, inputSize, "dataToWrite: ");
  // printBytes(queue, 16, "before debug queue: ");
  uint8_t numBytesQueued     = 0;
  readIdx                    = readIdx == -1 ? 0 : readIdx;
  const uint8_t localReadIdx = readIdx;

  if (writeIdx < localReadIdx || writeIdx == -1)
  {
    // inputSize = 6
    // 0 1 2 3 4 5 6 7 8 9
    //     W       R
    const uint8_t freeQueueSize = (writeIdx == -1) ? QUEUE_SIZE : localReadIdx - writeIdx;
    writeIdx                    = (writeIdx == -1) ? 0 : writeIdx;
    numBytesQueued              = inputSize < freeQueueSize ? inputSize : freeQueueSize;
    memcpy(queue + writeIdx, input, numBytesQueued);
    writeIdx = (writeIdx + numBytesQueued) & (QUEUE_SIZE - 1);
    // printBytes(queue, 16, "after debug queue: ");
    return numBytesQueued;
  }
  else
  {
    // inputSize = 5
    // 0 1 2 3 4 5 6 7 8 9
    //     R       W

    // printf("else write_queue: readIdx %d, writeIdx: %d\n", localReadIdx, writeIdx);
    const uint8_t freeQueueSizeTillEnd  = QUEUE_SIZE - writeIdx;
    const uint8_t numBytesToCopyTillEnd = inputSize < freeQueueSizeTillEnd ? inputSize : freeQueueSizeTillEnd;
    memcpy(queue + writeIdx, input, numBytesToCopyTillEnd);
    if (numBytesToCopyTillEnd == inputSize)
    {
      writeIdx = (writeIdx + numBytesToCopyTillEnd) & (QUEUE_SIZE - 1);
      // printBytes(queue, 16, "after debug queue: ");
      numBytesQueued = inputSize;
      return inputSize;
    }
    const uint8_t freeQueueSizeFromStart  = localReadIdx;
    const uint8_t remainingBytesToCopy    = inputSize - numBytesToCopyTillEnd;
    const uint8_t numBytesToCopyFromStart = freeQueueSizeFromStart < remainingBytesToCopy ? freeQueueSizeFromStart : remainingBytesToCopy;
    memcpy(queue, input + numBytesToCopyTillEnd, numBytesToCopyFromStart);
    numBytesQueued = numBytesToCopyTillEnd + numBytesToCopyFromStart;
    writeIdx       = (writeIdx + numBytesQueued) & (QUEUE_SIZE - 1);
    // printBytes(queue, 16, "after debug queue: ");
    return numBytesQueued;
  }
}
