#include <iostream>
#include <fstream>
#include <conio.h>
#define UP_KEY 372
#define DOWN_KEY 380
#define LEFT_KEY 375
#define RIGHT_KEY 377
using namespace std;
typedef int_fast8_t fnt;
typedef short int sint;
typedef struct Map_Exit
{
	fnt Left_exit;
	fnt Right_exit;
	fnt Up_exit;
	fnt Down_exit;
	fnt Oth[6];
	wchar_t Name[10][10];
}Map_Exit;
typedef struct base_map {
	wchar_t name[20];
	wchar_t describe[50];
	sint npc_id[10];
	sint siz[24][24];
	Map_Exit Me;
	fnt spawn_x;
	fnt spawn_y;
}bm;
bool inpu() {
	bool mode;
	int tmp;
	wcin >> tmp;
	while (1) {
		if (tmp == 1 || tmp == 0)
		{
			mode = tmp;
			return mode;
		}
		else
			wcout << L"错误输入" << endl;
		wcin >> tmp;
	}
}
int kbscan()
{
	char a = 0;
	a = _getch();
	if (a != -32)
	{
		return a;
	}
	else
	{
		a = _getch();
		return a + 300;
	}
}
bool if_vaild(sint x, sint y) {
	if (x < 0 or x >= 24 or y < 0 or y >= 24)
		return false;
	else
		return true;
}
int main() {
	int mp[24][24]{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
	enum MODE :bool { Change, Create };
	locale china("zh_CN.UTF-8");
	locale::global(china);
	wcout << L"请选择模式 0=更改地图,1=创建地图" << endl;
	bool mode;
	mode = inpu();
	/*switch (mode)
	{
	case 0: {

	}
	case 1: {
		wcout << "请输入地图名称" << endl;

	}
	}*/
	struct chose {
		int x;
		int y;
	}chose;
	chose.x = 12;
	chose.y = 12;
	while (1) {
		system("cls");
		for (int n = 0; n < 24; n++)
		{
			for (int j = 0; j < 24; j++)
			{
				if (n != chose.y || j != chose.x)
					wcout << "[ " << mp[n][j] << " ]";
				else
					wcout << "< " << mp[n][j] << " >";
			}
			wcout << endl;
		}
		sint ks = kbscan();
		switch (ks) {
		w:case 'w': {
			if (if_vaild(chose.y - 1, chose.x))
				chose.y -= 1;
			break;
		};
	a:case 'a': {
		if (if_vaild(chose.y, chose.x - 1))
			chose.x -= 1;
		break;
	};
s:case 's': {
	if (if_vaild(chose.y + 1, chose.x))
		chose.y += 1;
	break;
};
d:case 'd': {
if (if_vaild(chose.y, chose.x + 1))
chose.x += 1;
break;
};
case UP_KEY: goto w;
case LEFT_KEY: goto a;
case DOWN_KEY: goto s;
case RIGHT_KEY: goto d;
e:case 'e': {
	break;
}
case 'W':goto w;
case 'A':goto a;
case 'S':goto s;
case 'D':goto d;
case 'E':goto e;
default:break;
		}
	}
}