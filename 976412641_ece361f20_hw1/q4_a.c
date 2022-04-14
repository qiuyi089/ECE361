#include<stdio.h>
#include<stdlib.h>

void calculate_bill(int amount);//prototype of calculate how many 20$,10$,5$,1$ they going to need.

int main(){
	int input = 0;//store the user input
	//ask the user for the amount of money they going to pay
	printf("Please enter in the amount you want to pay: ");
	scanf("%d",&input);
	calculate_bill(input);
	return 0;
}

void calculate_bill(int amount){
	//check while the amount of money does not reach 0 keep on finding out how 
	//many bills till it hit 0.
	while(amount > 0){
		//if the amount of money is bigger or equal to 20 then 
		//take the number of time it divide by 20 and then find the 
		//amount that is going to be taken away by time the number of time
		//then take the amount and subtract it to the amount that going to be taken.
		if(amount >= 20){
			int num = amount / 20;
			int taken = 20 * num;
			amount = amount - taken;
			printf("the amount of 20$ you need is %d \n",num);
		}
		//if the amount of money is bigger or equal to 10 then 
		//take the number of time it divide by 10 and then find the 
		//amount that is going to be taken away by time the number of time
		//then take the amount and subtract it to the amount that going to be taken.
		if(amount >= 10){
			int num = amount / 10;
			int taken = 10 * num;
			amount = amount - taken;
			printf("the amount of 10$ you need is %d \n",num);
		}
		//if the amount of money is bigger or equal to 5 then 
		//take the number of time it divide by 5 and then find the 
		//amount that is going to be taken away by time the number of time
		//then take the amount and subtract it to the amount that going to be taken.
		if(amount >= 5){
			int num = amount / 5;
			int taken = 5 * num;
			amount = amount - taken;
			printf("the amount of 5$ you need is %d \n",num);
		}
		//if the amount of money is bigger or equal to 1 then 
		//take the number of time it divide by 1 and then find the 
		//amount that is going to be taken away by time the number of time
		//then take the amount and subtract it to the amount that going to be taken.
		if(amount >= 1){
			int num = amount / 1;
			int taken = 1 * num;
			amount = amount - taken;
			printf("the amount of 1$ you need is %d \n",num);
		}

	}
}








