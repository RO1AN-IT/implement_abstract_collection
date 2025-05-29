#include <iostream>
#include <string>
#include "ArraySequence.h"
#include "ListSequence.h"
#include "SegmentedList.h"
#include "AdaptiveSequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"

// template<typename T>
// void seq.toString() Sequence<T>* seq) {
//     std::cout << "[ ";
//     for (int i = 0; i < seq->GetLength(); ++i) {
//         std::cout << seq->Get(i);
//         if (i < seq->GetLength() - 1) std::cout << ", ";
//     }
//     std::cout << " ]" << std::endl;
// }

// template<typename T>
// void printContainer(const Container<T>* cont) {
//     std::cout << "[ ";
//     for (int i = 0; i < cont->getSize(); ++i) {
//         std::cout << cont->get(i);
//         if (i < cont->getSize() - 1) std::cout << ", ";
//     }
//     std::cout << " ]" << std::endl;
// }

void arraySequenceMenu(MutableArraySequence<int>& seq) {
    while (true) {
        std::cout << "\nArraySequence Menu:\n";
        std::cout << "1. Append\n2. Prepend\n3. InsertAt\n4. Remove\n5. RemoveAt\n";
        std::cout << "6. Get\n7. GetFirst\n8. GetLast\n9. GetLength\n10. Sum\n";
        std::cout << "11. Product\n12. Clear\n13. Contains\n14. Print\n15. Back\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Append(value);
                    std::cout << "Appended: " << value << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Prepend(value);
                    std::cout << "Prepended: " << value << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.InsertAt(value, index);
                    std::cout << "Inserted " << value << " at index " << index << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    if (seq.Remove(value)) {
                        std::cout << "Removed: " << value << std::endl;
                    } else {
                        std::cout << "Value not found" << std::endl;
                    }
                    break;
                }
                case 5: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    seq.RemoveAt(index);
                    std::cout << "Removed element at index " << index << std::endl;
                    break;
                }
                case 6: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Value: " << seq.Get(index) << std::endl;
                    break;
                }
                case 7:
                    std::cout << "First: " << seq.GetFirst() << std::endl;
                    break;
                case 8:
                    std::cout << "Last: " << seq.GetLast() << std::endl;
                    break;
                case 9:
                    std::cout << "Length: " << seq.GetLength() << std::endl;
                    break;
                case 10:
                   // std::cout << "Sum: " << seq.Sum() << std::endl;
                    break;
                case 11:
                    //std::cout << "Product: " << seq.Product() << std::endl;
                    break;
                case 12:
                    seq.Clear();
                    std::cout << "Sequence cleared" << std::endl;
                    break;
                case 13: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    std::cout << (seq.Contains(value) ? "Contains: true" : "Contains: false") << std::endl;
                    break;
                }
                case 14:
                    std::cout << "Sequence: " << seq.toString() << std::endl;
                    break;
                case 15:
                    return;
                default:
                    std::cout << "Invalid choice" << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
        }
    }
}

void listSequenceMenu(MutableListSequence<int>& seq) {
    while (true) {
        std::cout << "\nListSequence Menu:\n";
        std::cout << "1. Append\n2. Prepend\n3. InsertAt\n4. Remove\n5. RemoveAt\n";
        std::cout << "6. Get\n7. GetFirst\n8. GetLast\n9. GetLength\n10. Sum\n";
        std::cout << "11. Product\n12. Clear\n13. Contains\n14. Print\n15. Back\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Append(value);
                    std::cout << "Appended: " << value << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Prepend(value);
                    std::cout << "Prepended: " << value << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.InsertAt(value, index);
                    std::cout << "Inserted " << value << " at index " << index << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    if (seq.Remove(value)) {
                        std::cout << "Removed: " << value << std::endl;
                    } else {
                        std::cout << "Value not found" << std::endl;
                    }
                    break;
                }
                case 5: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    seq.RemoveAt(index);
                    std::cout << "Removed element at index " << index << std::endl;
                    break;
                }
                case 6: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Value: " << seq.Get(index) << std::endl;
                    break;
                }
                case 7:
                    std::cout << "First: " << seq.GetFirst() << std::endl;
                    break;
                case 8:
                    std::cout << "Last: " << seq.GetLast() << std::endl;
                    break;
                case 9:
                    std::cout << "Length: " << seq.GetLength() << std::endl;
                    break;
                case 10:
                    //std::cout << "Sum: " << seq.Sum() << std::endl;
                    break;
                case 11:
                    //std::cout << "Product: " << seq.Product() << std::endl;
                    break;
                case 12:
                    seq.Clear();
                    std::cout << "Sequence cleared" << std::endl;
                    break;
                case 13: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    std::cout << (seq.Contains(value) ? "Contains: true" : "Contains: false") << std::endl;
                    break;
                }
                case 14:
                    std::cout << "Sequence: " << seq.toString() << std::endl;
                    break;
                case 15:
                    return;
                default:
                    std::cout << "Invalid choice" << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
        }
    }
}

void segmentedListMenu(SegmentedList<int>& seq) {
    while (true) {
        std::cout << "\nSegmentedList Menu:\n";
        std::cout << "1. Append\n2. Prepend\n3. InsertAt\n4. Remove\n5. RemoveAt\n";
        std::cout << "6. Get\n7. GetFirst\n8. GetLast\n9. GetLength\n10. Sum\n";
        std::cout << "11. Product\n12. Clear\n13. Contains\n14. Print\n15. Back\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Append(value);
                    std::cout << "Appended: " << value << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Prepend(value);
                    std::cout << "Prepended: " << value << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.InsertAt(value, index);
                    std::cout << "Inserted " << value << " at index " << index << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    if (seq.Remove(value)) {
                        std::cout << "Removed: " << value << std::endl;
                    } else {
                        std::cout << "Value not found" << std::endl;
                    }
                    break;
                }
                case 5: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    seq.RemoveAt(index);
                    std::cout << "Removed element at index " << index << std::endl;
                    break;
                }
                case 6: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Value: " << seq.Get(index) << std::endl;
                    break;
                }
                case 7:
                    std::cout << "First: " << seq.GetFirst() << std::endl;
                    break;
                case 8:
                    std::cout << "Last: " << seq.GetLast() << std::endl;
                    break;
                case 9:
                    std::cout << "Length: " << seq.GetLength() << std::endl;
                    break;
                case 10:
                    //std::cout << "Sum: " << seq.Sum() << std::endl;
                    break;
                case 11:
                    //std::cout << "Product: " << seq.Product() << std::endl;
                    break;
                case 12:
                    seq.Clear();
                    std::cout << "Sequence cleared" << std::endl;
                    break;
                case 13: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    std::cout << (seq.Contains(value) ? "Contains: true" : "Contains: false") << std::endl;
                    break;
                }
                case 14:
                    std::cout << "Sequence: " << seq.toString() << std::endl;
                    break;
                case 15:
                    return;
                default:
                    std::cout << "Invalid choice" << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
        }
    }
}

void adaptiveSequenceMenu(AdaptiveSequence<int>& seq) {
    while (true) {
        std::cout << "\nAdaptiveSequence Menu:\n";
        std::cout << "1. Append\n2. Prepend\n3. InsertAt\n4. Remove\n5. RemoveAt\n";
        std::cout << "6. Get\n7. GetFirst\n8. GetLast\n9. GetLength\n10. Sum\n";
        std::cout << "11. Product\n12. Clear\n13. Contains\n14. Print\n15. Back\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Append(value);
                    std::cout << "Appended: " << value << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.Prepend(value);
                    std::cout << "Prepended: " << value << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    seq.InsertAt(value, index);
                    std::cout << "Inserted " << value << " at index " << index << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    if (seq.Remove(value)) {
                        std::cout << "Removed: " << value << std::endl;
                    } else {
                        std::cout << "Value not found" << std::endl;
                    }
                    break;
                }
                case 5: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    seq.RemoveAt(index);
                    std::cout << "Removed element at index " << index << std::endl;
                    break;
                }
                case 6: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Value: " << seq.Get(index) << std::endl;
                    break;
                }
                case 7:
                    std::cout << "First: " << seq.GetFirst() << std::endl;
                    break;
                case 8:
                    std::cout << "Last: " << seq.GetLast() << std::endl;
                    break;
                case 9:
                    std::cout << "Length: " << seq.GetLength() << std::endl;
                    break;
                case 10:
                    //std::cout << "Sum: " << seq.Sum() << std::endl;
                    break;
                case 11:
                    //std::cout << "Product: " << seq.Product() << std::endl;
                    break;
                case 12:
                    seq.Clear();
                    std::cout << "Sequence cleared" << std::endl;
                    break;
                case 13: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    std::cout << (seq.Contains(value) ? "Contains: true" : "Contains: false") << std::endl;
                    break;
                }
                case 14:
                    std::cout << "Sequence: " << seq.toString() << std::endl;
                    break;
                case 15:
                    return;
                default:
                    std::cout << "Invalid choice" << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
        }
    }
}

void linkedListMenu(LinkedList<int>& list) {
    while (true) {
        std::cout << "\nLinkedList Menu:\n";
        std::cout << "1. Append\n2. Prepend\n3. InsertAt\n4. Get\n5. GetFirst\n";
        std::cout << "6. GetLast\n7. GetSize\n8. Print\n9. Back\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    list.append(value);
                    std::cout << "Appended: " << value << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    list.prepend(value);
                    std::cout << "Prepended: " << value << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    list.insertAt(value, index);
                    std::cout << "Inserted " << value << " at index " << index << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Value: " << list.get(index) << std::endl;
                    break;
                }
                case 5:
                    std::cout << "First: " << list.getFirst() << std::endl;
                    break;
                case 6:
                    std::cout << "Last: " << list.getLast() << std::endl;
                    break;
                case 7:
                    std::cout << "Size: " << list.getSize() << std::endl;
                    break;
                case 8:
                    std::cout << "List: " << list.toString() << std::endl;
                    break;
                case 9:
                    return;
                default:
                    std::cout << "Invalid choice" << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
        }
    }
}

void dynamicArrayMenu(DynamicArray<int>& arr) {
    while (true) {
        std::cout << "\nDynamicArray Menu:\n";
        std::cout << "1. Append\n2. Prepend\n3. InsertAt\n4. Get\n5. GetFirst\n";
        std::cout << "6. GetLast\n7. GetSize\n8. Set\n9. Resize\n10. Print\n11. Back\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    arr.append(value);
                    std::cout << "Appended: " << value << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    arr.prepend(value);
                    std::cout << "Prepended: " << value << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    arr.insertAt(value, index);
                    std::cout << "Inserted " << value << " at index " << index << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Value: " << arr.get(index) << std::endl;
                    break;
                }
                case 5:
                    std::cout << "First: " << arr.getFirst() << std::endl;
                    break;
                case 6:
                    std::cout << "Last: " << arr.getLast() << std::endl;
                    break;
                case 7:
                    std::cout << "Size: " << arr.getSize() << std::endl;
                    break;
                case 8: {
                    std::cout << "Enter index: ";
                    int index;
                    std::cin >> index;
                    std::cout << "Enter value: ";
                    int value;
                    std::cin >> value;
                    arr.Set(index, value);
                    std::cout << "Set " << value << " at index " << index << std::endl;
                    break;
                }
                case 9: {
                    std::cout << "Enter new size: ";
                    int newSize;
                    std::cin >> newSize;
                    arr.Resize(newSize);
                    std::cout << "Resized to " << newSize << std::endl;
                    break;
                }
                case 10:
                    std::cout << "Array: " << arr.toString() << std::endl;
                    break;
                case 11:
                    return;
                default:
                    std::cout << "Invalid choice" << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred" << std::endl;
        }
    }
}

int main() {
    MutableArraySequence<int> arraySeq;
    MutableListSequence<int> listSeq;
    SegmentedList<int> segList;
    AdaptiveSequence<int> adaptSeq;
    LinkedList<int> linkedList;
    DynamicArray<int> dynArray;

    //std::unique_ptr<IEnumerator<int>> iter = arraySeq.GetEnumerator();

    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. ArraySequence\n2. ListSequence\n3. SegmentedList\n";
        std::cout << "4. AdaptiveSequence\n5. LinkedList\n6. DynamicArray\n7. Exit\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                arraySequenceMenu(arraySeq);
                break;
            case 2:
                listSequenceMenu(listSeq);
                break;
            case 3:
                segmentedListMenu(segList);
                break;
            case 4:
                adaptiveSequenceMenu(adaptSeq);
                break;
            case 5:
                linkedListMenu(linkedList);
                break;
            case 6:
                dynamicArrayMenu(dynArray);
                break;
            case 7:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice\n";
        }
    }
}