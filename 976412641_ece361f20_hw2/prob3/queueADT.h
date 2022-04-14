/*
I use the code from Karumanchi to create my function. 
*/
#include <stdio.h>
#include <stdlib.h>
/*
Create a struct for the queue ADT
*/
struct Queue{
    int capacity;//the maximum size of the queue
    int front, rear;//the front index and the rear index on the queue
    int array_size;//the current size of the array
    char * array;//The array that store the data
};

struct Queue *createQueue(int capacity);//Initialize the queue and set it size to the capcity
int isFull(struct Queue * que);//check if the queue is full 
int isEmpty(struct Queue * que);//check if the queue is empty
int enqueue(struct Queue * que,char d);//add the data to the queue
char dequeue(struct Queue * que);//delete the data from the queue
int listQueueContents(struct Queue * que);//display everything in the queue
