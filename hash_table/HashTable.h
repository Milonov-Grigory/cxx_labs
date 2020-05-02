//
// Created by krage56 on 02.05.2020.
//

#pragma once

#include <string>

template <typename Value>
class HashTable{

    struct Bucket{
        std::string key;
        Value val;
        Bucket* next;
        Bucket(std::string& k, Value v) : key(k), val(v), next(0){}
        ~Bucket() {}
    };

    Bucket** buckets;

public:

    //HashTable(size_t B, unsigned int (*HF)(const char*));
    HashTable()= default;
    ~HashTable();

    bool has(const char* key) const;
    Value& get(const char* key);
    const Value& get(const char* key) const;
    void insert(const char* key, Value val);

    //friend class iterator;

    class iterator{
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
    iterator end();
private:
    unsigned int (*hashFunc)(const char*);
    size_t capacity;
};

