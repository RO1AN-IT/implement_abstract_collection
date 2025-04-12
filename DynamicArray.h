#pragma once
#include "Container.h"

template<typename T>
class DynamicArray: public Container<T> {

public:
    DynamicArray(): data(nullptr), size(0) {}

    DynamicArray(int size): data(nullptr), size(size) {} 

    DynamicArray(const DynamicArray<T>& other) : DynamicArray(other.data, other.size) {}

    DynamicArray(T* items, int size): size(size) {
        if(size < 0){
            //error: throw std::invalid_argument("Size must be positive");
        }
        if(size == 0){
            data = nullptr;
            return;
        }
        data = new T[size];
        for(int i = 0; i < size; i++){
            data[i] = items[i];
        }
    }

    DynamicArray(DynamicArray<T>&& other) {
        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;
    }

    ~DynamicArray(){
        delete[] data;
    }

    T& operator[](int index) {
        if (index >= size || index < 0) {
            // Ошибка: throw std::out_of_range("Index out of range");
            return data[0];
        }
        return data[index];
    }

    const T& operator[](int index) const{
        if(index >= size || index < 0){
            //error : throw std::out_of_range("Index out of range");
            return data[0];
        }
        return data[index];
    }

    DynamicArray& operator=(const DynamicArray<T>& other){
        if(this == &other){
            return *this;
        }

        if(data){
            delete[] data;
        }

        data = new T[other.size];
        size = other.size;
        for(int i = 0; i < size; i++){
            data[i] = other.data[i];
        }
        return *this;
    }

    DynamicArray& operator=(const DynamicArray<T>&& other){
        if(this == &other){
            return *this;
        }

        if(data){
            delete[] data;
        }

        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;
        return *this;
    }

    T* getData() const override{
        return data;
    }

    T& get(int index) const override{
        if(index < 0 || index >= size){
            //erro: throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T getFirst() const override{
        if(size == 0){
            //error: throw std::out_of_range("Array is empty");
        }
        return data[0];
    }

    T getLast() const override{
        if(size == 0){
            //error: throw std::out_of_range("Array is empty");
        }
        return data[size - 1];
    }

    int getSize() const override{
        return size;
    }

    void Set(int index, const T& value){
        if(index < 0 || index >= size){
            //error: throw std::out_of_range("Index out of range");
            return;
        }
        data[index] = value;
    }

    void Set(int index, const T&& value){
        if(index < 0 || index >= size){
            //error: throw std::out_of_range("Index out of range");
            return;
        }
        data[index] = std::move(value);
    }

    void Resize(int newSize){
        if(newSize < 0){
            //error: throw std::invalid_argument("Size must be positive");
            return;
        }

        T* newData = new T[newSize];
        
        if(!data){
            data = newData;
            size = newSize;
            return;
        }

        for(int i = 0; i < size && i < newSize; i++){
            newData[i] = data[i];   
        }

        delete[] data;
        data = newData;
        size = newSize;
    }

    void append(T element) override{
        Resize(size + 1); 
        data[size - 1] = element;
    }

    void prepend(T element) override{
        Resize(size + 1);
        for(int i = size - 1; i > 0; i--){
            data[i] = data[i - 1];
        }
        data[0] = element;
    }

    void insertAt(T item, int index) override {
        if(index < 0 || index >= size){
            //error: throw std::out_of_range("Index out of range");
            return;
        }
        Resize(size + 1);
        for(int i = size - 1; i > index; i--){
            data[i] = data[i - 1];
        }
        data[index] = item;
    }
    
private:
    T* data;
    size_t size;

};
