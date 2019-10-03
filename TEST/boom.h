#ifndef BOOM_H
#define BOOM_H
class boom
{
private:
	int save[11][11]{0};
	char outer[11][11]{0};
	int ticker[11][11]{0};
	int ticked;
	int lastblock;
	int wrontic = 0;
	int right=0;
public:
	boom():ticked(0),lastblock(100) {
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				outer[i][j] = '#';
			}
		}
	}
	~boom() {};
	void nwg();//新游戏
	void reg();//重置游戏
	void over();//完蛋
	void tic(const int& x, const int& y);//标记函数
	void detic(const int& x, const int& y);//取消标记
	void finder(const int x, const int y);//递归拓展
	bool chose(const int& x, const int& y,const char& mode);//选择函数
	void clean(const int& x, const int& y);//打开方块
	void view();//输出玩家用
	void viewbo();//输出作弊用
	bool finish();//完成判断
	void rndfix(int &x,int&y);//避免重复随机
	void doubleclick(const int& x, const int& y);//双击
	void saves();
	void reads();
};
#endif // !BOOM_H
