/**
 * MLSapp_Helpers.c - Source code for binary tree app helper functions
 *
 * Author:	Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 	30-Oct-2020
 * 
 * This is the source code for a few "helper" functions for the
 * MLS app assignment (ece 361 hw 3)
 *
 * @note code is specific to the MSLtree ADT, but it does show
 * a method for parsing a line from a .csv file 
 */
 
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include "MLSapp_Helpers.h"
 
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
			printf("%s\n", buf);
			return NULL;
	}
	else {
		// parse the buffer
		if (strlen(buf) > 0) {
			numFields = sscanf(buf, "%[^,],%d,%d,%f,%d,%d,%d,%d",
				info.name, &conf, &info.pts, &info.ppg, &info.gp,
				&info.win, &info.loss, &info.tie);
				
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
				#if (_VERBOSE_ > 0)
						//printTeamInfo(&info);
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
 /**
*buildMLSTree() - read in the data from the text file and create a tree from it
*@param west_conf - pointer to the west conference tree
*@param east_conf - pointer to the east conference tree
*/
void buildMLSTree(MLStreePtr_t west_conf, MLStreePtr_t east_conf){
	//open the file and read in the data from the text file line by line
	//then loop through the text file to read in each data line and insert it 
	//into the binary tree that is sort by ppg. Check which data is west and east by 
	//if it 0 then it east, 1 for west
	FILE *fp;
	char comment[255];
	char buff[255];
	fp = fopen("MLS2020.txt","r");
	if(fp == NULL){
		printf("ERROR! there is no file that can be open. Program will now exit. \n");
		exit(1);
	}
	printf("\n");
	printf("Reading team info file ./MLS2020.txt... \n");
	fgets(comment,255,(FILE*)fp);
	printf("%s \n",comment);
	while(fgets(buff,255,(FILE*)fp) != NULL){
		TeamInfoPtr_t temp = NULL;
		temp = parseTeamInfo(buff,temp);
		if(temp -> conf == 0){
			insertTeams(east_conf,temp);
			printf("added %s to Eastern Conference \n",temp -> name);
		}
		else{
			insertTeams(west_conf,temp);
			printf("added %s to Western Conference \n",temp -> name);
		}
	}
}
// populates the tree and shows whether the team info was added correctly
void insertTeams(MLStreePtr_t tree,TeamInfoPtr_t info){
	insert(tree,*info);
	return ;
	
}

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
