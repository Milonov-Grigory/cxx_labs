
#pragma once

#include <string>
#include <iostream>
#include <cstring>
template <typename Value>
class HashTable{

    class Bucket{
    public:
        std::string key;
        Value val;
        Bucket* next;
        Bucket(std::string& k, Value v) : key(k), val(v), next(nullptr){}
        ~Bucket()=default;
    };

    Bucket** buckets = nullptr;

public:

    HashTable(size_t B, unsigned int (*HF)(const char*));
    HashTable()= default;
    ~HashTable();

    bool has(const char* key) const;
    Value& get(const char* key);
    const Value& get(const char* key) const;
    void insert(const char* key, Value val);

    //friend class iterator;

    /*class iterator{
        friend class HashTable;
        Bucket* buckets;
        size_t  S;
        size_t  cur_bucket;
        Bucket* cur_element;
        friend class HashTable;
        iterator(Bucket* b, size_t s, size_t cb, Bucket* ce)
                : buckets(b), S(s), cur_bucket(cb), cur_element(ce)
        {}

        public:
            iterator(); // empty
            iterator(const iterator& ) = default;
            iterator& operator++();
            const char* key();
            Value& val();
            const Value& val() const;
            bool operator=(const iterator& it) const;
    };

    iterator begin();
    iterator end();*/
private:
    unsigned int (*hashFunc)(const char*){};
    size_t capacity{};
};


template <typename Value>
HashTable<Value>::HashTable(size_t B, unsigned int (*HF)(const char*)){
    hashFunc = HF;
    capacity = B;
    buckets = new Bucket*[B];
    for(size_t i = 0; i < capacity; ++i){
        buckets[i] = nullptr;
    }
    for(size_t i = 0; i < capacity; ++i){
        if(buckets[i] == nullptr){
            std::cout << "nullptr\n";
        }
    }
}

template <typename Value>
HashTable<Value>::~HashTable(){
    Bucket* currentBucket = nullptr;
    for(size_t i = 0; i < capacity; ++i){
        currentBucket = buckets[i];
        while(currentBucket){
            Bucket* next = currentBucket->next;
            delete currentBucket;
            currentBucket = next;
        }
    }
}


template <typename Value>
bool HashTable<Value>::has(const char* key) const{
    size_t idx = (*hashFunc)(key) % capacity;
    Bucket* it = buckets[idx];
    while(it)
    {
        if(!strcmp(it->key.c_str(), key)) return true;
        it = it->next;
    }
    return false;
}

template <typename Value>
void HashTable<Value>::insert(const char* key, Value v){
    size_t idx = (*hashFunc)(key) % capacity;
    Bucket* currentBucket = buckets[idx];
    std::string str_key = key;
    Bucket* newBucket = new Bucket(str_key, v);
    newBucket->next = currentBucket;
    buckets[idx] = newBucket;
}