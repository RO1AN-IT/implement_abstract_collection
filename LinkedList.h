#pragma once
#include "Container.h"

template<typename T>
class LinkedList: public Container<T> {
public:
    LinkedList(): head(nullptr), end(nullptr), size(0){}

    LinkedList(int size): head(nullptr), end(nullptr), size(size){}

    LinkedList(T* items, int count): size(count){
        for(int i = 0; i < count; i++){
            append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& other): head(nullptr), end(nullptr){
        size = other.size;
        Node* src = other.head;
        Node** current = &head;
        other.end = nullptr;
        for(int i = 0; i < other.size; i++){
            *current = new Node;
            (*current)->data = src->data;
            (*current)->next = nullptr;
            end = *current;
            current = &((*current)->next);
            src = src->next;

            size++;
        } 
    }

    LinkedList(const LinkedList<T>&& other){
        head = other.head;
        end = other.end;
        size = other.size;

        other.head = nullptr;
        other.end = nullptr;
        other.size = 0;
    }

    LinkedList& operator=(const LinkedList<T>& other){
        if(this == &other){
            return *this;
        }
        if(head){
            delete head;
        }
        head = nullptr;
        end = nullptr;
        size = 0;
        Node* src = other.head;
        Node** current = &head;
        for(int i = 0; i < other.size; i++){
            *current = new Node;
            (*current)->data = src->data;
            (*current)->next = nullptr;
            end = *current;
            current = &((*current)->next);
            src = src->next;
        } 
        size = other.size;
        return *this;
    }

    LinkedList& operator=(const LinkedList<T>&& other){
        if(this == &other){
            return *this;
        }
        if(head){
            delete head;
        }
        head = nullptr;
        end = nullptr;
        size = 0;

        head = other.head;
        end = other.end;
        size = other.size;

        other.head = nullptr;
        other.end = nullptr;
        other.size = 0;
        return *this;
    }

    T& operator[](int index){
        if(index < 0 || index >= size){
            //error
        }

        Node* current = head;

        for(int i = 0; i < index; i++){
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const{
        if(index < 0 || index >= size){
            //error
        }

        Node* current = head;

        for(int i = 0; i < index; i++){
            current = current->next;
        }
        return current->data;
    }



    void append(T value) override{
        if(head == nullptr){
            head = new Node;
            head->data = value;
            head->next = nullptr;
            end = head;
            size = 1;
            return;
        }

        Node* last = end;
        last->next = new Node;
        (last->next)->data = value;
        (last->next)->next = nullptr;
        end = last->next;
        size++;
    }   

    void prepend(T value) override{
        if(head == nullptr){
            head = new Node;
            head->data = value;
            head->next = nullptr;
            end = head;
            size = 1;
            return;
        }

        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        size++;
    }

    void insertAt(T item, int index) override {
        if(index < 0 || index >= size){
            //error
            //return 0;
        }

        Node* last = head;
        for(int i = 0; i < index; i++){
            last = last->next;
        }

        Node* current = new Node;
        current->data = item;
        current->next = (last->next)->next;
        last->next->next = current;
        size++;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex){
        LinkedList<T>* sublist = new LinkedList<T>();

        if(startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size || startIndex < endIndex){
            //error
            return sublist;
        }

        if(head == nullptr){
            //error
            return sublist;
        }

        Node* current = head;
        for(int i = 0; i < startIndex; i++){
            current = current->next;
        }

        for(int i = startIndex; i < endIndex; i++){
            sublist->append(current->data);
            current = current->next;
        }

        return sublist;
    }

    LinkedList<T>* Concat(LinkedList<T> *list){
        if(list == nullptr){
            //error
            return nullptr;
        }
        if(head == nullptr){
            return list;
        }
        if(list->head == nullptr){
            return this;
        }
        end->next = list->head;
        end = list->end;
        size += list->size;
        list->head = nullptr;
        list->end = nullptr;
        list->size = 0;
        return this;

        // //LinkedList<T>* concat_list = new LinkedList<T>();   

        // Node* current = head;
        // for(int i = 0; i < size; i++){
        //     concat_list->append(current->data);
        //     current = current->next;
        // }

        // current = list->head;
        // for(int i = 0; i < list->size; i++){
        //     concat_list->append(current->data);
        //     current = current->next;
        // }

        // return concat_list;
    }

    T getFirst() const override{
        if(head == nullptr){
            //error
            return 0;
        }
        return head->data;
    }

    T getLast() const override{
        if(head == nullptr){
            //error
            return 0;
        }
        return end->data;
    }

    T& get(int index) const override{
        if(index < 0 || index >= size){
            //error
        }

        Node* current = head;
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        return current->data;
    }

    int getSize() const override{
        return size;
    }

    T* getData() const override{
        T* data = new T[size];
        Node* current = head;
        for(int i = 0; i< size; i++){
            data[i] = current->data;
             current = current->next;
        }
        return data;
    } 

    ~LinkedList() {
        Node* next = nullptr;
        Node* now = this->head;

        while(now != nullptr){
            next = now->next;
            delete now;
            now = next;
        }
    }

private:
    struct Node
    {
        T data;
        Node* next;
    };
    Node* head;
    Node* end;
    int size;
};