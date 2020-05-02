//
// Created by krage56 on 02.05.2020.
//

#include "HashTable.h"
/*template <typename Value>
HashTable<Value>::HashTable(size_t B, unsigned int (*HF)(const char*)){
    hashFunc = HF;
    capacity = B;
    buckets = new Bucket*[B];
    for(Bucket** it = buckets; it != buckets+B; ++it) *it = nullptr;
}*/

template <typename Value>
HashTable<Value>::~HashTable(){
    for(Bucket** it = buckets; it != buckets+capacity; ++it)
    {
        while (*it)
        {
            Bucket* next = *it->next;
            delete *it;
            *it = next;
        }
    }
}


template <typename Value>
bool HashTable<Value>::has(const char* key) const{
    size_t idx = (*hashFunc)(key) % capacity;
    Bucket* it = buckets[idx];
    while(it)
    {
        if(!strcmp(it->key,key)) return true;
        it = it->next;
    }
    return false;
}

template <typename Value>
void HashTable<Value>::insert(const char* key, Value v){
    size_t idx = (*hashFunc)(key) % capacity;
    Bucket* cur = buckets[idx];

    Bucket* newBucket = new Bucket(key, v);
    newBucket->next = cur;
    buckets[idx] = newBucket;
}

///////////



