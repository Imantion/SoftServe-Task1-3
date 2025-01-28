#include <iostream>
#include "VariantPrimitive.h"

int main() {
    // Test case 1: Default constructor
    VariantPrimitive defaultVar;
    std::cout << "Default type: " << defaultVar.get_type() << std::endl;

    // Test case 2: Constructor with int
    VariantPrimitive intVar(42);
    std::cout << "Int value: " << intVar.ToInt()
        << ", Type: " << intVar.get_type() << std::endl;

    // Test case 3: Constructor with float
    VariantPrimitive floatVar(3.14f);
    std::cout << "Float value: " << floatVar.ToFloat()
        << ", Type: " << floatVar.get_type() << std::endl;

    // Test case 4: Constructor with double
    VariantPrimitive doubleVar(2.71828);
    std::cout << "Double value: " << doubleVar.ToDouble()
        << ", Type: " << doubleVar.get_type() << std::endl;

    // Test case 5: Constructor with char
    VariantPrimitive charVar('A');
    std::cout << "Char value: " << charVar.ToChar()
        << ", Type: " << charVar.get_type() << std::endl;

    // Test case 6: Constructor with bool
    VariantPrimitive boolVar(true);
    std::cout << "Bool value: " << boolVar.ToBool()
        << ", Type: " << boolVar.get_type() << std::endl;

    // Test case 7: Assignment operator
    VariantPrimitive anotherVar;
    anotherVar = 100;  // Assign int
    std::cout << "Assigned int value: " << anotherVar.ToInt()
        << ", Type: " << anotherVar.get_type() << std::endl;

    anotherVar = false;  // Assign bool
    std::cout << "Assigned bool value: " << anotherVar.ToBool()
        << ", Type: " << anotherVar.get_type() << std::endl;

    // Test case 8: Reset function
    anotherVar.Reset();
    std::cout << "After reset, Type: " << anotherVar.get_type() << std::endl;

    // Test case 9: Swap function
    VariantPrimitive swapVar1(123);
    VariantPrimitive swapVar2(4.56f);
    std::cout << "Before swap: Var1 = " << swapVar1.ToInt() << ", Var2 = " << swapVar2.ToFloat() << std::endl;
    swapVar1.Swap(swapVar2);
    std::cout << "After swap: Var1 = " << swapVar1.ToFloat() << ", Var2 = " << swapVar2.ToInt() << std::endl;

    // Test case 10: Copy constructor
    VariantPrimitive copiedVar = intVar;
    std::cout << "Copied value: " << copiedVar.ToInt()
        << ", Type: " << copiedVar.get_type() << std::endl;



    return 0;
}
