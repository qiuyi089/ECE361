/*
I use the code from Karumanchi to create my source code for my funciton.
*/
#include "queueADT.h"

//Initialize the queue and set it size to the capcity
struct Queue * createQueue(int capacity)
{
    struct Queue * que = malloc(sizeof(struct Queue));//allocate the size for the queue
    //check if the malloc run correctly before initialize the rest of the structure.
    if(!que){
        //if malloc did allocate space then return NULL;
        return NULL;
    }
    que -> capacity = capacity;//set the maxium capacity to what the user want
    que -> front = que -> rear = -1;//set both front and rear to -1 since there is nothing in the queue yet
    que -> array = malloc(que -> capacity * sizeof(int));//initialize the array that going to be storing the data
    //check if malloc running correctly
    if(!que -> array){
        //if it didn't run correctly then return NULL
        return NULL;
    }
    //if everything run correctly then return queue back
    return que;
}
//check if the queue is full
int isFull(struct Queue * que){
    //check if the current size of the queue is the same as the maximum of the queue
    //if they are the same then that mean the queue is full, then return 1 else return 0
    if(que -> array_size == que -> capacity){
        return 1;
    }
    return 0;
}
//check if the queue is empty
int isEmpty(struct Queue * que){
    //if both the front and the rear is -1 then that mean the queue is empty
    //return back 1 if the queue is empty else return 0
    if(que -> front == -1 && que -> rear == -1)
        return 1;
    return 0;
}
//add the data into the queue
int enqueue(struct Queue * que, char d){
    //check for if the queue is full or not if it full then print out overflow and return 0
    //else add the data into the queue and increase the array size by 1. 

    if(isFull(que)){
        printf("Queue is overflow. \n");
        return 0;
    }
    else{
        que -> rear = (que -> rear + 1) % que -> capacity;//set the rear to the last element of the array
        que -> array[que -> rear] = d;//set the data in the rear
        //when the queue first got create and it is empty and there data coming in
        //then set the front to the first element of the array
        if(que -> front == -1){
            que -> front = que -> rear;
        }
        que -> array_size += 1;//increase the size
        return 1;
    }
    return 0;
}
//delete front of the queue
char dequeue(struct Queue * que){
    char temp = 'Q';//set this temp to an element that is not in the data.
    //check for if the queue is empty before performing any deletion.
    //if the queue is empty then return and print out error.
    if(isEmpty(que)){
        printf("The queue is empty. \n");
        return temp;
    }
    //set temp to the first element of the array to hold on to it
    temp = que -> array[que -> front];
    //then check if there is only 1 element in the list.
    //if there is only 1 element in the queue then set both front and rear to -1 to make the 
    //queue empty and size to 0.
    if(que -> front == que -> rear){
        que -> front = que -> rear = -1;
        que -> array_size = 0;
    }
    //if it not the last element in the queue then move the front up by 1 
    //and decrease the size by 1.
    else{
        que -> front = (que -> front + 1) % que -> capacity;
        que -> array_size -= 1;
    }
    //return the delete data back
    return temp;
}
//show all the element in the queue
int listQueueContents(struct Queue * que){
    //create a current to hold the index
    int current = que -> front;
    //use a while loop to traverse the index to display the data
    while(current != que -> rear){
        printf("The %d element is %c \n",current,que -> array[current]);
        current+=1;
    }
    //print out the last element in the list and then return the count back to the call
printf("The %d element is %c \n",current,que -> array[current]);
    current+=1;
    return current;
}







