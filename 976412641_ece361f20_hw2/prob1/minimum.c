#include "header.h"
int take_input(){
    int n;
    printf("Enter your input: ");
    if(!scanf("%d ",&n)){
        printf("You have enter something that is not a number. \n");
        printf("Please enter your input again. \n");
        return 0;
    }
    check_input_number(n);
    int user_input[n];
    for(int i = 0; i < n;i++){
        if(!(scanf("%d",&user_input[i]))){
            printf("You have enter something that is not a number. \n");
            printf("Please enter your input again. \n");
            i = n;
            return 0;
        }
    }
    return minimum(user_input,n);
}
void check_input_number(int number){
    if(number == 0 || number < 0){
        printf("your number is either negative or a zero. \n");
        printf("Program will now terminate. \n");
        exit(0);  
    }
}
int minimum(int list[],int n){
    int mininum_val = list[1];
    int catch = minimum2(list,n,mininum_val);
    printf("The min is %d \n",catch);
    return 1;
}
int minimum2(int list[],int n, int min_number){
    if(n == 0){
        if(min_number > list[n]){
            min_number = list[n];
        }
        return min_number;
    }
    else{
        if(min_number > list[n]){
            min_number = list[n];
        }
        return minimum2(list,n - 1, min_number);
    }
}