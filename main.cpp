#include<iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    LinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);

    std::cout << "List 1: " << list1.toString() << std::endl;

    LinkedList<int> list2;
    list2.append(4);
    list2.append(5);
    list2.append(6);

    std::cout << "List 2: " << list2.toString() << std::endl;

    list1 = *list1.Concat(&list2);

    std::cout << "Concatenated List: " << list1.toString() << std::endl;


    MutableArraySequence<int> list3;
    list3.Append(1);
    list3.Append(2);
    list3.Append(3);

    std::cout << "List 1: " << list3.toString() << std::endl;

    MutableArraySequence<int> list4;
    list4.Append(4);
    list4.Append(5);
    list4.Append(6);

    std::cout << "List 2: " << list4.toString() << std::endl;

    list3 = *list3.Concat(&list4);

    std::cout << "Concatenated List: " << list3.toString() << std::endl;


    list3[3] = 10;
    std::cout << "elem 3: " << list3[3]<< std::endl;
    return 0;
}