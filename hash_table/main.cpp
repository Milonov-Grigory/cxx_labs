
#include "HashTable.h"

unsigned int HashH37(const char * str){
    unsigned int hash = 2139062143;
    for(; *str; str++)
        hash = 37 * hash + *str;

    return hash;
}

using namespace std;

int main(){

    //HashTable<int, 100, HashH37> htH37;
    HashTable<string> htH37(250, HashH37);
    htH37.insert("Ivanov",    "Ivan");
    htH37.insert("Petrov",    "Slava");
    htH37.insert("Sidorov",   "Sidorovich");
    htH37.insert("Kuznetsov", "Nikita");

    cout << "{" << endl;
    for(auto it = htH37.begin(); it != htH37.end(); ++it){
        cout << "\"" << it.key() << "\" : " << it.val() << " ," << endl;
    }
    cout << "}" << endl;

    if (htH37.has("Ivanov")) htH37.get("Ivanov") = "Edgar";

    cout << "{" << endl;
    for(auto it = htH37.begin(); it != htH37.end(); ++it){
        cout << "\"" << it.key() << "\" : " << it.val() << " ," << endl;
    }
    cout << "}" << endl;

    std::cout << htH37.has("Ivanov");
    std::cout << htH37.has("Petrov");
    std::cout << htH37.has("Sidorov");
    std::cout << htH37.has("Kuznetsov") << endl;
    cout << htH37.get("Ivanov")<< endl;
    cout << htH37.get("Petrov")<< endl;
    cout << htH37.get("Sidorov")<< endl;
    cout << htH37.get("Kuznetsov")<< endl;
    return 0;
}

