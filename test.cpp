#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "AdaptiveSequence.h"
#include "SegmentedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"

int square(int x) { return x * x; }

bool isEven(int x) { return x % 2 == 0; }

int sumReduce(int acc, int x) { return acc + x; }

Sequence<int>* repeatElement(int x) {
    int* items = new int[2];
    items[0] = x;
    items[1] = x;
    Sequence<int>* seq = new AdaptiveSequence<int>(items, 2);
    delete[] items;
    return seq;
}

std::vector<int> parseValues(const std::string& values) {
    std::vector<int> result;
    std::stringstream ss(values);
    std::string item;
    while (std::getline(ss, item, ',')) {
        result.push_back(std::stoi(item));
    }
    return result;
}

template<typename T>
Sequence<T>* createSameTypeSequence(const Sequence<T>* seq, T* items, int size) {
    if (dynamic_cast<const AdaptiveSequence<T>*>(seq)) {
        return new AdaptiveSequence<T>(items, size);
    }
    else if (dynamic_cast<const SegmentedList<T>*>(seq)) {
        return new SegmentedList<T>(items, size);
    }
    else if (dynamic_cast<const MutableArraySequence<T>*>(seq)) {
        return new MutableArraySequence<T>(items, size);
    }
    else if (dynamic_cast<const MutableListSequence<T>*>(seq)) {
        return new MutableListSequence<T>(items, size);
    }
    return nullptr;
}

template<typename T>
std::string sequenceToString(const Sequence<T>* seq) {
    std::stringstream ss;
    ss << "[ ";
    for (int i = 0; i < seq->GetLength(); i++) {
        ss << seq->Get(i);
        if (i < seq->GetLength() - 1) ss << ", ";
    }
    ss << " ]";
    return ss.str();
}

int main() {
    std::ifstream inFile("input.txt");
    std::ofstream outFile("output.txt");
    if (!inFile.is_open() || !outFile.is_open()) {
        outFile << "Error: Unable to open input or output file\n";
        return 1;
    }

    AdaptiveSequence<int>* adaptive = new AdaptiveSequence<int>();
    SegmentedList<int>* segmented = new SegmentedList<int>();
    MutableArraySequence<int>* array = new MutableArraySequence<int>();
    MutableListSequence<int>* list = new MutableListSequence<int>();

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string collectionType, operation;
        ss >> collectionType >> operation;

        Sequence<int>* seq = nullptr;
        if (collectionType == "Adaptive") seq = adaptive;
        else if (collectionType == "Segmented") seq = segmented;
        else if (collectionType == "Array") seq = array;
        else if (collectionType == "List") seq = list;
        else {
            outFile << "Unknown collection: " << collectionType << "\n";
            continue;
        }

        std::string command = collectionType + " " + operation;
        std::string result;

        try {
            if (operation == "Append") {
                int value;
                ss >> value;
                seq->Append(value);
                command += " " + std::to_string(value);
                result = sequenceToString(seq);
            }
            else if (operation == "Prepend") {
                int value;
                ss >> value;
                seq->Prepend(value);
                command += " " + std::to_string(value);
                result = sequenceToString(seq);
            }
            else if (operation == "InsertAt") {
                int index, value;
                ss >> index >> value;
                seq->InsertAt(value, index);
                command += " " + std::to_string(index) + " " + std::to_string(value);
                result = sequenceToString(seq);
            }
            else if (operation == "RemoveAt") {
                int index;
                ss >> index;
                seq->RemoveAt(index);
                command += " " + std::to_string(index);
                result = sequenceToString(seq);
            }
            else if (operation == "GetSubSequence") {
                int start, end;
                ss >> start >> end;
                Sequence<int>* subseq = seq->GetSubSequence(start, end);
                command += " " + std::to_string(start) + " " + std::to_string(end);
                result = sequenceToString(subseq);
                delete subseq;
            }
            else if (operation == "Concat") {
                std::string values;
                std::getline(ss, values);
                values = values.substr(1); // Remove leading space
                std::vector<int> vals = parseValues(values);
                Sequence<int>* other = createSameTypeSequence(seq, vals.data(), vals.size());
                seq->Concat(other);
                command += " " + values;
                result = sequenceToString(seq);
                delete other;
            }
            else if (operation == "Map") {
                Sequence<int>* mapped = nullptr;
                if (auto* adaptiveSeq = dynamic_cast<AdaptiveSequence<int>*>(seq)) {
                    mapped = adaptiveSeq->Map(square);
                }
                else if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
                    mapped = arraySeq->Map(square);
                }
                else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
                    mapped = listSeq->Map(square);
                }
                if (mapped) {
                    result = sequenceToString(mapped);
                    delete mapped;
                }
                else {
                    result = "Error: Map not supported for " + collectionType;
                }
            }
            else if (operation == "Where") {
                Sequence<int>* filtered = nullptr;
                if (auto* adaptiveSeq = dynamic_cast<AdaptiveSequence<int>*>(seq)) {
                    filtered = adaptiveSeq->Where(isEven);
                }
                else if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
                    filtered = arraySeq->Where(isEven);
                }
                else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
                    filtered = listSeq->Where(isEven);
                }
                if (filtered) {
                    result = sequenceToString(filtered);
                    delete filtered;
                }
                else {
                    result = "Error: Where not supported for " + collectionType;
                }
            }
            else if (operation == "GetFirst") {
                result = std::to_string(seq->GetFirst());
                command = collectionType + " GetFirst";
            }
            else if (operation == "GetLast") {
                result = std::to_string(seq->GetLast());
                command = collectionType + " GetLast";
            }
            else if (operation == "Get") {
                int index;
                ss >> index;
                result = std::to_string(seq->Get(index));
                command += " " + std::to_string(index);
            }
            else if (operation == "GetLength") {
                result = std::to_string(seq->GetLength());
            }
            else if (operation == "Clear") {
                seq->Clear();
                result = sequenceToString(seq);
            }
            else if (operation == "Contains") {
                int value;
                ss >> value;
                result = seq->Contains(value) ? "true" : "false";
                command += " " + std::to_string(value);
            }
            else if (operation == "Remove") {
                int value;
                ss >> value;
                bool removed = seq->Remove(value);
                result = removed ? "true" : "false";
                command += " " + std::to_string(value);
            }
            else if (operation == "GetEnumerator") {
                auto enumerator = seq->GetEnumerator();
                std::stringstream ss;
                ss << "[ ";
                bool first = true;
                while (enumerator->MoveNext()) {
                    if (!first) ss << ", ";
                    ss << enumerator->Current();
                    first = false;
                }
                ss << " ]";
                result = ss.str();
            }
            // else if (operation == "Sum") {
            //     result = std::to_string(seq->Sum());
            // }
            // else if (operation == "Product") {
            //     result = std::to_string(seq->Product());
            // }
            else if (operation == "FlatMap") {
                Sequence<int>* flatMapped = nullptr;
                if (auto* adaptiveSeq = dynamic_cast<AdaptiveSequence<int>*>(seq)) {
                    flatMapped = adaptiveSeq->FlatMap(repeatElement);
                }
                else if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
                    flatMapped = arraySeq->FlatMap(repeatElement);
                }
                else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
                    flatMapped = listSeq->FlatMap(repeatElement);
                }
                if (flatMapped) {
                    result = sequenceToString(flatMapped);
                    delete flatMapped;
                }
                else {
                    result = "Error: FlatMap not supported for " + collectionType;
                }
            }
            else if (operation == "Reduce") {
                Sequence<int>* reduced = nullptr;
                if (auto* adaptiveSeq = dynamic_cast<AdaptiveSequence<int>*>(seq)) {
                    reduced = adaptiveSeq->Reduce(sumReduce, 0);
                }
                else if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
                    reduced = arraySeq->Reduce(sumReduce, 0);
                }
                else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
                    reduced = listSeq->Reduce(sumReduce, 0);
                }
                if (reduced) {
                    result = sequenceToString(reduced);
                    delete reduced;
                }
                else {
                    result = "Error: Reduce not supported for " + collectionType;
                }
            }
            // else if (operation == "Zip") {
            //     std::string values;
            //     std::getline(ss, values);
            //     values = values.substr(1); // Remove leading space
            //     std::vector<int> vals = parseValues(values);
            //     Sequence<int>* other = createSameTypeSequence(seq, vals.data(), vals.size());
            //     Sequence<std::tuple<int, int>>* zipped = nullptr;
            //     if (auto* adaptiveSeq = dynamic_cast<AdaptiveSequence<int>*>(seq)) {
            //         zipped = adaptiveSeq->Zip<int>(other);
            //     }
            //     else if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
            //         zipped = arraySeq->Zip<int>(other);
            //     }
            //     else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
            //         zipped = listSeq->Zip<int>(other);
            //     }
            //     if (zipped) {
            //         std::stringstream ss;
            //         ss << "[ ";
            //         for (int i = 0; i < zipped->GetLength(); i++) {
            //             auto tuple = zipped->Get(i);
            //             ss << "(" << std::get<0>(tuple) << "," << std::get<1>(tuple) << ")";
            //             if (i < zipped->GetLength() - 1) ss << ", ";
            //         }
            //         ss << " ]";
            //         result = ss.str();
            //         delete zipped;
            //     }
            //     else {
            //         result = "Error: Zip not supported for " + collectionType;
            //     }
            //     delete other;
            //     command += " " + values;
            // }
            else if (operation == "Split") {
                Sequence<Sequence<int>*>* split = nullptr;
                if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
                    split = arraySeq->Split(isEven);
                }
                else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
                    split = listSeq->Split(isEven);
                }
                if (split) {
                    std::stringstream ss;
                    ss << "[ ";
                    for (int i = 0; i < split->GetLength(); i++) {
                        ss << sequenceToString(split->Get(i));
                        if (i < split->GetLength() - 1) ss << ", ";
                    }
                    ss << " ]";
                    result = ss.str();
                    for (int i = 0; i < split->GetLength(); i++) {
                        delete split->Get(i);
                    }
                    delete split;
                }
                else {
                    result = "Error: Split not supported for " + collectionType;
                }
            }
            else if (operation == "From") {
                std::string values;
                std::getline(ss, values);
                values = values.substr(1);
                std::vector<int> vals = parseValues(values);
                seq->From(vals.data(), vals.size());
                command += " " + values;
                result = sequenceToString(seq);
            }
            else if (operation == "IndexOperator") {
                int index, value;
                ss >> index >> value;
                if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
                    (*arraySeq)[index] = value;
                    result = sequenceToString(seq);
                }
                else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
                    (*listSeq)[index] = value;
                    result = sequenceToString(seq);
                }
                else {
                    result = "Error: Index operator not supported for " + collectionType;
                }
                command += " " + std::to_string(index) + " " + std::to_string(value);
            }
            else if (operation == "CopyConstructor") {
                Sequence<int>* copy = nullptr;
                if (auto* adaptiveSeq = dynamic_cast<AdaptiveSequence<int>*>(seq)) {
                    copy = new AdaptiveSequence<int>(*adaptiveSeq);
                }
                else if (auto* segmentedSeq = dynamic_cast<SegmentedList<int>*>(seq)) {
                    copy = new SegmentedList<int>(*segmentedSeq);
                }
                else if (auto* arraySeq = dynamic_cast<MutableArraySequence<int>*>(seq)) {
                    copy = new MutableArraySequence<int>(*arraySeq);
                }
                else if (auto* listSeq = dynamic_cast<MutableListSequence<int>*>(seq)) {
                    copy = new MutableListSequence<int>(*listSeq);
                }
                result = sequenceToString(copy);
                delete copy;
            }
            else if (operation == "CopyAssignment") {
                Sequence<int>* temp = createSameTypeSequence<int>(seq, nullptr, 0);
                *temp = *seq;
                result = sequenceToString(temp);
                delete temp;
            }
        }
        catch (const std::exception& e) {
            result = "Error: " + std::string(e.what());
        }

        outFile << command << ": " << result << "\n";
    }

    delete adaptive;
    delete segmented;
    delete array;
    delete list;

    inFile.close();
    outFile.close();
    return 0;
}