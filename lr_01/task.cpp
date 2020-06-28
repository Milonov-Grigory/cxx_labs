/*
 Задание на лабораторную работу №1 по С++
 Тема: Классы и объекты.
 Задание.
 - Создать простой класс. +
 - Создать конструкторы и деструктор. +
 - Создать простой метод. +
 - Создать несколько объектов этого класса разными способами. +
 ( в статике, на стеке, на куче)
 - Продемонстрировать порядок работы конструкторов и деструкторов. +
*/

#include <iostream>

class A {
    public:
        A();
        A(int a);
        ~A();
        
        void printPrivateInt();
    private:
        int m_a;
     
};

A a0 = A();

int main(int argc, char ** argv) {
    A *a1 = new A(1);
    A a2 = A(2);
    a0.printPrivateInt();
    a1->printPrivateInt();
    a2.printPrivateInt();
    
    delete a1;
    return 0;
}

A::A() {
    std::cout << "A constructor()" << std::endl;
    m_a = 0;
}

A::A(int a) {
    std::cout << "A constructor(int a)" << std::endl;
    m_a = a;
}

A::~A() {
    std::cout << "A destructor" << std::endl;
}

void A::printPrivateInt() {
    std::cout << m_a << std::endl;
}