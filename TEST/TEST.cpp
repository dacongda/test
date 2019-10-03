#include "boom.h"
#include <graphics.h>
#include <conio.h>
#include <string>
int mainp();
void out1()
{
	for (int i = 1; i < 10; i++)
	{
		line(0, 64 * i, 640, 64 * i);
	}
	for (int i = 1; i < 10; i++)
	{
		line(64 * i, 0, 64 * i, 640);
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			outtextxy((64 * i) - 32, (64 * j) - 32, '#');
		}
	}
};
int main()
{
	initgraph(640, 640);   // 创建绘图窗口，大小为 640x480 像素
	setbkcolor(WHITE);
	cleardevice();
	setcolor(BLACK);
	out1();
	mainp();
	cleardevice();         
	closegraph();          // 关闭绘图窗口
}
int mainp()
{
	initgraph(640, 640);   // 创建绘图窗口，大小为 640x480 像素
	setbkcolor(WHITE);
	cleardevice();
	setcolor(BLACK);
	out1();
	boom a;
	a.nwg();
	while (a.finish())
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (m.mkCtrl) {
				a.saves();
				a.view();
				continue;
			}
			else {
				if (a.chose((((m.y) / 64) + 1), ((m.x) / 64 + 1), '0') == false)
				{
					cleardevice();
					RECT r = { 0, 0, 639, 639 };
					drawtext(_T("GameOver,restart again? Right Click to restart ,Left to quit"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				l:m = GetMouseMsg();
					if (m.uMsg == WM_RBUTTONDOWN) 
					{
						mainp(); return 0;
					}
					if (m.uMsg == WM_LBUTTONDOWN)
						return 0;
					else
						goto l;
				}
				else {
					a.view();
				}
				continue;
			}
		case WM_RBUTTONDOWN:
			if (m.mkCtrl) { a.reads(); a.view(); continue; }
			else {
				a.chose((((m.y) / 64) + 1), ((m.x) / 64 + 1), '1');
				a.view();
				continue;
		case WM_LBUTTONDBLCLK:
			a.doubleclick((((m.y) / 64) + 1), ((m.x) / 64 + 1));
			a.view();
			continue;
		default:continue;
			}
		}
		FlushMouseMsgBuffer();
	}
	cleardevice();
	RECT r = { 0, 0, 639, 639 };
	drawtext(_T("You Win!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
