/*
 * hash_table.c - Hash table ADT source code file
 *
 * Refactored by: Roy Kravitz (roy.kravitz@pdx.edu) in Nov. 2019
 * Modified for the HW #4 Team Info records in Nov 2020
 * Author:  <your name goes here>
 *
 * This is the source code file for the functionality in the Hash table ADT
 *
 * This file, and its associated header file are generated from the code provided by James
 * Routley in his excellent tutorial on Hash tables and hashing (https://github.com/jamesroutley/write-a-hash-table).
 *
 *
 * CAVEAT:  I did not implement Routley's algorithms and code for resizing the Hash table.
 * Instead I made the hash table (hopefully)large enough to hold all of the teams in
 * the team info file.  It would not be that much extra work to add in his support for
 * resizing the Hash table but like so many professors before me, I will leave that
 * as an exercise for the interested reader.
 */

// include the header files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"
#include "hw4_MLSapp_Helpers.h"


// constants, typedefs and global variables
static ht_item HT_DELETED_ITEM = {NULL, NULL};

// prototypes for the Helper functions

// create a new element for the hash table
static ht_item* ht_new_item(const char* k, void*  v);

// delete an element from the hash table
static void ht_del_item(ht_item* i);

  // generic hash function
static int ht_generic_hash(const char* s, const int a, const int m);

// actual hash function
static int ht_get_hash(const char* s, const int num_buckets, const int attempt);

// Hash Table ADT

/**
 * ht_new() - initializes a new Hash table
 *
 * Allocates space for a new hash table.  The size of the array is fixed in
 * this implementation
 *
 * @returns a pointer to the new hash table
 *
 * @note
 * We initialize the array of items with `calloc`, which fills the allocated memory
 * with `NULL` bytes. A `NULL` entry in the array indicates that the bucket is empty.
 */
ht_hash_table* ht_new(void) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
	if (ht == NULL) {
		#if (_VERBOSE_ > 0)
			fprintf(stderr,
				"ERROR(ht_new()): Could not allocate space for hash table\n");
		#endif
		return NULL;
	}

	// allocated space for hash table, now get space for all of the elements in the hash table
    ht->size = HASH_TABLE_SIZE;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
	if (ht->items == NULL) {
		#if (_VERBOSE_ > 0)
			fprintf(stderr,
				"ERROR(ht_new()): Could not allocate elements for the hash table\n");
		#endif
		return NULL;
	}
    return ht;
}


/**
 * ht_del_hash_table() - deletes an entire hash table
 *
 * Deletes all of the elements in the hash table and frees up their memory
 * After the elements are deleted the table, itself is deleted
 *
 * @param	ht is a pointer to the Hash table that should be deleted
 *
 */
void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if ((item != NULL) && (item != &HT_DELETED_ITEM)) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}


/**
 * ht_insert() - insert a new key-value pair into hash table
 *
 * To insert a new key-value pair, we iterate through indexes until we find an empty bucket.
 * We then insert the item into that bucket and increment the hash table's
 * `count` attribute, to indicate a new item has been added.
 *
 * @param ht is a pointer to a Hash table created with the ht_new() function
 * @param key is a pointer to a string containing the key
 * @param value is a void pointer to what we want to insert into the hash table
 *
 */
void ht_insert(ht_hash_table* ht, const char* key, void* value) {
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;

    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
		if (strcmp(cur_item->key, key) == 0) {  // support updating keys
            ht->items[index] = item;
            return;
        }
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;

	#if (_VERBOSE_ > 0)
		fprintf(stderr,
			"\tINFO(ht_insert()): Inserted hash table[%d], k:v = %s:%p\n",
			index, item->key, item->value);
	#endif

    ht->count++;
}


/**
 * ht_search() - search the hash table for an element with the specified key
 *
 * Searching is similar to inserting, but at each iteration of the `while` loop,
 * we check whether the item's key matches the key we're searching for. If it does,
 * we return the item's value. If the while loop hits a `NULL` bucket, we return`NULL`
 * to indicate that no value was found.
 *
 * @param ht is a pointer to a Hash table created with the ht_new() function
 * @param key is a pointer to a string containing the key
 *
 * @returns value as a void*
 */
void* ht_search(ht_hash_table* ht, const char* key) {
	int index;
	ht_item* item;
	int i;

	#if (_VERBOSE_ > 0)
		fprintf(stderr,
			"\tINFO(ht_search()): Searching for key: %s\n",
			key);
		#endif


    index = ht_get_hash(key, ht->size, 0);
    item = ht->items[index];
	i = 1;
    while (item != NULL && item != &HT_DELETED_ITEM) {
        if (strcmp(item->key, key) == 0) {
			#if (_VERBOSE_ > 0)
				fprintf(stderr,
					"\tINFO(ht_search()): Found key %s in bucket: %d at address %p\n",
					key, index, item->value);
			#endif
			return item->value;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }

	#if (_VERBOSE_ > 0)
		fprintf(stderr,
			"\tINFO(ht_search()): key: %s is not in the hash table\n",
			key);
		#endif
    return NULL;
}


/* ht_delete() - delete an element from the hash table
 *
 * Deleting from an open addressed hash table is more complicated than inserting
 * or searching. The item we wish to delete may be part of a collision chain.
 * Removing it from the table will break that chain, and will make finding items in
 * the tail of the chain impossible.
 *
 * To solve this, instead of deleting the item, we simply mark it as deleted.
 * We mark an item as deleted by replacing it with a pointer to a global sentinel
 * item which represents that a bucket contains a deleted item.
 *
 * @param ht is a pointer to a Hash table created with the ht_new() function
 * @param key is a pointer to a string containing the key
 *
 */
void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;

    while (item != NULL && item != &HT_DELETED_ITEM) {
        if (strcmp(item->key, key) == 0) {
            ht_del_item(item);
            ht->items[index] = &HT_DELETED_ITEM;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}


/**
 * ht_dump() - dumps (lists) the entire hash table to the console
 *
 * Traverses the entire hash table displaying the key and value for
 * every occupied bucket in the hash table.  Empty ('.') and deleted ("delete")
 * buckets are noted
 *
 * @param	ht is a pointer to the Hash table that should be deleted
 *
 */
void ht_dump(ht_hash_table* ht) {
	printf("Hash table contains:\n");
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item == NULL) {
            printf(".");
        }
		else if (item == &HT_DELETED_ITEM) {
			printf("\n\tHash Table[%02d] has been deleted\n", i);
		}
		else {
			printf("\n\tHash Table[%02d] has k:v = %s:%p", i, item->key, item->value);
		}
    }
	printf("\n");
}



// Helper functions

/**
 * ht_new_item() - allocate a new element for the hash table
 *
 * Allocates a chunk of memory the size of an `ht_item` and saves a copy of the
 * key and value pair in the new chunk of memory.
 *
 * @param k is a pointer to the string containing the key for the element
 * @param v is a pointer to a team Info record
 *
 * @returns a pointer to the new element
 *
 * @note
 * The function is declared `static` because it will only be called by code internal to the hash table.
 */
static ht_item* ht_new_item(const char* k, void*  v) {
    ht_item* i = malloc(sizeof(ht_item));
	if (i == NULL) {
		#if (_VERBOSE_ > 0)
		fprintf(stderr,
			"ERROR (ht_item()):  Could not allocate a new item\n");
		#endif
		return NULL;
	}

	// alas, if only there was a strdup() function in the string library..do this instead
	char* d = malloc(strlen(k) + 1);
	i->key = strcpy(d, k);
	i -> value = malloc(sizeof(TeamInfo_t));
	memcpy(i -> value,v,sizeof(TeamInfo_t));
    return i;
}



/**
 * ht_del_item() - deletes an element from the hash table
 *
 * Deletes the specified element from the hash table.  Frees up the memory
 * for the key and the value and the hash+item.
 *
 * @param	i is a pointer to the ht_item that should be deleted
 *
 * @note
 * The function is declared `static` because it will only be called by code internal to the hash table
 */
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}


/**
 * ht_generic_hash() -  generic Hash function
 *
 * Applies a generic hash function for character strings.  Produces an index into
 * the Hash table.  The algorithm works by creating a large integer from scanning each
 * character in the string and then using the modulus (%) operator to reduce the number so that it fits into the table.
 *
 * @param s is the key for the hash table element
 * @param a is a prime number larger than the size of the alphabet (> 128).
 * @param m is the number of elements (the size) in the Hash table
 *
 * @returns the value calculated by the function.  This generic function is used
 * in this implementation for generating the primary hash and the secondary hash that is
 * used if the first hash results in collision.
 *
 */
static int ht_generic_hash(const char* s, const int a, const int m) {
    long hash = 0;

    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}


/**
 * ht_get_hash() -  gets the index for a key by employing a double hashing algorithm
 *
 * The hashing function that returns the index into the hash table.  Collision handling
 * is handled by double hashing.  That is, a secondary hashing function is used to select
 * the next bucket in the hash table for that index if applying the first hashing
 * function results in a collision.
 *
 * @param s is the key for the Hash table element
 * @param num_buckets is the number of buckets in the Hash table
 * @param attempt is the number of attempts to find the correct bucket for the key
 *
 * @returns the value calculated by the function.
 *
 */
static int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_generic_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_generic_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}
/**
 * build_ht() - read in the information from file to table
 *
 *This build function read in the MLS team information from the text file
 *and then create a table and put the team into the table. It will loops
 *until there is not more data to be read from the file using the fp function.
 *It will create a temp structure and store the information in that temp struct
 *then it will pass that temp to the ht_insert() that already build in to put the 
 *information into the table
 *
 *@param table is the pointer to the hash table that store the team information
 *
 */
void build_ht(ht_hash_table * table){
	FILE * fp;
	char buff[255];
	fp = fopen("hw4_MLS2020.txt","r");
	if(fp == NULL){
		printf("ERROR! there is no file that can be open. Program will now exit. \n");
		exit(1);
	}
	TeamInfoPtr_t temp;
	int i = 0;
	int comment_count = 0;
	while(fgets(buff,255,(FILE*)fp) != NULL){
		temp = parseTeamInfo(buff,temp);
		if(comment_count >= 3){
			char * key = createKey(temp);
			printf("Added %s ,temp is not NULL\n",temp->name);
			ht_insert(table,key,temp);
		}
	   i++;
	   comment_count++;
	}
	fclose(fp);
	printf("Finish reading in the team. \n");
}
/**
 * find_team() - find the team that match with the key and print the team
 *
 *This function will find the team that the user want by create a key with the name that the user enter in
 *and the conference side that the user input. It will generate a key base on this and then using the key
 *it will call ht_search() function that is already been build in and implement to find the right team
 *with the given key. Once it find the right team it will then check if the team is not in the hash table 
 *if the team is in the hash table then it will display otherwise it will display an error message.
 *
 *
 *@param ht - the hash table where all the team information is being kept 
 *@param name - the name of the team that the user want to search
 *@param conf - the conference side that the team is on
 *
 */


TeamInfoPtr_t find_team(ht_hash_table * ht,char * name,char conf){
	TeamInfoPtr_t temp = (TeamInfoPtr_t)malloc(sizeof(TeamInfo_t));
	strcpy(temp -> nickname,name);
	if(conf == '1')
		temp -> conf = 1;
	else
		temp -> conf = 0;
	char * key = createKey(temp);
	TeamInfoPtr_t temp2 = ht_search(ht,key);
	if(temp2 == NULL || temp2 -> conf != temp -> conf)
		printf("The team you looking for isn't exist. \n");
	else{
		printTeamInfo(temp2);
	}	
	return NULL;
}















