#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "queue.h"

/**
 * Produces
 */
void *producer()
{
  uint8_t dataByte     = 0;
  uint8_t dataArray[6] = {0};
  while (1)
  {
    dataArray[0]            = dataByte++;
    dataArray[1]            = dataByte++;
    uint8_t numBytesWritten = write_queue(dataArray, 2);
    if (numBytesWritten < 2)
    {
      printf("%d bytes dropped since queue is full, ", 2 - numBytesWritten);
      printBytes(dataArray, numBytesWritten, "Wrote: ");
    }
    else
    {
      printf("wrote %d bytes to the queue, ", numBytesWritten);
      printBytes(dataArray, 2, "Wrote: ");
    }
    usleep(2000);

    dataArray[0]    = dataByte++;
    dataArray[1]    = dataByte++;
    dataArray[2]    = dataByte++;
    dataArray[3]    = dataByte++;
    dataArray[4]    = dataByte++;
    dataArray[5]    = dataByte++;
    numBytesWritten = write_queue(dataArray, 6);
    if (numBytesWritten < 6)
    {
      printf("%d bytes dropped since queue is full, ", 6 - numBytesWritten);
      printBytes(dataArray, numBytesWritten, "Wrote: ");
    }
    else
    {
      printf("wrote %d bytes to the queue, ", numBytesWritten);
      printBytes(dataArray, 6, "Wrote: ");
    }
    usleep(6000);
  }
}

void readBytes()
{
  uint8_t dataArraySize = 2;
  uint8_t dataArray[2]  = {0};
  uint8_t numBytesRead  = read_queue(dataArray, 2);
  if (numBytesRead < 2)
  {
    printf("requested %d bytes but %d bytes read\n", 2, numBytesRead);
    printBytes(dataArray, numBytesRead, "Read: ");
  }
  else
  {
    printf("read %d bytes from queue\n", numBytesRead);
    printBytes(dataArray, numBytesRead, "Read: ");
  }
}

void *consumer()
{
  while (1)
  {
    readBytes();
    usleep(2000);
    readBytes();
    usleep(2000);
    readBytes();
    usleep(2000);
    readBytes();
    usleep(2000);
  }
}

int main()
{
  pthread_t producer_thread;
  pthread_t consumer_thread;
  printf("Before Threads have started their work\n");

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  printf("After Threads have finished their work\n");

  return 0;
}