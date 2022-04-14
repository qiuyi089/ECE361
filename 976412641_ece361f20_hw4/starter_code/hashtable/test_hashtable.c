/**
 * test_hashtable.c - Test program for the Hash table ADT
 *
 * @author	Roy Kravitz (roy.kravitz@pdx.edu)
 * @date	14-Nov-2020	
 * 
 * This is the source code file for a  test program for a Hash Table ADT.
 * Although it shouldn't matter as long as the API doesn't change, this
 * test is based on James Routley's open addressing/double hashing hash
 * table ADT (https://github.com/jamesroutley/write-a-hash-table)
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"
#include "hw4_MLSapp_Helpers.h"

int main(){
	ht_hash_table* teams_ht;// hash table
	printf("Hash Table ADT test program (by Roy Kravitz, 14-Nov-2020)\n\n");
	// create a hash table
	teams_ht = ht_new();
	if (teams_ht != NULL) {
		printf("INFO(main()): Created a new hash table\n");
	}
	else {
		printf("EROR(main()): Could not create a new hash table\n");
		exit(1);
	}
	build_ht(teams_ht);//insert the data into the hash table
	ht_dump(teams_ht);//display the hash table after the data have been added	
	int loops = 1;//looping condition
	char confer[3];//take in the conference
	char buffer;//temp char that going to take in the \n that the buffer leave when the user input
	while(loops == 1){
		//keep looping and ask the user for their input
		//check if the user input is a valid one or not 
		//if it valid then start searching for the team that the user want
		//else display an error message and end the loop
		//if the user press enter without input anything then exit or if they press q or Q
		printf("Enter 0 to select Eastern conference, 1 to select Western conference, ? to list the hash table contents: ");
		fgets(confer,3,stdin);
		if(confer[0] == '1' || confer[0] == '0' || confer[0] == '?'){
			if(confer[0] == '?'){
				ht_dump(teams_ht);
			}
			else if(confer[0] == '1'){
				char name[30];
				printf("Enter the nickname for a team in the Western conference: ");
				scanf("%s",name);
				buffer = getchar();
				TeamInfoPtr_t temp = find_team(teams_ht,name,confer[0]);
			}
			else{
				char name[30];
				printf("Enter the nickname for a team in the Eastern conference: ");
				scanf("%s",name);
				buffer = getchar();
				TeamInfoPtr_t temp = find_team(teams_ht,name,confer[0]);
			}
		}
		else{
			if(confer[0] == 'q' || confer[0] == 'Q' || confer[0] == '\n'){
				loops = 0;
			}
			else
				printf("INVALID input of %c \n",confer[0]);
		}
	}
	// delete the entire hash table
	printf("Deleting Hash Table\n");
	ht_del_hash_table(teams_ht);

	return 0;
}































