#include <iostream>
#include "StringList.h"

void PrintList(StringList list)
{
    if (list == nullptr)
        return;

    StringList iterator = list;
    while (iterator != nullptr)
    {
        printf("%s ", (char*)iterator[0]);
        iterator = (StringList)iterator[1];
    }
    printf("\n");
}


int main()
{
    // Test case 1: Initialize list
    const char* a = "Apple";
    const char* b = "Banana";
    const char* c = "Carrot";
    const char* d = "Dog";
    const char* e = "Elephant";
    const char* f = "Fish";
    const char* g = "Giraffe";
    const char* h = "Horse";
    StringList stringList = nullptr;
    StringListInit(&stringList);
    //   std::cout << "List initialized.\n";

    //   // Test case 2: Add strings to the list

    StringListAdd(stringList, f);
    StringListAdd(stringList, b);
    StringListAdd(stringList, e);
    StringListAdd(stringList, g);
    StringListAdd(stringList, d);
    StringListAdd(stringList, e);  // Adding duplicate
    StringListAdd(stringList, f);
    StringListAdd(stringList, a);
    StringListAdd(stringList, c);// Adding duplicate

    //   PrintList(stringList);
    StringListSize(stringList);

    //// Test case 3: Remove duplicates
    StringListRemoveDuplicates(&stringList);
    //std::cout << "List after removing duplicates: ";
    //PrintList(stringList);
    //std::cout << "List size after removing duplicates: " << StringListSize(stringList) << "\n";

    //// Test case 4: Replace strings
    StringListReplaceInStrings(stringList, "App", "Orange");
    //std::cout << "List after replacing 'App' with 'Orange': ";
    //PrintList(stringList);

    //// Test case 5: Find the index of a string
    int index = StringListIndexOf(stringList, "Orangele");
    //std::cout << "Index of 'Orangele': " << index << "\n";

    //// Test case 6: Remove a string
    StringListRemove(&stringList, "Banana");
    //std::cout << "List after removing 'Banana': ";
    //PrintList(stringList);

    //// Test case 7: Sorting the list
    StringListSort(&stringList);
    //std::cout << "List after sorting: ";
    //PrintList(stringList);

    // Test case 8: Destroy the list
    StringListDestroy(&stringList);

    return 0;
}


//int main() {
//    // Test case 1: Initialize list
//    StringList stringList = nullptr;
//    StringListInit(&stringList);
//    std::cout << "List initialized.\n";
//
//    // Test case 2: Add strings to the list
//    StringListAdd(stringList, "Apple");
//    StringListAdd(stringList, "Banana");
//    StringListAdd(stringList, "Cherry");
//    StringListAdd(stringList, "Mellon");
//    StringListAdd(stringList, "Strawberry");
//    StringListAdd(stringList, "Pear");
//    StringListAdd(stringList, "Tangerin");
//    StringListAdd(stringList, "Apple");  // Adding duplicate
//    StringListAdd(stringList, "Banana");  // Adding duplicate
//    PrintList(stringList);
//    std::cout << "List size after adding elements: " << StringListSize(stringList) << "\n";
//
//    // Test case 3: Remove duplicates
//    StringListRemoveDuplicates(&stringList);
//    std::cout << "List after removing duplicates: ";
//    PrintList(stringList);
//    std::cout << "List size after removing duplicates: " << StringListSize(stringList) << "\n";
//
//    // Test case 4: Replace strings
//    StringListReplaceInStrings(stringList, "App", "Orange");
//    std::cout << "List after replacing 'App' with 'Orange': ";
//    PrintList(stringList);
//
//    // Test case 5: Find the index of a string
//    int index = StringListIndexOf(stringList, "Orangele");
//    std::cout << "Index of 'Orangele': " << index << "\n";
//
//    // Test case 6: Remove a string
//    StringListRemove(&stringList, "Banana");
//    std::cout << "List after removing 'Banana': ";
//    PrintList(stringList);
//
//    // Test case 7: Sorting the list
//    StringListSort(&stringList);
//    std::cout << "List after sorting: ";
//    PrintList(stringList);
//
//    // Test case 8: Destroy the list
//    StringListDestroy(&stringList);
//    std::cout << "List destroyed.\n";
//
//    return 0;
//}