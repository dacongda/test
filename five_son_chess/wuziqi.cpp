#include "wuziqi.h"
#include <iostream>
bool Fsq::wplace(const int x, const int y) {
	if (board[y][x] == 0)
	{
		board[y][x] = 1;
		return false;
	}
	else
		std::cout << "Has chess here!"<<endl;
		return true;
}
bool Fsq::bplace(const int x, const int y) {
	if (board[y][x] == 0)
	{
		board[y][x] = 2;
		return false;
	}
	else
		std::cout << "Has chess here!"<<endl;
		return true;
}
bool Fsq::check(int cha, const int x, const int y) {
	int n=1;//white
	int js=1;//black
	switch (cha) {
	case 1:
		
		for (int i = 1, j = 1; i < 5; i++, j++) {
			if (y + j > 19 || x + i > 19)
				break;
			if (board[y + j][x + j] == 1) {
				n++;
			}
			else
				break;
		}
		for (int i = -1, j = -1; i > -5; i--, j--) {
			if (y + j < 0 || x + i < 0)
				break;
			if (board[y + j][x + i] == 1) {
				n++;
			}
			else
				break;

		}
		if (n >= 5) { //左上
			return true;
		}
		else n = 1;
		for (int i = 1, j = -1; i < 5; i++, j--) {
			if (y + j < 0 || x + i>19)
				break;
			if (board[y + j][x + j] == 1) {
				n++;
			}
			else
				break;
		}
		for (int i = -1, j = 1; i > -5; i--, j++) {
			if (y + j > 19 || x + i < 0)
				break;
			if (board[y + j][x + i] == 1) {
				n++;
			}
			else
				break;

		}
		if (n >= 5) {
			return true;//左下
		}
		else n = 1;
		for (int i = 1; i < 5; i++) {

			if (x + i > 19)
				break;
			if (board[y][x + i] == 1) {
				n++;
			}
			else break;
		}
		for (int i = -1; i > -5; i--) {
			if (x + i < 0)
				break;
			if (board[y][x + i] == 1) {
				n++;
			}
			else break;
		}
		if (n >= 5) {
			return true;
		}
		else n = 1; //上下
		for (int j = 1; j < 5; j++) {

			if (y + j > 19)
				break;
			if (board[y + j][x] == 1) {
				n++;
			}
			else break;
		}
		for (int j = -1; j > -5; j--) {
			if (y + j < 0)
				break;
			if (board[y + j][x] == 1) {
				n++;
			}
			else break;
		}
		if (n >= 5) {
			return true;
		}
		else return false; //左右
	case 2:
		for (int i = 1, j = 1; i < 5; i++, j++) {
			if (y + j > 19 || x + i > 19)
				break;
			if (board[y + j][x + j] == 2) {
				js++;
			}
			else
				break;
		}
		for (int i = -1, j = -1; i > -5; i--, j--) {
			if (y + j < 0 || x + i < 0)
				break;
			if (board[y + j][x + i] == 2) {
				js++;
			}
			else
				break;

		}
		if (js >= 5) { //左上
			return true;
		}
		else js = 1;
		for (int i = 1, j = -1; i < 5; i++, j--) {
			if (y + j > 19 || x + i > 19)
				break;
			if (board[y + j][x + j] == 2) {
				js++;
			}
			else
				break;
		}
		for (int i = -1, j = 1; i > -5; i--, j++) {
			if (y + j > 19 || x + i < 0)
				break;
			if (board[y + j][x + i] == 2) {
				js++;
			}
			else
				break;

		}
		if (js >= 5) { //左下
			return true;
		}
		else js = 1;
		for (int i = 1; i < 5; i++) {

			if (x + i > 19)
				break;
			if (board[y][x + i] == 2) {
				js++;
			}
			else break;
		}
		for (int i = -1; i > -5; i--) {
			if (x + i < 0)
				break;
			if (board[y][x + i] == 2) {
				js++;
			}
			else break;
		}
		if (js >= 5) {
			return true;
		}
		else js = 1; //上下
		for (int j = 1; j < 5; j++) {

			if (y + j > 19)
				break;
			if (board[y + j][x] == 2) {
				js++;
			}
			else break;
		}
		for (int j = -1; j > -5; j--) {
			if (y + j < 0)
				break;
			if (board[y + j][x] == 2) {
				js++;
			}
			else break;
		}
		if (js >= 5) {
			return true;
		}
		else
			return false;
	}
	return false;
}
std::ostream & operator << (std::ostream & os,const Fsq & Fs) {
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			os << "[ ";
			if (Fs.board[i][j]==0)
			{
				os << " ";
			}
			else
			{
				os << Fs.board[i][j];
			}
			os << " ]";
		}
		os <<std::endl<< std::endl;
	}
	return os;
}
namespace wzq {
	bool is_outs(const int x, const int y) {
		if (x < 0 || y < 0 || x>19 || y>19)
			return true;
		else
			return false;
	}
}