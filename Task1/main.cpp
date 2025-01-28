#include <iostream>
#include "StringList.h"

int main() {
    // Test case 1: Initialize list
    void** stringList = nullptr;
    StringListInit(&stringList);
    std::cout << "List initialized.\n";

    // Test case 2: Add strings to the list
    StringListAdd(stringList, "Apple");
    StringListAdd(stringList, "Banana");
    StringListAdd(stringList, "Cherry");
    StringListAdd(stringList, "Mellon");
    StringListAdd(stringList, "Strawberry");
    StringListAdd(stringList, "Pear");
    StringListAdd(stringList, "Tangerin");
    StringListAdd(stringList, "Apple");  // Adding duplicate
    StringListAdd(stringList, "Banana");  // Adding duplicate
    PrintList(stringList);
    std::cout << "List size after adding elements: " << StringListSize(stringList) << "\n";

    // Test case 3: Remove duplicates
    StringListRemoveDuplicates(&stringList);
    std::cout << "List after removing duplicates: ";
    PrintList(stringList);
    std::cout << "List size after removing duplicates: " << StringListSize(stringList) << "\n";

    // Test case 4: Replace strings
    StringListReplaceInStrings(stringList, "App", "Orange");
    std::cout << "List after replacing 'App' with 'Orange': ";
    PrintList(stringList);

    // Test case 5: Find the index of a string
    int index = StringListIndexOf(stringList, "Orangele");
    std::cout << "Index of 'Orangele': " << index << "\n";

    // Test case 6: Remove a string
    StringListRemove(&stringList, "Banana");
    std::cout << "List after removing 'Banana': ";
    PrintList(stringList);

    // Test case 7: Sorting the list
    StringListSort(&stringList);
    std::cout << "List after sorting: ";
    PrintList(stringList);

    // Test case 8: Destroy the list
    StringListDestroy(&stringList);
    std::cout << "List destroyed.\n";

    return 0;
}