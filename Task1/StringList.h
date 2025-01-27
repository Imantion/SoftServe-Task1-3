#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Initializes list */
void StringListInit(void*** list);
/* Destroy list and set pointer to NULL. */
void StringListDestroy(void*** list);

/* Inserts value at the end of the list. */
void StringListAdd(void** list, const char* str);
/* Removes all occurrences of str in the list. */
void StringListRemove(void*** list, const char* str);

void PrintList(void** list);

/* Returns the number of items in the list. */
int StringListSize(void** list);

/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(void** list, char* str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(void*** list);
/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(void** list, const char* before, const char* after);
/* Sorts the list of strings in ascending order */
void StringListSort(void*** list);
