/*Copyright (c) 2016 CareerMonk Publications and others.
#E-Mail            : info@careermonk.com 
#Creation Date     : 2008-01-10 06:15:46 
#Created by        : Narasimha Karumanchi 
#Book Title        : Data Structures And Algorithms Made Easy
#Warranty          : This software is provided "as is" without any 
#                    warranty; without even the implied warranty of 
#                    merchantability or fitness for a particular purpose.*/

#include "header.h"

int main(){
    int flag = 0;
    while((flag) == 0){
        struct Stack *stk = createStack();
        if((take_input(stk)) == 1){
            flag = 1;
        }
        if((isEmpty(stk))){
            deleteStack(stk);
            break;
        }
        int pop_size = size(stk);
        for(int i = 0; i < pop_size; i++){
            pop(stk);
        }
        deleteStack(stk);
    }
    return 0;
 }







