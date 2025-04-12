#pragma once 
#include "Sequence.h"
#include "LinkedList.h"

template<typename T>
class MutableListSequence; // Предварительное объявление
template<typename T>
class ImmutableListSequence;

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* data;
    int size;

    Sequence<T>* AppendInternal(T item) {
        data->append(item);
        size++;
        return this;
    }

    Sequence<T>* PrependInternal(T item) {
        data->prepend(item);
        size++;
        return this;
    }

    Sequence<T>* InsertAtInternal(T item, int index) {
        data->insertAt(item, index);
        size++;
        return this;
    }

    Sequence<T>* ConcatInternal(Sequence<T>* array) {
        for (int i = 0; i < array->GetLength(); i++) {
            data->append(array->Get(i));
        }
        size += array->GetLength();
        return this;
    }

public:
    // Конструкторы и деструктор
    ListSequence() : size(0) {
        data = new LinkedList<T>(0);
    }
    ListSequence(int size) : ListSequence(nullptr, size) {}
    ListSequence(const ListSequence<T>& other) : ListSequence(other.data->getData(), other.size) {}
    ListSequence(T* items, int size) : size(size) {
        data = new LinkedList<T>(items, size);
    }

    virtual ~ListSequence() { delete data; }
    //-------------------------

    // Операторы
    T& operator[](int index) {
        if (index < 0 || index >= GetLength()) {
            throw std::out_of_range("Index out of range");
        }
        return data->get(index);
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= GetLength()) {
            throw std::out_of_range("Index out of range");
        }
        return data->get(index);
    }

    Sequence<T>& operator=(const Sequence<T>& other){
        if (this == &other) {
            return *this;
        }
    
        delete this->data;
    
        const ListSequence<T>* arrSeq = dynamic_cast<const ListSequence<T>*>(&other);
        if (!arrSeq) {
            throw std::invalid_argument("Incompatible types in assignment");
        }
    
        int length = arrSeq->GetLength();
        T* newData = new T[length];
        for (int i = 0; i < length; ++i) {
            newData[i] = arrSeq->Get(i);
        }
    
        this->data = new LinkedList<T>(newData, length);
        this->size = length;
    
        delete[] newData;
        return *this;
    }
    //------------------------

    T Get(int index) override {
        if (data->getSize() == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data->get(index);
    }

    T GetFirst() override {
        if (data->getSize() == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        return data->getFirst();
    }

    T GetLast() override {
        if (data->getSize() == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        return data->getLast();
    }

    int GetLength() override {
        return size;
    }

    Sequence<T>* GetSubSequence(int startIndex, int endIndex) const override {
        if (data->getSize() == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        if (startIndex < 0 || startIndex >= data->getSize() || endIndex < startIndex || endIndex >= data->getSize()) {
            throw std::out_of_range("Invalid range");
        }
        int subSize = endIndex - startIndex + 1;
        T* subItems = new T[subSize];
        for (int i = 0; i < subSize; i++) {
            subItems[i] = data->get(startIndex + i);
        }
        MutableListSequence<T>* subseq = new MutableListSequence<T>(subItems, subSize);
        delete[] subItems;
        return subseq;
    }

    Sequence<T>* Append(T item) override {
        return static_cast<ListSequence<T>*>(Instance())->AppendInternal(item);
    }

    Sequence<T>* Prepend(T item) override {
        return static_cast<ListSequence<T>*>(Instance())->PrependInternal(item);
    }

    Sequence<T>* InsertAt(T item, int index) override {
        return static_cast<ListSequence<T>*>(Instance())->InsertAtInternal(item, index);
    }

    Sequence<T>* Concat(Sequence<T>* array) override {
        return static_cast<ListSequence<T>*>(Instance())->ConcatInternal(array);
    }

    virtual Sequence<T>* Instance() = 0;
};

template<typename T>
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(int size) : ListSequence<T>(size) {}
    MutableListSequence(const MutableListSequence<T>& other) : ListSequence<T>(other) {}
    MutableListSequence(T* items, int size) : ListSequence<T>(items, size) {}

    Sequence<T>* Instance() override {
        return this;
    }

    Sequence<T>& operator=(const Sequence<T>& other){
        if (this == &other) {
            return *this;
        }
    
        delete this->data;
    
        const ListSequence<T>* arrSeq = dynamic_cast<const ListSequence<T>*>(&other);
        if (!arrSeq) {
            throw std::invalid_argument("Incompatible types in assignment");
        }
    
        int length = arrSeq->GetLength();
        T* newData = new T[length];
        for (int i = 0; i < length; ++i) {
            newData[i] = arrSeq->Get(i);
        }
    
        this->data = new LinkedList<T>(newData, length);
        this->size = length;
    
        delete[] newData;
        return *this;
    }
};

template<typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(int size) : ListSequence<T>(size) {}
    ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequence<T>(other) {}
    ImmutableListSequence(T* items, int size) : ListSequence<T>(items, size) {}

    Sequence<T>* Instance() override {
        return new ImmutableListSequence<T>(*this);
    }

    Sequence<T>& operator=(const Sequence<T>& other){
        if (this == &other) {
            return *this;
        }
    
        delete this->data;
    
        const ListSequence<T>* arrSeq = dynamic_cast<const ListSequence<T>*>(&other);
        if (!arrSeq) {
            throw std::invalid_argument("Incompatible types in assignment");
        }
    
        int length = arrSeq->GetLength();
        T* newData = new T[length];
        for (int i = 0; i < length; ++i) {
            newData[i] = arrSeq->Get(i);
        }
    
        this->data = new LinkedList<T>(newData, length);
        this->size = length;
    
        delete[] newData;
        return *this;
    }
};