#ifndef ARRAYTEMPLATE_H
#define ARRAYTEMPLATE_H



template <typename T>
class Array {
    T* ArrayPointer;
    int LastElement;
    size_t sizeOfArray;
    public:
    ~Array() {
        delete[] ArrayPointer;
    }
    Array(): ArrayPointer(NULL), LastElement(-1), sizeOfArray(0) {}
    Array(const T &firstElement): ArrayPointer(NULL), sizeOfArray(8), LastElement(0) {
        ArrayPointer= new T[8]; 
        ArrayPointer[0]=firstElement;
    }
    Array(const Array<T> &oldArray): ArrayPointer(NULL), LastElement(-1), sizeOfArray(0) {
        reserve(oldArray.LastElement);
        cpy(oldArray.ArrayPointer,ArrayPointer,oldArray.LastElement);
        LastElement=oldArray.LastElement;
    }
    class iterator {
        T* currentPointer;
        public:
        iterator(): currentPointer(begin()) {}
        iterator(T* cp): currentPointer(cp) {}
        T& operator*() {return *currentPointer;}
        void operator=(const iterator& iter) {currentPointer=iter.currentPointer;}
        void operator++(int) {currentPointer++;}
        void operator++() {currentPointer++;}
        void operator--() {currentPointer--;}
        void operator--(int) {currentPointer--;}
        bool operator== (const iterator& iter) {return (currentPointer==iter.currentPointer);}
        bool operator!= (const iterator& iter) {return (currentPointer!=iter.currentPointer);}
    };
    iterator begin() {
        return iterator(ArrayPointer);
    }
    iterator end() {
        return iterator(ArrayPointer+LastElement+1);
    }
    private:
    void cpy(T* oldPointer, T* newPointer, const int &LastElementOffset) {
        if (LastElementOffset<0) {return;}
        if ((newPointer>oldPointer)&&(newPointer<(oldPointer+LastElementOffset))) {
            for (int i=LastElementOffset; i>=0; i--) {
                new(newPointer+i) T(*(oldPointer+i));
            }          
        } else if ((oldPointer>newPointer)&&(oldPointer<(newPointer+LastElementOffset))) {
            for (int i = 0; i<=LastElementOffset; i++) {
                new(newPointer+i) T(*(oldPointer+i));
            }

        } else {
            for (int i = 0; i<=LastElementOffset; i++) {
                new(newPointer+i) T(*(oldPointer+i));
            }
        }
    }
    void reserve(const size_t &neededSize) {
        if (!ArrayPointer) {
            ArrayPointer = new T[8];
            LastElement = -1;
            sizeOfArray = 8;
        }
        while (neededSize>=sizeOfArray) {       
            sizeOfArray=sizeOfArray<<1;
            T* newptr = new T[sizeOfArray];
            cpy(ArrayPointer,newptr,LastElement);
            delete[] ArrayPointer;
            ArrayPointer=newptr;
        }
    }
    void optimize() {
        Array buf(*this);
        (*this)=buf;
    }
    public:
    void add(const T &newElement) {
        if (!ArrayPointer) {
            ArrayPointer = new T[8];
            ArrayPointer[0]=newElement;
            LastElement = 0;
            sizeOfArray=8;
        } else {
            reserve(LastElement + 1);
            LastElement++;
            new(ArrayPointer+LastElement) T(newElement);
        }
    }
    void insert(const T &newElement, const int &pos) {
        if (pos<0) {return;}
        if (pos>LastElement) {
            add(newElement);
        } else {
            reserve(LastElement+1);
            LastElement++;
            cpy(ArrayPointer+pos,ArrayPointer+pos+1,LastElement-pos);
            new(ArrayPointer+pos) T(newElement);
        }
    }
    void pushBack(const T &newElement) {
        insert(newElement,0);
    }
    void eraze(const int &pos) {
        if (pos<0) {return;}
        if (pos<=LastElement) {
            cpy(ArrayPointer+pos+1,ArrayPointer+pos,LastElement-pos);
            LastElement--;
        }
        optimize();
    }
    T operator[] (const int &offset) {
        return *(ArrayPointer+offset);
    }
    void operator= (const Array<T> &array) {
        if (ArrayPointer!=array.ArrayPointer) {delete[] ArrayPointer;}
        reserve(array.LastElement);
        cpy(array.ArrayPointer,ArrayPointer,array.LastElement);
        LastElement=array.LastElement;
    }
    int ioLastElement() {return LastElement;}
};


#endif //ARRAYTEMPLATE_H
