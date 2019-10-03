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
	void nwg();//����Ϸ
	void reg();//������Ϸ
	void over();//�군
	void tic(const int& x, const int& y);//��Ǻ���
	void detic(const int& x, const int& y);//ȡ�����
	void finder(const int x, const int y);//�ݹ���չ
	bool chose(const int& x, const int& y,const char& mode);//ѡ����
	void clean(const int& x, const int& y);//�򿪷���
	void view();//��������
	void viewbo();//���������
	bool finish();//����ж�
	void rndfix(int &x,int&y);//�����ظ����
	void doubleclick(const int& x, const int& y);//˫��
	void saves();
	void reads();
};
#endif // !BOOM_H
