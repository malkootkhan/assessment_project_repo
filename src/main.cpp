#include "Queue.hpp"
#include <thread>
#include <semaphore.h>
#include <condition_variable>
#include <iostream>
#include <chrono>


/**
 * @Writer task to push elements into the queue
 */
void writeQueue(Queue<int>& queue) {
        
        queue.Push(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
        queue.Push(2);                                                  /**
                                                                          *@push value to queue
                                                                          */
        queue.Push(3);
        queue.Push(4);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
        queue.Push(5);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
}

/** 
 * @Reader task to pop elements from the queue
*/
void readQueue(Queue<int>& queue, int milliSectimeOut) {
    /**
     * @ if there is non-zero value of timeout 
     */
    if(milliSectimeOut) {
        std::cout<<queue.PopWithTimeout(milliSectimeOut)<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
        std::cout<<queue.PopWithTimeout(milliSectimeOut)<<std::endl;
        std::cout<<queue.PopWithTimeout(milliSectimeOut)<<std::endl;
        std::cout<<queue.PopWithTimeout(milliSectimeOut)<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
        std::cout<<queue.PopWithTimeout(milliSectimeOut)<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
    }
    /**
     * @when timeout is not required
     */
    else {
        std::cout<<queue.Pop()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /** 
                                                                        *@Simulate a small delay
                                                                        */
        std::cout<<queue.Pop()<<std::endl;                            /**
                                                                        *@pop value of the queue
                                                                        */
        std::cout<<queue.Pop()<<std::endl;
        std::cout<<queue.Pop()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
        std::cout<<queue.Pop()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  /**
                                                                        *@Simulate a small delay
                                                                        */
    }
}

int main() {
    Queue<int> queue(2);  /**
                            *@Create a queue of size 2
                            */

    int milliSecTimeout;
    std::cout<<"Enter timeout for Pop to wait for value in queue: ";
    std::cin>>milliSecTimeout;



    /**
     * @Create writer and reader threads
     */
    std::thread writer(writeQueue, std::ref(queue));
    std::thread reader(readQueue, std::ref(queue), milliSecTimeout);

    /**
     * @Wait for both threads to finish
     */
    writer.join();
    reader.join();

    return 0;
}

