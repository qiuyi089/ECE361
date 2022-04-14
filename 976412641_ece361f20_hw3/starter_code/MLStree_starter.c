/**
 * MLStree_starter.c - Starter source code file for MLS binary tree
 *
 * Author: Roy Kravitz (roy.kravitz@pdx.edu)
 * Date: 30-Oct-2020
 * 
 * This is starter source code for a binary tree ADT targeted to the
 * MLS standings app (ECE 361 hw3).  You need to develop the four
 * functions that say // ADD CODE HERE
 *
 * @note code is based on the BinarySearchTree example used during
 * the ECE 361 lectures 
 *
 * @note This is a reasonably sized subset of my binary tree ADT.  You
 * can build on this or go in your own direction.  You are the softare
 * engineer on this project.  If you decide to go your own way, it is 
 * in your benefit to preserve the structure of the prototypes in MLStree.harderr
 * because they are used in test_MLStree.c
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLStree.h"
#include "MLSapp_Helpers.h"
 
 /**
 * createMLStree() - creates an MLS tree 
 *
 * @param	cont				Eastern or Western conference
 * @param	numTeams			Number of teams in the conference
 * @param 	numPlayoffTeams		Number of teams qualifying for playoffs
 *
 * @return	a pointer to the new MLStree if it succeeds.  NULL if it fails.
 * root node is NULL to start with because the tree has 0 nodes
 *
 */
 MLStreePtr_t createMLStree(MLSconf_t conf, int numTeams, int numPlayoffTeams) {
	MLStreePtr_t temp;
	
	// allocate space for the new tree
	temp = malloc(sizeof(MLStree_t));
	if (temp == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR(createMLSTree()): Could not allocate space for MLStree\n");
		#endif		
		return NULL;
	}
	
	// initialize the tree struct
	
	// ADD YOUR CODE HERE
	temp -> numTeams = numTeams;
	temp -> numPlayoffTeams = numPlayoffTeams;
	temp -> conf = conf;
	temp -> root = NULL;
	return temp;
}


/**
 * insert() - inserts a new team info record into the tree
 *
 * @param	tree	pointer to the MLStree to add the node to
 * @param	info	team info record to add
 * @return	pointer to the new tree node

 * @note Not a good idea to expose the data node but w/o a pointer to
 * root I don't see much harm and it could be useful...and, in fact, INFO
 * made use of it several times in my application
 */
TreeNodePtr_t insert(MLStreePtr_t tree, TeamInfo_t info) {
	TreeNodePtr_t	 tempNodePtr;		// pointer to a new node
	// make sure there is a tree
	if (tree == NULL) {
		#if (_VERBOSE_ > 0)
			printf("ERROR(insert(): Not a valid MLS tree\n");
		#endif		
		return NULL;
	}
	
	// add and populate the new node to the tree
	// ADD YOUR CODE HERE
	tempNodePtr = (TreeNodePtr_t) malloc(sizeof(TreeNode_t));
	tempNodePtr -> info = info;
	if(tree -> root == NULL){
		tree -> root = tempNodePtr;
		return tree -> root;
	}	
	// insert the node based on the PPG (points per game) because PPG 
	// is being used in the MLS 2020 season to determine the standings.
	// The binary tree should be built with the PPG of the leftChild <
	// PPG of its parent node and the PPG of the rightChild > the PPG of
	// its parent node.
	// Study the sample code provided to design this function
	
	// ADD YOUR CODE HERE
	//Recursive traverse the tree for insertion
	insert_recursion(tree -> root,info);
	return tree -> root;
	
}
/**
*insert_recursion() - insert the information into the tree using recursion
*@param root - The pointer to the root of the tree that hold all the information about the team
*@param info - The pointer to the information that is need to be insert into the tree
*/
TreeNodePtr_t insert_recursion(TreeNodePtr_t root, TeamInfo_t info){
	if(!root){
		TreeNodePtr_t temp = (TreeNodePtr_t) malloc(sizeof(TreeNode_t));
		temp -> info = info;
		temp -> leftChild = NULL;
		temp -> rightChild = NULL;
		return temp;
	}
	if(root -> info.ppg > info.ppg)
		root -> leftChild = insert_recursion(root -> leftChild, info);
	else 
		root -> rightChild = insert_recursion(root -> rightChild, info);
	return root;

}

/**
 * printStandings() - prints the standings (table)
 *
 * @param	tree	pointer to the MLStree to search
 *
 * @note teams that qualify for the playoffs get an x in the first column
 <F7><F8>i*
 * @note function should do a reverse in-order traversal since we want the
 * teams listed from highest PPG to lowest PPG.  
 * Try to mimic the Table entries shown in the hw3_results.txt file.  It's
 * going to take some playing around and likely lots of compiles to get the
 * formatting to where you like it.  That's why writing a makefile for this
 * assignment will be helpful. 
 */
 void printStandings(MLStreePtr_t tree) {
	if(tree == NULL){
		printf("ERROR! There is no tree to print. \n");
		return;
	}
	// Study the sample code to get an idea of how to do a recursive
	// in-order traversal
	
	// ADD YOUR CODE HERE
	int count = 1;
	int * counter = &count;
	printf("  #                               Club         PTS        PPG       GP   W   L   T \n");
	printStandings_recursion(tree -> root,counter,tree -> numPlayoffTeams);	
	printf("x - team has qualified for the playoffs. \n");
}
/**
* printStanding_recursion() - print out the standing using recursion
*@param  root- pointer to the root of the BST tree
*@param  num- increment when printout team in the league
*@param  playoff-  the number of team that can be qualify for the playoff
*/


void printStandings_recursion(TreeNodePtr_t root, int * num,int playoff){
	if(root == NULL)
		return;
	printStandings_recursion(root -> rightChild,num,playoff);
	if(*num <= playoff){
		printf("%3d  x   %30s %10d        %.2f %7d %3d %3d %3d \n",*num,root -> info.name,root -> info.pts, root -> info.ppg,root -> info.gp,root -> info.win, root -> info.loss, root -> info.tie);	
	(*num)++;

	}
	else{ 
		printf("%3d     %30s %11d        %.2f %7d %3d %3d %3d \n",*num,root -> info.name,root -> info.pts, root -> info.ppg,root -> info.gp,root -> info.win, root -> info.loss, root -> info.tie);	
	(*num)++;
	}
	printStandings_recursion(root -> leftChild,num,playoff);
}
/**
* printWinningTeam() - print out the best team in the league
*@param  west - The tree that contain the west side team
*@param  east - The tree that contain the east side team
*/

void printWinningTeam(MLStreePtr_t west, MLStreePtr_t east){
	if(west == NULL || east == NULL){
		printf("One of your Tree is NULL. \n");
	}
	printf("\n");
	TeamInfoPtr_t west_side = findHighest_ppg(west -> root);
	TeamInfoPtr_t east_side = findHighest_ppg(east -> root);

	if(west_side -> ppg > east_side -> ppg){
		printf("Congratulation the MLS 2020 Shield winner - %s \n",west_side -> name);
		printTeamInfo(west_side);
	}
	else{
		printf("Congratulation the MLS 2020 Shield winner - %s \n",east_side -> name);
		printTeamInfo(east_side);	
	}
}
/**
*findHighest_ppg() - find the team with the highest ppg and return back the node that contain it
*@param root - The root of the tree
*/
TeamInfoPtr_t findHighest_ppg(TreeNodePtr_t root){
	if(root == NULL){
		printf("ERROR! There is no tree to traverse \n");
		return NULL;
	}
	if(root -> rightChild == NULL)
		return &root -> info;
	return findHighest_ppg(root -> rightChild);
}








