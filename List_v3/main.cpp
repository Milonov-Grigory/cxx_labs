#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    std::cout << "Start" << std::endl;

    TList<int> ListI;
    TList<double> ListD;
    TList<float> ListF;
    TList<char> ListC;

    std::cout << "Insert 99" << std::endl;
    try
    {
        ListI.Insert(99);
        ListI.Print();
    }
    catch(...)
    {
        cout << endl << "Exception! " << std::endl;
    }

    std::cout << "Insert 98" << std::endl;
    ListI.InsertAt(98, 99);
    ListI.Print();

    std::cout << "Insert 97" << std::endl;
    ListI.InsertAt(97, 99);
    ListI.Print();

    std::cout << "Erase 97" << std::endl;
    ListI.EraseValue(97);
    ListI.Print();

    std::cout << "Erase 98" << std::endl;
    ListI.EraseValue(98);
    ListI.Print();

    std::cout << "Clear" << std::endl;
    ListI.Clear();
    ListI.Print();
	
    std::cout << "Add 99" << std::endl;
    ListI.Add(99);
    ListI.Print();

    std::cout << "Add 33" << std::endl;
    ListI.Add(33);
    ListI.Print();

    int value = 66;

    std::cout << "Exist " << value << std::endl;
    if (ListI.Exist(value) == true)
    {
        std::cout << value << " Exists" << std::endl;
    }
    else
    {
        std::cout << value << " Doesn't Exist" << std::endl;
    }

    for(auto it = ListI.begin(); it != ListI.end(); it = ListI.next(it))
    {
        std::cout << "Added " << *it << std::endl;
    }

    std::cout << "Insert 'A'" << std::endl;
    ListC.Insert('A');
    ListC.Print();

    std::cout << "Insert 'C'" << std::endl;
    ListC.InsertAt('C', 'B');
    ListC.Print();

    std::cout << "Insert 'B'" << std::endl;
    ListC.InsertAt('B', 'A');
    ListC.Print();

    std::cout << "Insert 'E'" << std::endl;
    ListC.InsertAt('E', 'C');
    ListC.Print();
	
    for(auto it = ListC.begin(); it != ListC.end(); ++it)
    {
        std::cout << "Inserted " << *it << std::endl;
    }

    std::cout << "End" << std::endl;

    std::cout << "Insert 65 at pos 0" << std::endl;
    ListI.Insert(65, 0);
    ListI.Print();

    std::cout << "Insert 43 at pos 0" << std::endl;
    ListI.Insert(43, 0);
    ListI.Print();

    std::cout << "Insert 15 at pos 999" << std::endl;
    ListI.Insert(15, 999);
    ListI.Print();

    std::cout << "Erase from pos 0" << std::endl;
    ListI.ErasePos(0);
    ListI.Print();

    std::cout << "EndEnd" << std::endl;

    return 0;
}


