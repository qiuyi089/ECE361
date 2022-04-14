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

// main program
int main()
{
	initQueue();
	testQueue();
}

void testQueue()
{
	printf("\n\n======STARTING QUEUE TESTS======\n\n");
	//use this char to test dequeue
	char first = 'c';

	//Add queue enough to fill the queue
	enqueue(first);
	enqueue('g');
	enqueue('t');
	enqueue('Y');
	enqueue('H');
	enqueue('X');
	enqueue('r');
	enqueue('m');
	enqueue('n');
	enqueue('y');
	enqueue('p');	// should fail, queue is full
	enqueue('Z');	// should fail, queue is empty

	if(listQueueContents() == QUEUE_SIZE)
		printf("----List Queue Contents Test Successful\n");
	else
		printf("----List Queue Contents Test Failure\n");

	if(isFull())
		printf("----Queue Full Test Successful\n");
	else
		printf("----Queue Full Test Failure\n");

	if(dequeue() == first)
		printf("----Dequeue Test Successful\n");
	else
		printf("----Dequeue Test Failure\n");

	//empty the queue
	printf("Empty the queue\n");
	for(int i = 0 ; i < QUEUE_SIZE + 1 ; ++i)
		dequeue();

	printf("Queue should be empty - nothing displayed\n");
	listQueueContents();

	if(isEmpty())
		printf("----Queue Empty Test Successful\n");
	else
		printf("----Queue Empty Test Failure\n");
	
	printf("---Testing partial fills---\n");
	printf("   Adding p and Z to queue\n");
	enqueue('p');
	enqueue('Z');
	listQueueContents();
	printf("   Removing p\n");
	dequeue();
	listQueueContents();
	printf("   Adding ! to queue\n");
	enqueue('!');
	listQueueContents();
	printf("----Queue Test Complete\n");
}
