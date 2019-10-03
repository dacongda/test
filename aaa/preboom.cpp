#include "boom.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <random>
void boom::nwg()
{
	using namespace std;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int x = (rand() % 20 % 10) + 1;
		int y = (rand() % 20 % 10) + 1;
		if (save[x][y] != 0)
		{
			rndfix(x, y);
		}
		else {
			save[x][y] = 10;
			for (int xc = -1; xc <2; xc += 1)
			{
				for (int yc = -1; yc <2; yc += 1)
				{
					if (x + xc > 10 || y + yc > 10 || x + xc < 1 || y + yc < 1)
					{
						continue;
					}
					else {
						if (xc == 0 && yc == 0)
							continue;
						else
							save[x + xc][y + yc] += 1;
					}
				}
			}
		}
	}
}
void boom::rndfix(int& x, int& y) {
	x = (rand() % 20 % 10) + 1;
	y = (rand() % 20 % 10) + 1;
	if (save[x][y] != 0)
	{
		rndfix(x, y);
	}
	else {
		save[x][y] = 10;
		for (int xc = -1; xc <= 1; xc ++)
		{
			for (int yc = -1; yc <= 1; yc ++)
			{
				if (x + xc > 10 || y + yc > 10 || x + xc < 1 || y + yc < 1)
				{
					break;
				}
				else {
					if (xc == 0 && yc == 0)
						continue;
					else
						save[x + xc][y + yc] += 1;
				}
			}
		}
	}

}
void boom::reg()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			save[i][j] = 0;
			for (int i = 0; i < 11; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					outer[i][j] = '#';
				}
			}
			ticker[i][j] = 0;
		}
	}
}
void boom::over() 
{
	std::cout << "gameover!";
}
void boom::clean(const int& x, const int& y)//清除
{
	if(ticker[y][x]==0)//若没被标记
	{
	outer[y][x] = save[y][x]+'0';
	ticker[y][x] = 1;//若清除则标记
	if(y<1||x<1||y>10||x>10){}
	else {
		lastblock -= 1;
	}//剩余方格减一
	}
	else {
		std::cout << "The block has been ticked" << std::endl;
	}//若已标记
}
void boom::finder(const int x, const int y)//发现
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if(((x+i==x)&&(y+j==y))||x+i<1||y+j<1||x+i>10||y+j>10)//若超出数组范围或为自己则跳过
			{
				continue;
			}
			else
			{
				if(ticker[y+j][x+i]!=0)//若被标记或者为雷则跳过
				{
					continue;
				}
				else if(save[y+j][x+i]==0)
				{
					clean(x + i,y + j);
					finder(x + i, y + j);
				}
				else if ((1 <= save[y+j][x+i]) && (save[y+j][x+i]) <= 8)
				{
					clean(x + i, y + j);
				}
			}
		}
	}

}
bool boom::chose(const int& x, const int& y, const char& mode)
{if(x<1||x>10||y<1||y>10)
{
	std::cout << "x and y must betwen 1 to 10" << std::endl;
	return true;
}
else{
	switch (mode)
	{
	case '0' :
		if (ticker[y][x] != 0)
		{
			std::cout << "has ticked" << std::endl;
		}
		if (save[y][x] >= 10)//踩中雷原地爆炸
		{
			over();
			return false;
		}
		else if (1 <= save[y][x] && save[y][x] <= 8)
		{
			clean(x, y);//该格有数字
			return true;
		}
		else if (save[y][x] == 0)
		{
			clean(x, y);
			finder(x, y);//为零则开始自动发现
			return true;
		}
	case '1':
		tic(x, y);
		return true;
	case '2':
		detic(x, y);
		outer[y][x] = '#';
		return true;
	case '3':
		return false;
	case '4':
		this->saves();
		return true;
	case '5':
		this->reads();
		return true;
	default:
		std::cout << "wrong input of mode ,PLZ enter again" << std::endl;
		break;
	}
	}
return true;
}
void boom::view()//输出数组
{
	std::cout << "    ";
	for (int i = 1; i < 11; i++)
		std::cout << "[ " <<std::setw(2)<< i << "  ]";
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 1; i < 11; i++)
	{
		std::cout << "["<< std::setw(2) << i<<"]";
		for(int j=1;j< 11;j++)
		{
			std::cout <<"[ "<< std::setw(2) <<outer[i][j] << "  ]";
		}
		std::cout << std::endl << std::endl;
		
	}
	std::cout <<lastblock << std::endl;
}
void boom::viewbo()//输出数组
{
	std::cout << "    ";
	for (int i = 1; i < 11; i++)
		std::cout << "[ " << std::setw(2) << i << "  ]";
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 1; i < 11; i++)
	{
		std::cout << "[" << std::setw(2) << i << "]";
		for (int j = 1; j < 11; j++)
		{
			std::cout << "[ " << std::setw(2) << save[i][j] << "  ]";
		}
		std::cout << std::endl << std::endl;

	}
}
bool boom::finish() {
	if (lastblock <= 10 || right == 10)
	{
		std::cout << "goodgame!" << std::endl;
		return false;
	}
	else{
		return true;
	}
}
void boom::tic(const int& x, const int& y)//1为CL标记，2为错误标记，3为正确标记
{
	if(ticker[y][x]==0){
		if (save[y][x] < 10)
		{
			ticker[y][x] = 2;
			wrontic += 1;
			outer[y][x] = 'T';
			ticked++;
		}
		else
		{
			ticker[y][x] = 3;
			right += 1;
			outer[y][x] = 'T';
			ticked++;
		}
	}
	else if(ticker[y][x]==1)
	{
		doubleclick(x, y);
	}
	else
	{
		std::cout << "ticked" << std::endl;
	}
}
void boom::detic(const int& x, const int& y)
{
	if (ticker[y][x] == 3)
	{
		ticker[y][x] = 0;
	}
	else if (ticker[y][x] == 2)
	{
		ticker[y][x] = 0;
		wrontic -= 1;
	}
	else
	{
		std::cout << "Fail detick for it haven't ticked or cleaned " << std::endl;
	}
}
void boom::doubleclick(const int &x,const int &y){
	int tk=0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (ticker[y + j][x + i] == 3 || ticker[y + j][x + i] == 2)
				tk++;
		}
	}
	if (save[y][x] == tk)
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if ((x + i == x && y + j == y) || x + i < 1 || y + j < 1 || x + i>10 || y + j>10)//若超出数组范围或为自己则跳过
				{
					continue;
				}
				else
				{
					if (ticker[y + j][x + i] == 2)
					{
						chose(x, y, '3');
						break;
					}
					else if (ticker[y + j][x + i] == 3)
					{
						continue;
					}
					else {
						chose(x + i, y + j, '0');
					}

				}
			}
		}
	}
}
void boom::saves()
{
	using namespace std;
	ofstream file("save.dat", ios::binary);
	file.write((char*)save, sizeof(save));
	file.write((char*)outer, sizeof(outer));
	file.write((char*)ticker, sizeof(ticker));
	file.write((char*)&lastblock, sizeof(lastblock));
	file.write((char*)&ticked, sizeof(ticked));
	file.write((char*)&wrontic, sizeof(wrontic));
	file.write((char*)&right, sizeof(right));
	file.close();
}
void boom::reads()
{
	using namespace std;
	ifstream file("save.dat", ios::binary);
	file.read((char*)save, sizeof(save));
	file.read((char*)outer, sizeof(outer));
	file.read((char*)ticker, sizeof(ticker));
	file.read((char*)&lastblock, sizeof(lastblock));
	file.read((char*)&ticked, sizeof(ticked));
	file.read((char*)&wrontic, sizeof(wrontic));
	file.read((char*)&right, sizeof(right));
	file.close();
}
