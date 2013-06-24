/*	 
 *	File: table.c
 *
 *	Description: Implement a set using a hash table of length
 *		     m>0 and linear probing to resolve collisions.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2

 struct set {
	int count;
	int length;
	char **elts;
	char *flags;
};

//return a pointer to a new set with maximum capacity of maxElts

 struct set *createSet(int maxElts)
{
	struct set *sp;
	int i;
	sp=malloc(sizeof(struct set));
		assert(sp!=NULL);

	sp->count=0;
	sp->length=maxElts;

	sp->elts=malloc(sizeof(char*)*maxElts);
		assert(sp->elts!=NULL);

	//allocate memory for the second array where the flags are
	
	sp->flags=malloc(sizeof(char)*maxElts);
		assert(sp->flags!=NULL);

	//set every index in the flag array as empty	

	for(i=0;i < sp->length; i++)
	{
		sp->flags[i]=EMPTY; 
	}

	return sp;
}

//deallocate memory associated with the set pointed to by sp

 void destroySet(struct set *sp)
{

	int i;
	
	//if an index in the flag array is filled, delete it in the data array
	
	for(i=0;i < sp->length; i++)
	{
		if(sp->flags[i]==FILLED)
			free(sp->elts[i]);
	}
		free(sp->elts);	
		free(sp->flags);
		free(sp);
}

//return the number of elements in the set pointed to by sp

 int numElements(struct set *sp)
{
	return sp->count;
}	

//hash function used for search logic

 unsigned hashString(char *s){
	unsigned hash=0;

	while(*s != '\0')
		hash= 31 * hash + *s ++;

	return hash;
}

//return the location of the element in the array

 int findElement(struct set *sp, char *elt, bool *found)
{
	int i, vacant,index;
	unsigned first=hashString(elt);
	
	//use variable vacant to keep track of the nearest empty or deleted index	

	vacant=-1;

	for(i=0;i < sp->length; i++)
	{
		index=(first+i)%(sp->length);
	
	if(sp->flags[index]==DELETED){
		if(vacant==-1)
			vacant=index;
	}

	else if(sp->flags[index]==FILLED){
		if(strcmp(elt,sp->elts[index])==0)
			*found=true;
			return index;
		}

	else {	
		//set found equal to false prior to checking vacant
		*found=false;
		if(vacant!=-1)
			return vacant;
		return index;
	     }
	}
*found=false;
return index;		
}
//return whether elt is a member of the set pointed to by sp

 bool hasElement(struct set *sp, char *elt)
{
	bool found;
	findElement(sp,elt,&found);
	return found;
}

//add elt from the set pointed to by sp, and return whether the set changed
 
 bool addElement(struct set *sp, char *elt)
{
	bool found;
	int index=findElement(sp,elt,&found);
	

	assert(sp!=NULL);
	if(sp->count>=sp->length)
		return false;
	
	//if the element was found return false

	if(found){
		return false;
	}

	//remember to set the flag to FILLED when adding the element

	sp->elts[index]=strdup(elt);
	sp->flags[index]=FILLED;
	sp->count++;
	return true;
	
}

//remove elt from the set pointed to by sp, and return whether the set changed

 bool removeElement(struct set *sp, char *elt)
{
	bool found;
	int index=findElement(sp,elt,&found);
	
	assert(sp!=NULL);

	//if the element was not found return false

	if(!found){
		return false;
	}

	//set the flag pointer to DELETED and then free the elts pointer	

	
		free(sp->elts[index]);
		sp->flags[index]=DELETED;
		sp->count--;
		return true;
}
