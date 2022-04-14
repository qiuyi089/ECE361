/**
 * hw4_MLSapp_Helpers.h - Header file for MLS hash table helper functions
 *
 * @author Roy Kravitz (roy.kravitz@pdx.edu)
 * @date 14-Noc-2020
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
 */
#ifndef _HW4_MLSAPPHELPERS_H
#define _HW4_MLSAPPHELPERS_H
 
#include <stdbool.h>
#include "hash_table.h"

// define constants
#define NUMTEAMINFOFIELDS 9 	// was 8 for Homework #3
#define MAXCONFTEXT 4

// function prototypes
TeamInfoPtr_t parseTeamInfo(const char *buf, TeamInfoPtr_t info_ptr);
void printTeamInfo(TeamInfoPtr_t teamInfo);
char* createKey(TeamInfoPtr_t teamInfoPtr);
void strUpper(char* str);

#endif

 