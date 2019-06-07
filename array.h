#ifndef ARRAY_H
#define ARRAY_H
#include<iostream>
#include<stdlib.h>
#include<stdexcept>

template<typename T>
class Array
{
private:
        T* ptr;
        size_t size;
        size_t capacity;
public:
    struct Iterator{
        T* mas;
        Iterator():mas(NULL){}
        Iterator(const Iterator &iter1):mas(iter1.mas){}
        Iterator(T* _begin):mas(_begin){}
        T& operator*(){return *mas;}
        T& operator++(){mas++;return *mas;}
        T& operator--(){mas--;return *mas;}
        bool operator!=(const Iterator &iter1){return mas != iter1.mas;}
    };

    Array():ptr(NULL),size(0),capacity(0){}
    ~Array(){
        for(int i = 0;i < size;i++){
            (ptr + i)->~T();
        }
        delete (ptr);
    }
    Array(const Array<T> &arr){
        if(!arr.ptr){
            ptr = NULL;
            size = 0;
            capacity = 0;
        }
        else{
            char* buf = new char [sizeof(T) * arr.capacity];
            ptr = reinterpret_cast<T*>(buf);
            for(int i = 0;i < arr.size;i++){
                new (ptr + i) T (*(arr.ptr + i));
            }
            size = arr.size;
            capacity = arr.capacity;
        }
    }

    T& operator[](size_t index){
        try
        {
            if(index < size){
                return *(ptr + index);
            }
            else {
                throw std::out_of_range("Out of bounds");
            }
        }
        catch(std::exception e){
            std::cout<<"Out of bounds"<<std::endl;
            exit(0);
        }
    }

    void insert(T element,size_t pos){
        try
        {
            if(pos < size){
                if(size == capacity){
                    capacity*=2;
                    char* buf = new char [sizeof(T) * capacity];
                    T* buf1 = reinterpret_cast<T*>(buf);
                    for (size_t i = 0;i < pos;i++){
                        new (buf1 + i) T (*(ptr + i));
                    }
                    new (buf1 + pos) T (element);
                    for(size_t i = pos + 1;i <= size;i++){
                        new (buf1 + i) T (*(ptr + i - 1));
                    }
                    for(int i = 0;i < size;i++){
                        (ptr + i)->~T();
                    }
                    delete(ptr);
                    ptr = buf1;
                }
                else{
                    for(int i = size;i >= pos + 1;i--){
                        new (ptr + i) T (*(ptr + i - 1));
                        (ptr + i - 1)->~T();
                    }
                    new (ptr + pos) T (element);
                }
            }
            else{
                throw std::out_of_range("Out of bounds");
            }
            size++;
        }
        catch(std::exception e){
            std::cout<<"Out of bounds"<<std::endl;
            exit(0);
        }
    }
    void insert(T element,Iterator pos){
        Iterator pos_finder(begin());
        int idx = 0;
        while(pos_finder != pos){
            ++pos_finder;
            ++idx;
        }
        insert(element,idx);
    }
    void erase(size_t pos){
        try{
            if(pos < size && size != 0){
                for(size_t i = pos;i < size - 1;i++){
                    new (ptr + i) T (*(ptr + i + 1));
                    (ptr + i + 1)->~T();
                }
                    size--;
                while(size <= capacity/2){
                    capacity/=2;
                    char* buf = new char [sizeof(T) * capacity];
                    T* buf1 = reinterpret_cast<T*>(buf);
                    for(size_t i = 0;i < size;i++){
                        new (buf1 + i) T (*(ptr + i));
                    }
                    for(size_t i = 0;i < size;i++){
                        (ptr + i)->~T();
                    }
                    delete(ptr);
                    ptr = buf1;
                    }
            }
            else{
                throw std::out_of_range("Out of bounds");
            }
        }
        catch(std::exception e){
            std::cout<<"Out of bounds"<<std::endl;
            exit(0);
        }
    }
    void push_back(T element){
        if(size == capacity){
            if(size == 0){
                char* buf = new char[sizeof(T)];
                ptr = reinterpret_cast<T*>(buf);
                capacity = 1;
            }
            else{
                capacity*=2;
                char* buf = new char[sizeof(T) * capacity];
                T* buf1 = reinterpret_cast<T*>(buf);
                for(int i = 0;i < size;i++){
                    new (buf1 + i) T (*(ptr + i));
                }
                for(int i = 0;i < size;i++){
                    (ptr + i)->~T();
                }
                delete(ptr);
                ptr = buf1;
            }
        }
        size++;
        new (ptr + size - 1) T (element);
    }
    size_t getSize(){return size;}
    Iterator begin(){
        return Iterator(ptr);
    }
    Iterator end(){
        return Iterator((ptr + size - 1));
    }
    void print(){
        for(int i = 0;i < size;i++){
            std::cout<<*(ptr + i);
        }
        std::cout<<std::endl;
    }
};
#endif // ARRAY_H
