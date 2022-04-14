#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Color{
	char hex[10];
	char name[30];
}color_t,*colorPtr;

/**
 *compare() - this function compare the name and return back the result
 *
 *It compare the 2 name of the structure and return back the result
 *1 for color1 is bigger
 *-1 for color 1 is less than
 *0 if they both are equal to each other
 *The function use strcmp to compare the 2 string 
 *
 *@param color1 - a void type pointer that can be typecast to the char pointer that point to the key
 *@param color2 - a void type pointer that can be typecast to color struct
 *
 */
int compare2(const void* color1, const void* color2){
	const colorPtr ptr = (colorPtr)color2;
	return strcmp((const char*)color1,ptr -> name);
}

/**
 *compare_structure() - it will be like the compare() above but this is use to compare the 2 structure
 *
 *The function work like the compare above it but it will return back the difference between 2 structure
 *
 *@param struct1 - a void pointer that can be type cast into what we want
 *@param struct2 - a void pointer that can be type cast into what we want also
 */

int compare(const void * struct1, const void * struct2){
	colorPtr ptr1 = ((colorPtr)struct1); 	
	colorPtr ptr2 = ((colorPtr)struct2);
	return strcmp(ptr1 -> name,ptr2 -> name); 
}

/**
 *insert_color() - insert all the color in the table into an array of struct
 *
 *This function will take in an array of struct and then manually put in the data 
 *for each of the array memeber. It will use strcpy() to copy the data into the array member
 *
 *@param color[] - an array of color struct
 *
 */

void insert_color(color_t color[]){
	strcpy(color[0].name,"black");
	strcpy(color[0].hex,"#000000");

	strcpy(color[1].name,"dark gray");
	strcpy(color[1].hex,"#555555");

	strcpy(color[2].name,"blue");
	strcpy(color[2].hex,"#0000AA");

	strcpy(color[3].name,"light blue");
	strcpy(color[3].hex,"#5555FF");

	strcpy(color[4].name,"green");
	strcpy(color[4].hex,"#00AA00");

	strcpy(color[5].name,"light green");
	strcpy(color[5].hex,"#55FF55");

	strcpy(color[6].name,"cyan");
	strcpy(color[6].hex,"#00AAAA");

	strcpy(color[7].name,"light cyan");
	strcpy(color[7].hex,"#55FFFF");

	strcpy(color[8].name,"red");
	strcpy(color[8].hex,"#AA0000");
	
	strcpy(color[9].name,"light red");
	strcpy(color[9].hex,"#FF5555");
	
	strcpy(color[10].name,"magenta");
	strcpy(color[10].hex,"#AA00AA");
	
	strcpy(color[11].name,"light magenta");
	strcpy(color[11].hex,"#FF55FF");
	
	strcpy(color[12].name,"brown");
	strcpy(color[12].hex,"#AA5500");
	
	strcpy(color[13].name,"yellow");
	strcpy(color[13].hex,"#FFFF55");
	
	strcpy(color[14].name,"light gray");
	strcpy(color[14].hex,"#AAAAAA");
	
	strcpy(color[15].name,"white");
	strcpy(color[15].hex,"#FFFFFF");
}


int main(){
	color_t color_table[16];//array of struct
	insert_color(color_table);
	//print out the array before it was sorted
	printf("Before sorted \n");
	for(int i = 0;i < 16;i++){
		printf("the color is %s and the hex of it is %s \n",color_table[i].name, color_table[i].hex);
	}
	qsort(color_table,16,sizeof(color_table[0]),compare);//qsort function
	printf("\n");
	//print out the array after the sort function
	printf("After sorted \n");
	for(int i = 0;i < 16;i++){
		printf("the color is %s and the hex of it is %s \n",color_table[i].name, color_table[i].hex);
	}
	color_t user_input;
	int loop = 1;
	//keep on looping and asking the user what the color they want to search
	//if they press enter without input or q or Q then end the loop
	//else search up the color they want suing the bsearch function and print out the hex value
	while(loop == 1){
		printf("\n");
		printf("What is the color you want to search for: ");
		fgets(user_input.name,30,stdin);
		if(user_input.name[0] == '\n'){
			loop = 0;
			exit(0);
		}
		else if(user_input.name[0] == 'q' || user_input.name[0] == 'Q'){
			loop = 0;
			exit(0);
		}
		//replace the new line with \0 in the array
		int length = strlen(user_input.name);
		if(user_input.name[length - 1] == '\n')
			user_input.name[--length] = '\0';
		//search for the item with bsearch()
		char * item_hex = (char*)bsearch(user_input.name,color_table,16,sizeof(color_table[0]),compare2);
		if(item_hex != NULL){
			printf("The color that your search for is %s and it hex value is %s \n",user_input.name,item_hex);
		}
		else
			printf("The color you searching for isn't in the table \n");
	}
	return 0;
}







