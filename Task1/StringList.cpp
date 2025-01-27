#include "StringList.h"

void StringListInit(void*** list)
{
	if (list == NULL) return;


	*list = (void**)malloc(sizeof(void*) * 2);
	(*list)[0] = NULL;
	(*list)[1] = NULL;
}

static void freeRecursive(void** pointer) {

	if (pointer[1] != NULL)
		freeRecursive((void**)pointer[1]);

	free(pointer[0]);
	free(pointer);
}

void StringListDestroy(void*** list)
{
	if (list == NULL) return;
	
	freeRecursive(*list);

	*list = NULL;
}

/* Inserts value at the end of the list */
void StringListAdd(void** list, const char* str) {

	if (list == NULL) 
		throw "List is not intialized";

	if (list[0] == NULL)
	{
		list[0] = _strdup(str);
		return;
	}

	void** iterator = list;
	while (iterator[1] != NULL)
	{
		iterator = (void**)iterator[1];
	}
	
	void** next = (void**)malloc(sizeof(void*) * 2);

	next[0] = _strdup(str);
	next[1] = NULL;

	iterator[1] = next;
}

void StringListRemove(void*** list, const char* str)
{
	if (list == NULL)
		throw "List is NULL";
	void** iterator = *list;
	void** previous = NULL;
	while (iterator != NULL)
	{
		if (strcmp((char*)iterator[0], str) == 0)
		{
			if (previous == NULL)
			{
				*list = (void**)iterator[1];
				free(iterator[0]);
				free(iterator);
				iterator = *list;
			}
			else
			{
				previous[1] = iterator[1];
				free(iterator[0]);
				free(iterator);
				iterator = (void**)previous[1];
			}
		}
		else
		{
			previous = iterator;
			iterator = (void**)iterator[1];
		}
	}
}

void PrintList(void** list)
{
	if (list == NULL)
		return;

	void** iterator = list;
	while (iterator != NULL)
	{
		printf("%s ", (char*)iterator[0]);
		iterator = (void**)iterator[1];
	}
	printf("\n");
}

int StringListSize(void** list)
{
	int size = 0;

	void** iterator = list;
	while (iterator != NULL)
	{
		size++;
		iterator = (void**)iterator[1];
	}

	return size;
}

int StringListIndexOf(void** list, char* str)
{
	void** iterator = list;
	int index = 0;

	while (iterator != NULL)
	{
		if (strcmp((char*)iterator[0], str) == 0)
			return index;
		index++;
		iterator = (void**)iterator[1];
	}

	return -1;
}

void StringListRemoveDuplicates(void*** list)
{
	if (list == NULL)
		throw "List is NULL";

	void** iterator = *list;
	while (iterator != NULL)
	{
		void** innerIterator = (void**)iterator[1];
		void** previous = iterator;
		while (innerIterator != NULL)
		{
			if (strcmp((char*)iterator[0], (char*)innerIterator[0]) == 0)
			{
				previous[1] = innerIterator[1];
				free(innerIterator[0]);
				free(innerIterator);
				innerIterator = (void**)previous[1];
			}
			else
			{
				previous = innerIterator;
				innerIterator = (void**)innerIterator[1];
			}
		}
		iterator = (void**)iterator[1];
	}
}

void StringListReplaceInStrings(void** list, const char* before, const char* after)
{
	if (list == NULL)
		throw "List is NULL";

	void** iterator = list;
	while (iterator != NULL)
	{
		
		if (char* subStrPosition = strstr((char*)iterator[0], before))
		{
			size_t newLength = strlen((char*)iterator[0]) - strlen(before) + strlen(after) + 1;
			size_t prefixLength = subStrPosition - (char*)iterator[0];
			size_t suffixLength = strlen(subStrPosition + strlen(before));


			char* newString = (char*)malloc(newLength);
			strncpy_s(newString, newLength, (char*)iterator[0], prefixLength);
			strcat_s(newString, newLength, after);
			strcat_s(newString, newLength, subStrPosition + strlen(before));
			free(iterator[0]);
			iterator[0] = newString;
		}

		iterator = (void**)iterator[1];
	}
}

void StringListSort(void*** list)
{
	if (list == NULL)
		throw "List is NULL";
	
	int listSize = StringListSize(*list);
	
	for (size_t i = 0; i < listSize - 1; i++)
	{
		void** iterator = *list;
		void** previous = *list;

		for (size_t j = 0; j < listSize - i - 1; j++)
		{
			void** nextIterator = (void**)iterator[1];

			char* d = (char*)previous[0];
			char* a = (char*)iterator[0];
			char* b = (char*)nextIterator[0];

			if (strcmp((char*)iterator[0], (char*)(nextIterator[0])) > 0)
			{
				if(iterator == *list)
				{
					*list = nextIterator;
					iterator[1] = nextIterator[1];
					nextIterator[1] = iterator;
					previous = nextIterator;
				}
				else
				{
					previous[1] = nextIterator;
					iterator[1] = nextIterator[1];
					nextIterator[1] = iterator;
					previous = nextIterator;
				}

				iterator = (void**)nextIterator[1];
			}
			else
			{
				previous = iterator;
				iterator = (void**)iterator[1];
			}
		}
	}
}

