/*
 Задание на лабораторную работу №1 по С++
 Тема: Классы и объекты.
 Задание.
 - Создать простой класс.
 - Создать конструкторы и деструктор
 - Создать простой метод
 - Создать несколько объектов этого класса разными способами.
 ( в статике, на стеке, на куче)
 - Продемонстрировать порядок работы конструкторов и деструкторов.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

class Item {
         int _type;
         int _amount;
         double _status;
    public:
        Item():
            _type(0),_amount(1),_status(1.0)
        {
            std::cout << "CSTLOG>>stdcstusd.\n";
        }
        Item(const Item &item) 
        {
            _type=item._type;
            _amount=item._amount;
            _status=item._status;
            std::cout << "CSTLOG>>itmcpycstusd.\n";
        }
        Item(int amount, int type, double status):
            _type(type),_amount(amount),_status(status)
        {
            std::cout << "CSTLOG>>nwcstmcstusd.\n";
        }

        Item& Corrupt(double value)
        {
            _status=_status-value;
            if (_status<0) {
                _amount=0;
            }
            if (_status<0.01) {
                _status=0.01;
            }
            std::cout << "ITMLOG>>itmcrptd.\n";
            return *this;
        }
        Item& Repair(double value)
        {
            _status=_status+value;
            if (_status>1.0) {
                _status=1.0;
            }
            std::cout << "ITMLOG>>itmrprd.\n";
            return *this;
        }
        Item& ChangeType(int type)
        {
            _type=type;
            std::cout << "ITMLOG>>tpcngd.\n";
            return *this;
        }

        Item& operator= (const Item &item)
        {
            _type=item._type;
            _amount=item._amount;
            _status=item._status;
            std::cout << "OPRLOG>>cpyopr.\n";
            return *this;
        }
        Item operator+ (int amount)
        {
            Item buf(*this);
            buf._amount+=amount;
            std::cout << "OPRLOG>>addopr.\n";
            return buf;
        }
        Item& operator++ (int idk_what_is_it)
        {
            *this=*this+idk_what_is_it+1;
            std::cout << "OPRLOG>>incopr.\n";
            return *this;
        }
        
        bool operator== (const Item &item) {
            std::cout << "OPRLOG>>iseqopr.\n";
            if ((_type==item._type)&&(_status==item._status)) {
                return true;
            }
            return false;
        }

        friend std::ostream& operator<< (std::ostream& stream, const Item &item) {
            stream << "Item:\nAmount: " << item._amount << "\nType: " << item._type << "\nStatus: " << item._status << "\n";
        }

        ~Item()
        {
            std::cout << "DSTLOG>>itmdstusd.\n";
        }
};

int main() {
    {
        Item item0;
        static Item item1;
        std::cout<<"static item1 created\n"<<item1<<"destructing item0(nonstatic standart item) and creating new item(3::1::0.74)\n";
    }
    Item item2(3,1,0.74);
    std::cout<<"item2 created\n"<<item2<<"creating new item as item2\n";
    Item item3(item2);
    Item* item4 = new Item[1];
    *item4=item3;
    item4->Corrupt(0.5);
    if (item2==item3) {
        std::cout<<"created item3 as item2\n"<<item3<<"created item4 on heap, item4 copyed item3, item4 corrupted 0.5\n"<<item4<<"\n"<<*item4;
    }
    (*item4)++;
    *item4=*item4+2;
    item4->Repair(1.0);
    item4->ChangeType(2);
    std::cout<<"item4 inscreased, added 2, repaired, changed type\n"<<*item4<<item4<<"\n";
    delete[] item4;
    return 0;
}

