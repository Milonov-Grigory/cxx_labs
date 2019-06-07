#include <iostream>
#include"array.h"
using namespace std;

int main(int argc, char *argv[])
{
    bool cont = 1;
    int a;
    Array<int> arr;
    while(cont){
	cout<<"1) Push back"<<endl;
	cout<<"2) Insert"<<endl;
	cout<<"3) Erase"<<endl;
	cout<<"4) Print"<<endl;
        cout<<"5) Exit"<<endl;
	cout<<"Enter action : ";
	cin>>a;
	switch(a){
		case 1:
		{
		    cout<<"Value : ";
		    int val;
		    cin>>val;
		    arr.push_back(val);
                    break;
		}
		case 2:
		{
		    cout<<"Pos : ";
		    size_t pos;
		    cin>>pos;
		    int val;
		    cout<<"Value : ";
		    cin>>val;
		    arr.insert(val,pos);
                    break;
	 	}
		case 3:
		{
		    cout<<"Pos : ";
		    size_t pos;
		    cin>>pos;
                    arr.erase(pos);
                    break;
		}
		case 4:
                {
		    arr.print();
                    break;
                }
		case 5:
                {
                    cont = 0;
                    break;
                }
        }
    }
	return (0);
}
