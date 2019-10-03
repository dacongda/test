#include <iostream>
#include <string>
#include "FileC.h"
int main()
{
	using namespace std;
	string name;
    std::cout << "what file you want to open"<<endl;
	std::cin >> name;
	FilC::FileOp(name);
	FilC::FileCg(name);
}
