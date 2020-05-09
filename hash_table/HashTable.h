
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
    class iterator{
        friend class HashTable;
        Bucket** buckets;
        size_t  S;
        size_t  cur_bucket;
        Bucket* cur_element;
        friend class HashTable;
        iterator(Bucket** b, size_t s, size_t cb, Bucket* ce)
                : buckets(b), S(s), cur_bucket(cb), cur_element(ce)
        {}

        public:
            iterator() = default; // empty
            iterator(const iterator& ) = default;
            bool operator!=(iterator& it) const;
            bool operator!=(iterator&& it) const;
            void operator++();
            std::string& key() {
                return cur_element->key;
            }
            Value& val() {
                return cur_element->val;
            }
            const Value& val() const {
                return cur_element->val;
            }

            iterator& operator=(const iterator& it) const;
            iterator& operator=(iterator&& it) noexcept ;
    };

    iterator begin();

    iterator end();

private:
    unsigned int (*hashFunc)(const char*){};
    size_t capacity;
};

template<typename Value>
bool HashTable<Value>::iterator::operator!=(HashTable::iterator &it) const {
    return this->cur_element != it.cur_element;
}

template<typename Value>
bool HashTable<Value>::iterator::operator!=(HashTable::iterator &&it) const {
    return this->cur_element != it.cur_element;
}

template<typename Value>
void HashTable<Value>::iterator::operator++() {
    if(cur_element && (cur_element->next || cur_bucket == S - 1)){
        cur_element = cur_element->next;
    }
    else if(cur_element || cur_bucket != S - 1){
        for (size_t i = cur_bucket + 1; i < S; ++i) {
            cur_element = buckets[i];
            if (cur_element) {
                cur_bucket = i;
                break;
            }
        }
    }
}

template<typename Value>
typename HashTable<Value>::iterator &HashTable<Value>::iterator::operator=
        (const HashTable::iterator &it) const{
        buckets = it.buckets;
        S = it.S;
        cur_bucket = it.cur_bucket;
        cur_element = it.cur_element;
}

template<typename Value>
typename HashTable<Value>::iterator
&HashTable<Value>::iterator::operator=(HashTable::iterator &&it)noexcept {
    *this = std::move(it);
    return *this;
}


template <typename Value>
HashTable<Value>::HashTable(size_t B, unsigned int (*HF)(const char*)){
    this->hashFunc = HF;
    capacity = B;
    buckets = new Bucket*[B];
    for(size_t i = 0; i < capacity; ++i){
        buckets[i] = nullptr;
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
    size_t idx = (*this->hashFunc)(key) % capacity;
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
    size_t idx = (*this->hashFunc)(key) % capacity;
    Bucket* currentBucket = buckets[idx];
    std::string str_key = key;
    Bucket* newBucket = new Bucket(str_key, v);
    newBucket->next = currentBucket;
    buckets[idx] = newBucket;
}

template<typename Value>
Value &HashTable<Value>::get(const char *key) {
    size_t idx = (*this->hashFunc)(key) % capacity;
    for(auto* it = buckets[idx]; it != nullptr; it = it->next){
        if(it->key == key){
            return it->val;
        }
    }
    throw std::invalid_argument("Didn`t find");
}

template<typename Value>
const Value &HashTable<Value>::get(const char *key) const {
    size_t idx = (*this->hashFunc)(key) % capacity;
    for(auto* it = buckets[idx]; it != nullptr; it = it->next){
        if(it->key == key){
            return it->val;
        }
    }
    throw std::invalid_argument("Didn`t find");
}

template<typename Value>
typename HashTable<Value>::iterator HashTable<Value>::begin() {
    Bucket* result = nullptr;
    size_t count = 0;
    while(!result && count < capacity ){
        result = buckets[count];
        ++count;
    }
    return iterator(buckets, capacity, count - 1, result);
}

template<typename Value>
typename HashTable<Value>::iterator HashTable<Value>::end() {
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
    return iterator(buckets, capacity, i - 1, nullptr);
}

