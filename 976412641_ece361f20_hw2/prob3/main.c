/**
 * test_queueADT.c - Source code for program to test the Queue ADT
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 17-Oct-2020
 *
 * This is the source code to test the array-based Queue ADT
 *
 * @note Code is based on Oliver Rew's HW #3 solution (10/2018)
 */
// include files
#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"

// function prototypes
void testQueue();
int QUEUE_SIZE = 10;
// main program
int main()
{
	//initQueue();
	testQueue();
}

void testQueue()
{
	printf("\n\n======STARTING QUEUE TESTS======\n\n");
    printf("initialize a queue. \n");
    struct Queue * test_queue = createQueue(QUEUE_SIZE);//create an object for the queue
	//use this char to test dequeue
	char first = 'c';

	//Add queue enough to fill the queue
	enqueue(test_queue,first);
	enqueue(test_queue,'g');
	enqueue(test_queue,'t');
	enqueue(test_queue,'Y');
	enqueue(test_queue,'H');
	enqueue(test_queue,'X');
	enqueue(test_queue,'r');
	enqueue(test_queue,'m');
	enqueue(test_queue,'n');
	enqueue(test_queue,'y');
	enqueue(test_queue,'p');	// should fail, queue is full
	enqueue(test_queue,'Z');	// should fail, queue is empty

	if(listQueueContents(test_queue) == QUEUE_SIZE)
		printf("----List Queue Contents Test Successful\n");
	else
		printf("----List Queue Contents Test Failure\n");

	if(isFull(test_queue))
		printf("----Queue Full Test Successful\n");
	else
		printf("----Queue Full Test Failure\n");

	if(dequeue(test_queue) == first)
		printf("----Dequeue Test Successful\n");
	else
		printf("----Dequeue Test Failure\n");

	//empty the queue
	printf("Empty the queue\n");
	for(int i = 0 ; i < QUEUE_SIZE + 1 ; ++i)
		dequeue(test_queue);

	printf("Queue should be empty - nothing displayed\n");
	listQueueContents(test_queue);

	if(isEmpty(test_queue))
		printf("----Queue Empty Test Successful\n");
	else
		printf("----Queue Empty Test Failure\n");
	
	printf("---Testing partial fills---\n");
	printf("   Adding p and Z to queue\n");
	enqueue(test_queue,'p');
	enqueue(test_queue,'Z');
	listQueueContents(test_queue);
	printf("   Removing p\n");
	dequeue(test_queue);
	listQueueContents(test_queue);
	printf("   Adding ! to queue\n");
	enqueue(test_queue,'!');
	listQueueContents(test_queue);
	printf("----Queue Test Complete\n");
}
