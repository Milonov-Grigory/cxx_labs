
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

    class iterator{
        friend class HashTable;
        Bucket** buckets;
        size_t  S;//пусть будет количество бакетов
        size_t  cur_bucket;
        Bucket* cur_element;
        friend class HashTable;
        iterator(Bucket** b, size_t s, size_t cb, Bucket* ce)
                : buckets(b), S(s), cur_bucket(cb), cur_element(ce)
        {}

        public:
            iterator() = default; // empty
            iterator(const iterator& ) = default;
            bool operator!=(iterator& it) const{
                return this->cur_element != it.cur_element;
            }
            bool operator!=(iterator&& it) const{
                return this->cur_element != it.cur_element;
            }
            void operator++() {
                if(cur_element && (cur_element->next || cur_bucket == S - 1)){
                    cur_element = cur_element->next;
                }
                else{
                    for (size_t i = cur_bucket; i < S; ++i) {
                        cur_element = buckets[i];
                        if (cur_element) {
                            break;
                        }
                    }
                }

            }

            const char* key();
            Value& val();
            const Value& val() const;
            iterator& operator=(const iterator& it) const {
                buckets = it.buckets;
                S = it.S;
                cur_bucket = it.cur_bucket;
                cur_element = it.cur_element;
            }
            iterator& operator=(iterator&& it) noexcept {
                *this = std::move(it);
                return *this;
            }
    };

    iterator begin() {
        Bucket* result = nullptr;
        size_t count = 0;
        while(!result && count < capacity){
            result = buckets[count];
            ++count;
        }
        return iterator(buckets, capacity, count, result);
    }

    iterator end() {
        Bucket* result = nullptr;
        size_t i = this->begin().cur_bucket;
        for(i ; i < capacity; ++i){
            result = buckets[i];
            if(result) {
                while (result->next) {
                    result = result->next;
                }
            }
        }
        return iterator(buckets, capacity, i, result);
    }

private:
    unsigned int (*hashFunc)(const char*){};
    size_t capacity;
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


