#include "StringList.h"

#include <stdexcept>

void StringListInit(StringList* list)
{
    if (list == nullptr)
        throw std::invalid_argument("List is null");

    *list = (StringList)malloc(sizeof(void*) * 2);

    if (*list == nullptr)
        throw std::bad_alloc();

    (*list)[DATA] = nullptr;
    (*list)[NEXTPTR] = nullptr;
}

static void freeRecursive(StringList pointer)
{
    if (pointer[NEXTPTR] != nullptr)
        freeRecursive((StringList)pointer[NEXTPTR]);

    free(pointer[DATA]);
    free(pointer);
}

void StringListDestroy(StringList* list)
{
    if (list == nullptr) return;

    freeRecursive(*list);

    *list = nullptr;
}

void StringListAdd(StringList list, const char* str)
{
    if (list == nullptr)
        throw std::invalid_argument("List is not initialized");

    if (list[DATA] == nullptr)
    {
        list[DATA] = _strdup(str);
        return;
    }

    StringList iterator = list;
    while (iterator[NEXTPTR] != nullptr)
    {
        iterator = (StringList)iterator[NEXTPTR];
    }

    StringList next = (StringList)malloc(sizeof(void*) * 2);

	if (next == nullptr)
		throw std::bad_alloc();

    next[DATA] = _strdup(str);
    next[NEXTPTR] = nullptr;

    iterator[NEXTPTR] = next;
}

void StringListRemove(StringList* list, const char* str)
{
    if (list == nullptr)
        throw std::invalid_argument("List is nullptr");

    StringList iterator = *list;
    StringList previous = nullptr;

    while (iterator != nullptr)
    {
        if (strcmp((char*)iterator[DATA], str) == 0)
        {
            if (previous == nullptr)
            {
                *list = (StringList)iterator[NEXTPTR];
                free(iterator[DATA]);
                free(iterator);
                iterator = *list;
            }
            else
            {
                previous[NEXTPTR] = iterator[NEXTPTR];
                free(iterator[DATA]);
                free(iterator);
                iterator = (StringList)previous[NEXTPTR];
            }
        }
        else
        {
            previous = iterator;
            iterator = (StringList)iterator[NEXTPTR];
        }
    }
}

int StringListSize(StringList list)
{
    if (list == nullptr)
        throw std::invalid_argument("List is nullptr");

    int size = 0;

    StringList iterator = list;
    while (iterator != nullptr)
    {
        size++;
        iterator = (StringList)iterator[NEXTPTR];
    }

    return size;
}

int StringListIndexOf(StringList list, const char* str)
{
    if (list == nullptr)
        throw std::invalid_argument("List is nullptr");

    StringList iterator = list;
    int index = 0;

    while (iterator != nullptr)
    {
        if (strcmp((char*)iterator[DATA], str) == 0)
            return index;
        index++;
        iterator = (StringList)iterator[NEXTPTR];
    }

    return -1;
}

char* StringListGetElement(StringList list, int index)
{
    if (list == nullptr)
        throw std::invalid_argument("List is nullptr");

    StringList iterator = list;

    for (size_t i = 0; i <= index; i++)
    {
        if (iterator == nullptr)
            throw std::out_of_range("Index out of range");

        if (i == index)
            return (char*)iterator[DATA];

        iterator = (StringList)iterator[NEXTPTR];
    }

	return nullptr;
}

void StringListRemoveDuplicates(StringList* list)
{
    if (list == nullptr)
        throw std::invalid_argument("List is nullptr");

    StringList iterator = *list;
    while (iterator != nullptr)
    {
        StringList innerIterator = (StringList)iterator[NEXTPTR];
        StringList previous = iterator;
        while (innerIterator != nullptr)
        {
            if (strcmp((char*)iterator[DATA], (char*)innerIterator[DATA]) == 0)
            {
                previous[NEXTPTR] = innerIterator[NEXTPTR];
                free(innerIterator[DATA]);
                free(innerIterator);
                innerIterator = (StringList)previous[NEXTPTR];
            }
            else
            {
                previous = innerIterator;
                innerIterator = (StringList)innerIterator[NEXTPTR];
            }
        }
        iterator = (StringList)iterator[NEXTPTR];
    }
}

void StringListReplaceInStrings(StringList list, const char* before, const char* after)
{
    if (list == nullptr)
        throw std::invalid_argument("List is nullptr");

    StringList iterator = list;
    while (iterator != nullptr)
    {
        if (char* subStrPosition = strstr((char*)iterator[DATA], before))
        {
            size_t newSubStrLength = strlen(after);
			size_t oldSubStrLength = strlen(before);
            size_t newLength = strlen((char*)iterator[DATA]) - oldSubStrLength + newSubStrLength + 1;
            size_t prefixLength = subStrPosition - (char*)iterator[DATA];
            size_t suffixLength = strlen(subStrPosition + oldSubStrLength);

            char* newString = (char*)realloc((char*)iterator[DATA], newLength);
			if (newString == nullptr)
				throw std::bad_alloc();

            memcpy(newString + (newLength - suffixLength - 1), newString + prefixLength + oldSubStrLength, suffixLength + 1);
            memcpy(newString + prefixLength, after, newSubStrLength);
			
            iterator[DATA] = newString;
        }

        iterator = (StringList)iterator[NEXTPTR];
    }
}

void StringListSort(StringList* list)
{
    if (list == nullptr)
        throw std::invalid_argument("List is nullptr");

    int listSize = StringListSize(*list);

    for (size_t i = 0; i < listSize - 1; i++)
    {
        StringList iterator = *list;
        StringList previous = *list;

        for (size_t j = 0; j < listSize - i - 1; j++)
        {
            StringList nextIterator = (StringList)iterator[NEXTPTR];

            if (strcmp((char*)iterator[DATA], (char*)(nextIterator[DATA])) > 0)
            {
                if (iterator == *list)
                {
                    *list = nextIterator;
                    iterator[NEXTPTR] = nextIterator[NEXTPTR];
                    nextIterator[NEXTPTR] = iterator;
                    previous = nextIterator;
                }
                else
                {
                    previous[NEXTPTR] = nextIterator;
                    iterator[NEXTPTR] = nextIterator[NEXTPTR];
                    nextIterator[NEXTPTR] = iterator;
                    previous = nextIterator;
                }

                iterator = (StringList)nextIterator[NEXTPTR];
            }
            else
            {
                previous = iterator;
                iterator = (StringList)iterator[NEXTPTR];
            }
        }
    }
}
