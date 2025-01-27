#include "StringList.h"

int main()
{
	void** list;
	StringListInit(&list);
	StringListAdd(list, "b");
	StringListAdd(list, "d");
	StringListAdd(list, "f");
	StringListAdd(list, "a");
	StringListAdd(list, "c");
	StringListAdd(list, "h");

	StringListSort(&list);
	PrintList(list);
	


	return 0;
}