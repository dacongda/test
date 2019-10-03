#include <iostream>
#include "FileC.h"
#include <string>
#include <fstream>
namespace FilC
{
	void FileOp(std::string name)
	{
		std::fstream File(name);
		if (File.fail())
		{
			std::cout << "Failed open" << std::endl;
			std::cout << "if you want to create a new one?Y /N" << std::endl;
			char a;
			std::cin >> a;
			if (a == 'Y')
			{
				FileNw(name);
				FileOp(name);
			}
			else if (a == 'N')
			{
				exit(0);
			}
			else
			{
				std::cout << "wrong input" << std::endl;
				FileCg(name);
			}
		}else{
		std::string Fileinf;
		File >> Fileinf;
		std::cout << Fileinf << std::endl;
		File.close();
		std::cout << "successful" << std::endl;
		}
	}
	void FileCg(std::string name)
	{	
		std::fstream File(name);
		if (File.fail())
		{
			std::cout << "Failed open" << std::endl;
			std::cout << "if you want to create a new one?Y /N" << std::endl;
			char a;
			std::cin >> a;
			if (a == 'Y')
			{
				FileNw(name);
				FileCg(name);
			}
			else if (a == 'N')
			{
				exit(0);
			}
			else
			{
				std::cout << "wrong input" << std::endl;
				FileCg(name);
			}
		}
		else{
		std::cout << "what do you want to input" << std::endl;
		std::string inf;
		std::cin >> inf;
		File << inf.data();
		File.close();
		std::cout << "sucessful cp" << std::endl;
		}
	}
	void FileAd(std::string name)
	{
		std::fstream File(name,std::ios::app);
		if (File.fail())
		{
			std::cout << "Failed open" << std::endl;
			std::cout << "if you want to create a new one?Y /N" << std::endl;
			char a;
			std::cin >> a;
			if (a == 'Y')
			{
				FileNw(name);
				FileCg(name);
			}
			else if (a == 'N')
			{
				exit(0);
			}
			else
			{
				std::cout << "wrong input" << std::endl;
				FileCg(name);
			}
		}
		else {
			std::cout << "what do you want to input" << std::endl;
			std::string inf;
			std::cin >> inf;
			File << inf.data();
			File.close();
			std::cout << "sucessful cp" << std::endl;
		}
	}
	void FileNw(std::string name)
	{
		std::ofstream File(name);
		File.close();
	}
}