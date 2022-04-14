/**
 * test_MLStree.c - Source code file for a simple test program for the MLS binary tree
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 * 
 * This is source code for testing my MLStree binary tree ADT that is
 * used in the MLS standings app (ECE 361 hw3)
 *
 * @note you may have to make some modifications to tailor the test program
 * to your binary tree ADT
 *
 * @note this program tests the three functions you need to create in your
 * binary tree ADT.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLStree.h"
#include "MLSapp_Helpers.h"

// main program
int main() {
	MLStreePtr_t west_conf;
	MLStreePtr_t east_conf;	
	// Western conference has 12 teams, and in this
	// test program the top two teams qualify for the playoffs
	west_conf = createMLStree(WEST, 12, 8);
	east_conf = createMLStree(EAST,14,10);
	buildMLSTree(west_conf,east_conf);
	//Print out the team standing and the winner of the league
	printf("\n");	
	printf("The current standing are: \n");
	printf("Eastern Conference: \n");
	printStandings(east_conf);
	printf("\n");
	printf("Western Conference: \n");
	printStandings(west_conf);
	printWinningTeam(west_conf, east_conf);	
}




