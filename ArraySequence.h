#pragma once 
#include "Sequence.h"
#include "DynamicArray.h"

template<typename T>
class MutableArraySequence; 
template<typename T>
class ImmutableArraySequence;

template<typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* data;
    int size;

    Sequence<T>* AppendInternal(T item) {
        data->Resize(size + 1);
        size++;
        data->Set(size - 1, item);
        return this;
    }

    Sequence<T>* PrependInternal(T item) {
        data->Resize(size + 1);
        size++;
        for (int i = size - 1; i > 0; i--) {
            data->Set(i, data->get(i - 1));
        }
        data->Set(0, item);
        return this;
    }

    Sequence<T>* InsertAtInternal(T item, int index) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        data->Resize(size + 1);
        size++;
        for (int i = size - 1; i > index; i--) {
            data->Set(i, data->get(i - 1));
        }
        data->Set(index, item);
        return this;
    }

    Sequence<T>* ConcatInternal(Sequence<T>* array) {
        int reSize = this->GetLength() + array->GetLength();
        data->Resize(reSize);
        for (int i = 0; i < array->GetLength(); i++) {
            data->Set(this->GetLength() + i, array->Get(i));
        }
        size = reSize;
        return this;
    }

public:
    //конструкторы и деструктор
    ArraySequence(): size(0) {
        data = new DynamicArray<T>(0);
    }
    ArraySequence(int size) : ArraySequence(nullptr, size) {}
    ArraySequence(const ArraySequence<T>& other) : ArraySequence(other.data->getData(), other.size) {}
    ArraySequence(T* items, int size) : size(size) {
        data = new DynamicArray<T>(items, size);
    }

    virtual ~ArraySequence() { delete data; }
    //------------------------

    //перегрузки операторов
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
    
        const ArraySequence<T>* arrSeq = dynamic_cast<const ArraySequence<T>*>(&other);
        if (!arrSeq) {
            throw std::invalid_argument("Incompatible types in assignment");
        }
    
        int length = arrSeq->GetLength();
        T* newData = new T[length];
        for (int i = 0; i < length; ++i) {
            newData[i] = arrSeq->Get(i);
        }
    
        this->data = new DynamicArray<T>(newData, length);
        this->size = length;
    
        delete[] newData;
        return *this;
    }
    //-------------------------

    T Get(int index) const override {
        if (size == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        return data->get(index);
    }

    T GetFirst() const override {
        if (size == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        return data->get(0);
    }

    T GetLast() const override {
        if (size == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        return data->get(size - 1);
    }

    int GetLength() const override {
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
        MutableArraySequence<T>* subseq = new MutableArraySequence<T>(subItems, subSize);
        delete[] subItems;
        return subseq;
    }

    Sequence<T>* Append(T item) override {
        return static_cast<ArraySequence<T>*>(Instance())->AppendInternal(item);
    }

    Sequence<T>* Prepend(T item) override {
        return static_cast<ArraySequence<T>*>(Instance())->PrependInternal(item);
    }

    Sequence<T>* InsertAt(T item, int index) override {
        return static_cast<ArraySequence<T>*>(Instance())->InsertAtInternal(item, index);
    }

    Sequence<T>* Concat(Sequence<T>* array) override {
        return static_cast<ArraySequence<T>*>(Instance())->ConcatInternal(array);
    }

    virtual Sequence<T>* Instance() = 0;
};

template<typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(int size) : ArraySequence<T>(size) {}
    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    MutableArraySequence(T* items, int size) : ArraySequence<T>(items, size) {}

    Sequence<T>* Instance() override {
        return this;
    }

    Sequence<T>& operator=(const Sequence<T>& other){
        if (this == &other) {
            return *this;
        }
    
        delete this->data;
    
        const ArraySequence<T>* arrSeq = dynamic_cast<const ArraySequence<T>*>(&other);
        if (!arrSeq) {
            throw std::invalid_argument("Incompatible types in assignment");
        }
    
        int length = arrSeq->GetLength();
        T* newData = new T[length];
        for (int i = 0; i < length; ++i) {
            newData[i] = arrSeq->Get(i);
        }
    
        this->data = new DynamicArray<T>(newData, length);
        this->size = length;
    
        delete[] newData;
        return *this;
    }
    
};

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(int size) : ArraySequence<T>(size) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    ImmutableArraySequence(T* items, int size) : ArraySequence<T>(items, size) {}

    Sequence<T>* Instance() override {
        return new ImmutableArraySequence<T>(*this);
    }

    Sequence<T>& operator=(const Sequence<T>& other){
        if (this == &other) {
            return *this;
        }
    
        delete this->data;
    
        const ArraySequence<T>* arrSeq = dynamic_cast<const ArraySequence<T>*>(&other);
        if (!arrSeq) {
            throw std::invalid_argument("Incompatible types in assignment");
        }
    
        int length = arrSeq->GetLength();
        T* newData = new T[length];
        for (int i = 0; i < length; ++i) {
            newData[i] = arrSeq->Get(i);
        }
    
        this->data = new DynamicArray<T>(newData, length);
        this->size = length;
    
        delete[] newData;
        return *this;
    }
    
};