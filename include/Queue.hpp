#ifndef __QUEUE_HPP
#define __QUEUE_HPP

#include <iostream>             /*standard input output header */    
#include <condition_variable>   /*part of thread library provides thread synchronization*/
#include <stdexcept>            /*standard exception library*/
#include <chrono>               /*Time and duration library*/
#include <semaphore.h>          /*Include POSIX semaphore header*/

/**
 * @class Queue
 * @brief A brief description of what the class does.
 *
 * This class provides functionality to perform specific tasks related to
 * queue operations. It includes methods to Push, Pop, PopWithTimeout, count, size operations
 * and handles data variables defined in the class. 
 *
 * @details
 * The Queue class is designed to handle basic typical queue operations and maitain data.
 * It manages the lifecycle of of data and provides interfaces for Pop, PopWithTimeout, Push, size, and count operations.
 * The class is thread-safe and ensures that resources are efficiently managed.
 *
 * @note
 * - The class is designed for linux CMake build system and can be built and run in any other OS
 *
 * @author 
 * @date 2024-09-19
 *
 * @version 1.0
 *
 * @example
 * Example usage:
 * @code
 * Queue obj(queue_size);
 * obj.Pop<int>(); or obj.Push<int>(data);
 * @endcode
 *
 * @see the class and the related members functions and variables
 */

/**
 * @Template class for the multi-threaded queue
 */
template<typename T>
class Queue {
private:
    T* data;                       /**
                                     *@Pointer to dynamic array for storing queue elements
                                     */
    int front, rear, size, count;   /**
                                      *@Front and rear index, size of the queue, current count of elements
                                      */
    std::condition_variable cv;     /**
                                      *@Condition variable for blocking operations
                                      */
    std::mutex cv_mtx;              /**
                                      *@Mutex for condition variable use
                                      */

    sem_t sem;                      /**
                                      *@POSIX semaphore for access control (replacing the mutex)
                                      */

public:
    /**
     * @Constructor to initialize the queue with a given size
     */
    Queue(int maxSize) : size(maxSize), front(0), rear(0), count(0) {
        data = new T[size];  /**
                               *@Dynamically allocate memory for queue
                               */

        /**
         * @Initialize the semaphore with a value of 1 to allow one thread at a time
         */
        sem_init(&sem, 0, 1);
    }

    /**
     * @Destructor to release memory
     */
    ~Queue() {
        delete[] data;
        sem_destroy(&sem);  /**
                              *@Destroy the semaphore
                              */
    }

    /**
     * @Function to push an element into the queue
     */
    void Push(T element) {
        {
            /**
             * @Acquire the semaphore (lock)
             */
            sem_wait(&sem);

            if (count == size) {
                /**
                 * @If the queue is full, drop the oldest element
                 */
                front = (front + 1) % size;
                count--;
            }

            /**
             * @Insert the new element
             */
            data[rear] = element;
            rear = (rear + 1) % size;
            count++;

            /**
             * @Release the semaphore (unlock) immediately after queue modification
             */
            sem_post(&sem);
        }

        /**Notify one waiting thread that a new element is available
         */
        std::lock_guard<std::mutex> lk(cv_mtx);
        cv.notify_one();
    }

    /**Function to pop an element, blocks indefinitely if empty
     */
    T Pop() {
        std::unique_lock<std::mutex> lk(cv_mtx);

        /**
         * @Wait until there's at least one element in the queue
         */
        cv.wait(lk, [this] { return count > 0; });

        T value;
        {
            /**
             * @Acquire the semaphore (lock)
             */
            sem_wait(&sem);

            /**
             * @Retrieve and remove the front element
             */
            value = data[front];
            front = (front + 1) % size;
            count--;

            /**
             * @Release the semaphore (unlock)
             */
            sem_post(&sem);
        }

        return value;
    }

    /**
     * @Function to pop an element with a timeout, throws exception on timeout
     */
    T PopWithTimeout(int milliseconds) {
        std::unique_lock<std::mutex> lk(cv_mtx);

        /**
         * @Wait with timeout for an element to be available
         */
        if (cv.wait_for(lk, std::chrono::milliseconds(milliseconds), [this] { return count > 0; })) {
            T value;
            {
                /**
                 * @Acquire the semaphore (lock)
                 */
                sem_wait(&sem);

                /**
                 * @Retrieve and remove the front element
                 */
                value = data[front];
                front = (front + 1) % size;
                count--;

                /**
                 * @Release the semaphore (unlock)
                 */
                sem_post(&sem);
            }
            return value;
        } else {
            /**
             * @Timeout occurred, throw an exception
             */
            throw std::runtime_error("Pop timeout: queue is empty.");
        }
    }

    /**
     * @Return the number of elements currently in the queue
     */
    int Count() {
        sem_wait(&sem);  /**
                           *@Acquire the semaphore (lock)
                           */
        int currentCount = count;
        sem_post(&sem);  /**
                           *@Release the semaphore (unlock)
                           */
        return currentCount;
    }

    /**
     * @Return the maximum size of the queue
     */
    int Size() {
        return size;
    }
};

#endif /**
         *@QUEUE_HPP
         */

