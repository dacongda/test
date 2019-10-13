#ifndef WUZIQI_H_
#define WUZIQI_H_
#include <iostream>
using namespace std;
class Fsq
{
private:
	int board[20][20]{0};
public:
	Fsq(){};
	~Fsq(){}
	void regame() {};
	bool wplace(const int x,const int y);
	bool bplace(const int x,const int y);
	bool check(int cha,const int x,const int y);
	friend std::ostream & operator << (std::ostream &os,const Fsq &Fs);
};
namespace wzq {
	bool is_outs(const int x, const int y);
}
#endif
