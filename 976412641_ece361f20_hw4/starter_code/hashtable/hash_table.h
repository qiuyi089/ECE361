/*
 * hash_table.h - Hash table ADT header file
 *
 * Refactored by: Roy Kravitz (roy.kravitz@pdx.edu) in Nov. 2019
 * Modified for the HW #4 Team Info records in Nov 2020
 * Author:  <your name goes here>
 * 
 * This is the header file for constants, variables, structs and function prototypes
 * for functionality in the Hash table ADT    
 *
 * This file, and its associated source code file (including the functions that you
 * need to provide) are based on the code provided by James Routley in his excellent
 * tutorial on Hash tables and hashing (https://github.com/jamesroutley/write-a-hash-table).
 *
 * NOTE:  The Hash table ADT is a clone of James Routhly's code except I refactored it
 * for ECE 361 HW #4 and the TeamInfo_t struct
 *
 * CAVEAT:  I did not implement Routhley's algorithms and code for resizing the Hash table.
 * Instead I made the hash table (hopefully)large enough to hold all of the teams
 * in the team info file.  It would not be that much extra work to add in his support for
 * resizing the Hash table but like so many professors before me, I will leave that
 * as an exercise for the interested reader.
 */

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

// constants
#define NUM_MLS_TEAMS		26
#define HASH_TABLE_SIZE		(NUM_MLS_TEAMS * 1.5)
#define HT_PRIME_1			151
#define HT_PRIME_2			193

#define MAXNAME 30		// maximum length for team name
#define MAXNICKNAME 25	// maximum length for team nickname
 

// Debug constants
// This is a good way to compile debug code into your program as needed and then
// remove it when you have everything working.
// Be sure you use {} in pieces of code that make use of the approach
#define _VERBOSE_ 0		// > 0 compiles in the debug code.
						
// define conference enum
typedef enum _MLSconf_e {EAST, WEST} MLSconf_t;

// define team info struct
typedef struct _mlsTeamInfo_s {
	char 		name[MAXNAME];
	char		nickname[MAXNICKNAME];
	MLSconf_t	conf;
	float		ppg;
	int			pts;
	int			gp;
	int			win;
	int			loss;
	int			tie;
} TeamInfo_t, *TeamInfoPtr_t;

// struct containing key:value (k:v) pairs
typedef struct ht_item {
    char* key;
    void* value;
} ht_item;

// struct containing the hash table
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;


// API function prototypes

// creates a new hash table
ht_hash_table* ht_new(void);

// deletes a hash table
void ht_del_hash_table(ht_hash_table* ht);

// inserts element into hash table
void ht_insert(ht_hash_table* ht, const char* key, void* value);

// searches for element in the hash table
void* ht_search(ht_hash_table* ht, const char* key);

// deletes an element from the hash table
void ht_delete(ht_hash_table* ht, const char* key);

// displays the entire hash table on stdout
void ht_dump(ht_hash_table* ht);
//creating the hash table from parsing
void build_ht(ht_hash_table * table);
//chech for correct nickname and if it exist return back the team
TeamInfoPtr_t find_team(ht_hash_table *ht, char * name, char conf);

#endif
