#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

#define MAX_VAL 10
// global binary semaphore instances
// object counts are set to zero
// objects are in non-signaled state
std::binary_semaphore smphSignalZeroToEvenThread{0}, smphSignalToZeroThread{0};
std::binary_semaphore smphSignalZeroToOddThread{0};
volatile uint32_t     counter = 0;

void threadZero()
{
  // Wait for child threads(odd or even threads) to notify
  //   std::cout<<"starting thread zero\n";
  do
  {
    smphSignalToZeroThread.acquire();
    counter = counter + 1;
    if (counter > MAX_VAL)
      break;
    std::cout << "0 ";
    if (counter & 1)
    {
      // std::cout<<"Signalling to odd thread\n";
      smphSignalZeroToOddThread.release();
    }
    else
    {
      // std::cout<<"Signalling to even thread\n";
      smphSignalZeroToEvenThread.release();
    }

  } while (counter <= MAX_VAL);
  //   std::cout<<"\nExiting thread zero\n";
  smphSignalZeroToEvenThread.release();
  smphSignalZeroToOddThread.release();
  return;
}

void threadOdd()
{
  // std::cout<<"starting thread odd\n";
  while (1)
  {
    // wait for a signal from the zero proc
    // by attempting to decrement the semaphore
    smphSignalZeroToOddThread.acquire();
    if (counter > MAX_VAL)
      break;
    std::cout << counter << " ";
    // signal the zero thread back
    smphSignalToZeroThread.release();
  }
  return;
}

void threadEven()
{
  // std::cout<<"starting thread even\n";
  while (1)
  {
    // wait for a signal from the zero proc
    // by attempting to decrement the semaphore
    smphSignalZeroToEvenThread.acquire();
    if (counter > MAX_VAL)
      break;
    std::cout << counter << " ";
    // signal the zero thread back
    smphSignalToZeroThread.release();
  }
  return;
}

int main()
{
  // create some worker thread
  std::thread thrWorkerZero(threadZero), thrWorkerOdd(threadOdd), thrWorkerEven(threadEven);

  std::cout << "signalling thread zero\n";
  smphSignalToZeroThread.release();

  thrWorkerZero.join();
  thrWorkerOdd.join();
  thrWorkerEven.join();

  std::cout << "\nAll threads finished their work\n";
  return 0;
}