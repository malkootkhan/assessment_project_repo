#include "Queue.hpp"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

/**
 * @Test Case 1: single Push and Pop
 */
TEST(QueueTest, singlePushPop) {
    Queue<int> queue(2);  /**
                            *@Queue of size 3
                            */

    /**
     * @Push elements into the queue
     */
    queue.Push(1);

    /**
     * @Pop and verify the elements
     */
    EXPECT_EQ(queue.Pop(), 1);
}
/**
 * Test Case 2: three Push Pop
 */
TEST(QueueTest, threePushPop){
    Queue<int> queue(2);

    queue.Push(2);
    queue.Push(3);
    queue.Push(4);

    EXPECT_EQ(queue.Pop(), 3);
    EXPECT_EQ(queue.Pop(), 4);
    queue.Push(5);
    EXPECT_EQ(queue.Pop(), 5);
}

/**
 * @Test Case 3: Pop with Timeout Success
 */
TEST(QueueTest, PopWithTimeoutSuccess) {
    Queue<int> queue(2);

    /**
     * @Push an element
     */
    queue.Push(42);

    /**
     * @Pop with timeout
     */
    EXPECT_EQ(queue.PopWithTimeout(100), 42);  /**
                                                 *@Expect 42 before timeout
                                                 */
}

/**
 * @Test Case 4: Pop with Timeout Failure
 */
TEST(QueueTest, PopWithTimeoutFailure) {
    Queue<int> queue(2);

    /**
     * @Try to pop from an empty queue with a timeout of 100ms
     */
    EXPECT_THROW(queue.PopWithTimeout(100), std::runtime_error);  /**
                                                                    *@Expect timeout exception
                                                                    */
}

/**
 * @Test Case 5: Overwrite Old Elements in Full Queue
 */
TEST(QueueTest, OverwriteOldElementInFullQueue) {
    Queue<int> queue(2);  /**
                            *@Queue of size 2
                            */

    /**
     * @Push elements into the queue
     */
    queue.Push(1);
    queue.Push(2);
    
    /**
     * @Push another element to overwrite the oldest
     */
    queue.Push(3);  /**
                      *@Should overwrite 1
                      */

    /**
     * @Pop and verify the elements
     */
    EXPECT_EQ(queue.Pop(), 2);  /**
                                  *@Oldest element is 2 (1 was overwritten)
                                  */
    EXPECT_EQ(queue.Pop(), 3);  /**
                                  *@Next is 3
                                  */
}

