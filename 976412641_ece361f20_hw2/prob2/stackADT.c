/*Copyright (c) 2016 CareerMonk Publications and others.
#E-Mail            : info@careermonk.com 
#Creation Date     : 2008-01-10 06:15:46 
#Created by        : Narasimha Karumanchi 
#Book Title        : Data Structures And Algorithms Made Easy
#Warranty          : This software is provided "as is" without any 
#                    warranty; without even the implied warranty of 
#                    merchantability or fitness for a particular purpose.*/

#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"

struct Stack *createStack(){
    struct Stack *stk;
    stk = malloc(sizeof(struct Stack));
    stk->top = NULL;
    return stk;
}

void push(struct Stack *stk, int data){
    struct ListNode *temp;
    temp = malloc(sizeof(struct ListNode));
    if(!temp){
        printf("\nStack/Heap overflow");
        return;
    }
    temp->data = data;
    temp->next = stk->top;
    stk->top = temp;
}

int size(struct Stack *stk){
    // we can improve the size function by adding extra size variable in stack structure
    // and update it while push/pop operations
    int count = 0;
    struct ListNode *temp;
    if(isEmpty(stk))  
        return 0;
    temp = stk->top;
    while (temp){
        count++;
        temp = temp->next;
    }
    return count;
}

int isEmpty(struct Stack *stk){
    return stk->top == NULL;
}

int pop(struct Stack *stk){
    int data;
    struct ListNode *temp;
    if(isEmpty(stk))   
        return INT_MIN;
    temp = stk->top;
    stk->top = stk->top->next;
    data = temp->data;
    free(temp);
    return data;
}

int peek(struct Stack * stk){
    if(isEmpty(stk))  
        return INT_MIN;
    return stk->top->data;
}

void deleteStack(struct Stack *stk){
    struct ListNode *temp, *p;
    p = stk->top;
    while( p) {
        temp = p->next;
        p = p->next;
        free(temp);
    }
    free(stk);
 }
int take_input(struct Stack * stk){
    char user_input;
    int loop = 0;
    int loop2 = 0;
    while(loop == 0){
        printf("Enter your RPN: ");
        while(loop2 == 0){
            scanf(" %c",&user_input);
            if(user_input == '='){
                printf("Top element is %d\n", peek(stk));
                break;
            }
            else if(isdigit(user_input)){
                int temp_hold = atol(&user_input);
                push(stk,temp_hold);
            }
            else if(user_input == '+'){
                int catch_result = rpn_calculator('+',stk);
                push(stk,catch_result);
            }
            else if(user_input == '-'){
                int catch_result = rpn_calculator('-',stk);
                push(stk,catch_result);
            }
            else if(user_input == '/'){
                int catch_result = rpn_calculator('/',stk);
                push(stk,catch_result);
            }
            else if(user_input == '*'){
                int catch_result = rpn_calculator('*',stk);
                push(stk,catch_result);
            }
            else if(user_input == '%'){
                int catch_result = rpn_calculator('%',stk);
                push(stk,catch_result);
            }
            else{
                printf("You didnt enter in correct input program will stop. \n");
                return 1;
            }
        }
        break;
    }
    return 0;
}
int rpn_calculator(char operation, struct Stack * stk){
    int temp1 = pop(stk);
    int temp2 = pop(stk);
    if(operation == '+'){
        return temp2 + temp1;
    }
    else if(operation == '/'){
        return temp2 / temp1;
    }
    else if(operation == '*'){
        return temp2 * temp1;
    }
    else if(operation == '%'){
        return temp2 % temp1;
    }
    else if(operation == '-'){
        return temp2 - temp1;
    }
    return 0;
}




