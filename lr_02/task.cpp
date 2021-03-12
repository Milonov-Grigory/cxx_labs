#include <iostream>
#include <cmath>
#include "arraytemplate.h"

int main (void) {
    Array<int> testarray;
    testarray.add((15));
    testarray.add((14));
    testarray.add((13));
    testarray.add((12));
    testarray.add((11));
    testarray.add((10));
    testarray.add((9));
    std::cout<<"Array : ";
    Array<int>::iterator iter;
    for (iter = testarray.begin(); iter!=testarray.end(); iter++) {
        std::cout << *iter << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Erase №3 (#4) (inverted) : ";
    testarray.eraze(3);
    for (Array<int>::iterator iter2 = (iter--)--; iter2>=testarray.begin(); iter2--) {
        std::cout << *iter2 << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Insert 5 at pos 3 : ";
    testarray.insert((5),3);
    for (int i = 0; i<=testarray.ioLastElement(); i++) {
        std::cout << testarray[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Insert 1 at pos 100 : ";
    testarray.insert((1),100); 
    for (int i = 0; i<=testarray.ioLastElement(); i++) {
        std::cout << testarray[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Copy to new Array : ";
    Array<int> testarray2;
    testarray2=testarray;
    for (int i = 0; i<=testarray2.ioLastElement(); i++) {
        std::cout << testarray2[i] << " ";
    }
    std::cout<<std::endl;
    std::cout<<"Copyed Array : ";
    for (int i = 0; i<=testarray.ioLastElement(); i++) {
        std::cout << testarray[i] << " ";
    }
    std::cout<<std::endl;

    return 0;
}
