/*
 * File:        set.h
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for strings.  A
 *              set is an unordered collection of distinct elements.
 */

struct set *createSet(int maxElts);

void destroySet(struct set *sp);

int numElements(struct set *sp);

bool hasElement(struct set *sp, char *elt);

bool addElement(struct set *sp, char *elt);

bool removeElement(struct set *sp, char *elt);
