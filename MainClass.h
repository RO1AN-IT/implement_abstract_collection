#pragma once

template<typename T>
class DynamicArray {
    public:
        DynamicArray(): data(nullptr), size(0) {}

        DynamicArray(int size): size(size) {
            data = new T[size];
        }

        DynamicArray(const DynamicArray<T>& other) {
            data = new T[other.size];
            size = other.size;
            for(int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }

        DynamicArray(T* items, int size): data(items), size(size) {}

        DynamicArray(DynamicArray<T>&& other) {
            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
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

        ~DynamicArray(){
            delete[] data;
        }

        T Get(int index){
            if(index < 0 || index >= size){
                //erro: throw std::out_of_range("Index out of range");
                return T{};
            }
            return data[index];
        }

        int GetSize(){
            return size;
        }

        void Set(int index, const T& value){
            if(index < 0 || index >= size){
                //error: throw std::out_of_range("Index out of range");
                return;
            }
            data[index] = value;
        }

        void Set(int insex, const T&& value){
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

            for(int i = 0; i< size && i < newSize; i++){
                newData[i] = data[i];   
            }

            delete[] data;
            data = newData;
            size = newSize;
        }
    private:
        T* data;
        syze_t size;
};
