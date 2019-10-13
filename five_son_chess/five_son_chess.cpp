#include <iostream>
#include "wuziqi.h"
int main()
{
	using namespace std;
	Fsq newgame;
	cout << newgame;
	while (true) {
		puts("Plz Player White enter x,y");
		int x=0,y=0;
		cin >> x >> y;
		while (wzq::is_outs(x-1, y-1)) {
			puts("wrong inputs !,enter again");
				cin >> x >> y;
			}
		while(newgame.wplace(x - 1, y - 1))
		{
			cin >> x >> y;
			while (wzq::is_outs(x - 1, y - 1)) {
				puts("wrong inputs !,enter again");
				cin >> x >> y;
			}
		}
		system("CLS");
		if (newgame.check(1, x - 1, y - 1)) {
			cout << "player white win!";
			break;
		}	
		cout << newgame;
		puts("Plz Player Black enter x,y");
		x = 0, y = 0;
		cin >> x >> y;
		while (wzq::is_outs(x - 1, y - 1)) {
			puts("wrong inputs !,enter again");
			cin >> x >> y;
		}
		while (newgame.bplace(x - 1, y - 1))
		{
			cin >> x >> y;
			while (wzq::is_outs(x - 1, y - 1)) {
				puts("wrong inputs !,enter again");
				cin >> x >> y;
			}
		}
		system("CLS");
		if (newgame.check(2, x - 1, y - 1)) {
			cout << "player black win!";
			break;			
		}
		cout << newgame;
		}
}