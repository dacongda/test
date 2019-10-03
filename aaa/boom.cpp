#include <iostream>
#include "boom.h"
void mainp(boom& a);
void mainq(boom& a);
int main(int argc,char *argv[])
{
	using namespace std;
	cout << "|--------------------|\n" <<
			"|                    |\n" <<
		    "|                    |\n" <<
		    "|       É¨   À×      |\n" <<
		    "|                    |\n" <<
		    "|                    |\n" <<
		    "|--------------------|\n";
	I:cout << "N:start Q:Quiet M:maker" << endl;
	char ac='0';
	cin >> ac;
	boom a;
	switch (ac)
	{
	case 'N':	
		if(argc==2){
		mainp(a);
		}
		else
		{
		mainq(a);
		}
		break;
    case 'Q':
		return 0;
	case 'M':
		cout << "Made by DacongDA" << endl;
		goto I;
	default:
		cout << "wrong input" << endl;
		goto I;
	}
}
void mainp(boom& a)
{
	using namespace std;
	a.nwg();
	a.view();
	a.viewbo();
	while (a.finish())
	{
		int x, y;
		char mode;
		mode = '0';
		cout << "Please enter X ,Y and Mode" << endl;
		cin >> x >> y >> mode;
		if (a.chose(x,y,mode) == false)
		{
			cout << "wanna play again?" << endl;
			char c;
			cin >> c;
			if (c == 'Y')
			{
				a.reg();
				mainp(a);
			}
		}
		else
		{
			system("CLS");
			a.view();
			a.viewbo();
		}
	}
	cout << "wanna play again?" << endl;
	char c = '0';
	switch (c)
	{
	case 'Y':
		a.reg();
		mainp(a);
	default:
		break;
	}
}
void mainq(boom& a)
{
	using namespace std;
	a.nwg();
	a.view();
	while (a.finish())
	{
		int x, y;
		char mode;
		mode = '0';
		cout << "Please enter X ,Y and Mode" << endl;
		cin >> x >> y >> mode;
		if (a.chose(x, y, mode) == false)
		{
			cout << "wanna play again?" << endl;
			char c;
			cin >> c;
			if (c == 'Y')
			{
				a.reg();
				mainq(a);
			}
		}
		else
		{
			system("CLS");
			a.view();
		}
	}
	cout << "wanna play again?Press Y/y to sure" << endl;
	char c = '0';
	switch (c)
	{
	case 'y':goto Y;
	Y:case 'Y':
		a.reg();
		mainq(a);
	default:
		break;
	}
}
