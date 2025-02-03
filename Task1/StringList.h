#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef void** StringList;

enum StringListIndexing
{
	DATA,
	NEXTPTR
};

void StringListInit(StringList* list);
void StringListDestroy(StringList* list);

void StringListAdd(StringList list, const char* str);
void StringListRemove(StringList* list, const char* str);

int StringListSize(StringList list);

int StringListIndexOf(StringList list, const char* str);
char* StringListGetElement(StringList list, int index);

void StringListRemoveDuplicates(StringList* list);
void StringListReplaceInStrings(StringList list, const char* before, const char* after);
void StringListSort(StringList* list);
