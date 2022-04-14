/**
 * hw4_MLSapp_Helpers.c - Source code for for MLS hash table helper functions
 *
 * @author	Roy Kravitz (roy.kravitz@pdx.edu)
 * @date 	14-Nov-2020
 * 
 * This is the header file for a few "helper" functions for the
 * hash table-based MLS app assignment (ECE 361 HW #4)
 *
 * @note Modified from HW #3 Helper files to accommodate the additional
 * "nickname" field of the TeamInfo_t record.
 *
 * @note: You do not need to utilize this file or the functions in the source
 * code file.  I have included them because they are used in the test_hashtable.c_str
 * program included with the release.   These are starter code files - you will need
 * to complete the missing functions.
 *
 */
 
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <ctype.h>
 #include "hw4_MLSapp_Helpers.h"

 // THIS IS THE HOMEWORK #3 VERSION
 // MODIFY THIS FUNCTION TO PROCESS THE ADDITIONAL STRING CONTAINING THE NICKNAME
 // NICKNAME IS A STRING (%s) appended to the end of buf.
 /**
 * parseTeamInfo() - parses a buffer to create a Team Info record
 *
 * @param	buf			buffer to parseTeamInfo
 * @param	into_ptr	pointer to TeamInfo struct.  Pass NULL if
 *						you don't want the data passed back this way 
 * @return	pointer to a TeamInfo struct
 *
 * @note the TeamInfo record is static so that its reference
 * "lives" past the return. Automatic variables are allocated on the stack
 * which does not persist after the function returns.  However, this means
 * that it will only contain the fields from the last time the function was
 * called.  Normally
 * this is OK, but if you need to preserve the record between calls to the function
 * you need to stash the record somewhere before you call parseTeamInfo() again
 * or return it through info_ptr.
 *
 * @note Yes, the prototype of this function looks a bit odd since
 * there are two ways to return the TeamInfo data.  A pointer to
 * the record is returned from the function, but as the previous note
 * says, the record will be overwritten the next time you call
 * parseTeamInfo().  The record is also returned in the Team Info struct pointed
 * to by info_ptr.  Either approach works.  I did this because a) the
 * approach is not unusual in the C library API so it is good to expose it
 * to you and b) many of you seemed put off by the exam question that did
 * the same thing so, you have the choice.  Tomato...Tomaahto.
 */
 TeamInfoPtr_t parseTeamInfo(const char *buf, TeamInfoPtr_t info_ptr){
	static TeamInfo_t 	info;		// will point to a team info record
	int					numFields;	// number of fields parsed by scanf
	int					conf;		// 0 for Eastern, 1 for Western conferences
	// comments in the file start with // and should be displayed
	if ((buf[0] == '/') && (buf[1] == '/'))  {
			printf("%s", buf);
			return NULL;
	}
	else {
		// parse the buffer
		if (strlen(buf) > 0) {
			numFields = sscanf(buf, "%[^,],%d,%d,%f,%d,%d,%d,%d,%s",
				info.name, &conf, &info.pts, &info.ppg, &info.gp,
				&info.win, &info.loss, &info.tie,info.nickname);
				
			// determine the conference
			if (conf == 0)
				info.conf = EAST;
			else
				info.conf = WEST;
			
			if (numFields != NUMTEAMINFOFIELDS) {
				// parsing error
				printf("ERROR(parseTeamInfo()): could not parse record");
				printf("\tnumber of fields parsed = %d\n%s\n",
					numFields, buf);
				return NULL;
			}
			else {
				#if (_VERBOSE_ > 1)
					printTeamInfo(&info);
				#endif	 
				if (info_ptr != NULL) { // copy the TeamInfo struct 
					*info_ptr = info;
				}
				return &info;
			}		
		}
	}
	return NULL;
 }
 
 
 // THIS IS THE HOMEWORK #3 VERSION
 // MODIFY THIS FUNCTION TO DISPLAYTHE ADDITIONAL STRING CONTAINING THE NICKNAME
 // THIS FIELD IS teamInfo->nickname.
 /**
 * printTeamInfo() - prints a Team Info record
 *
 * @param	TeamInfo record to display.
 *
 */
 void printTeamInfo(TeamInfoPtr_t teamInfo) {
	if (teamInfo != NULL) {
		printf("\n");
		printf("Team Information for the %s:\n", teamInfo->name);
		printf("\tConference: %s\n", (teamInfo->conf == EAST ? "Eastern" : "Western"));
		printf("\tPoints per game (PPG): %5.2f\n", teamInfo->ppg);
		printf("\tTotal points (PTS): %d\n", teamInfo->pts);
		printf("\tNumber of games (GP): %d\n", teamInfo->gp);
		printf("\tRecord (w-l-t): %d-%d-%d\n", teamInfo->win, teamInfo->loss,
			teamInfo->tie);
	}
	else {
		printf("ERROR(printTeamInfo()): TeamInfo pointer is NULL\n");
	}
	printf("----------------------\n");
}

// YOU NEED TO WRITE THIS FUNCTION
// THE KEY IS A CONCATENATION OF <NICKNAME><"EAST" OR "WEST">
// EXAMPLE:  PORTLAND TIMBERS KEY IS "PTFCWEST"
/**
 * createKey() - Creates a key for a team info record.
 *
 * The function generate a key for a key:value pair that will be inserted into a hash table
 * This is for ECE 361 HW #4.   The key is the concatenation of the nickname and the
 * conference the team plays in (ex: PTFCWEST for the Portland Timbers of the
 * Western conference)
 *
 * @param name      (pointer to a team info record
 *
 * @returns         a pointer to a character string containing the key for a hash table
 */
char* createKey(TeamInfoPtr_t teamInfoPtr) {
	//TODO:  WRITE THIS FUNCTION
	if(teamInfoPtr -> conf == 0){
		char * temp = (char*)malloc(strlen(teamInfoPtr -> nickname) + 5);
		strUpper(teamInfoPtr -> nickname);
		strcpy(temp,teamInfoPtr -> nickname);
		char * temp2 = "EAST";
		strcat(temp,temp2);
		return temp;
	}
	else {
		char * temp = (char*)malloc(strlen(teamInfoPtr -> nickname) + 5);
		strUpper(teamInfoPtr -> nickname);
		strcpy(temp,teamInfoPtr -> nickname);
		char * temp2 = "WEST";
		strcat(temp,temp2);
		return temp;
	}
	return NULL;
} 


// HERE'S A "FREEBIE"
 /**
 * strUpper() - converts the characters of a string to uppercase
 *
 * @param	char* is a pointer to the character string to convert
 *
 * @note: Based on, but not exactly the same as
 * https://stackoverflow.com/questions/33086007/c-string-to-uppercase-in-c-and-c
 *
 */
void strUpper(char* str) {
    while (*str != '\0')
    {
        *str = (char) toupper((int) *str);
        str++;
    }
}
