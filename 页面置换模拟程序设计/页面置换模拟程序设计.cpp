/*页面置换模拟程序设计*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
using namespace std;
int unfindpage=0;
int sum = 320;
float pagerate;
/*定义内存中物理块的结构*/
struct memoryblock
{
	int pagenumber;//页面号
	int access;//访问位
	int time;//访问时间
	int counter;//访问次数
};
struct memoryblock M[4];
bool cmp1(memoryblock a ,memoryblock b)
{
	return a.time > b.time;
}
bool cmp2(memoryblock a, memoryblock b)
{
	return a.counter < b.counter;
}
void init()//初始化物理块
{
	int i;
	for (i = 0;i < 4;i++)
	{
		M[i].pagenumber = -1;
		M[i].access = 0;
		M[i].time = 0;
		M[i].counter = 0;
	}
}
/*生成作业指令的访问序列*/
int command[320];
void random()
{
	srand((unsigned)time(NULL));
	int cnt = 0;
	command[cnt] = rand() % 320;
	cnt++;
	command[cnt] = command[cnt - 1] + 1;
	cnt++;
	while (cnt < 320)
	{
		command[cnt] = rand() % command[cnt - 2];
		cnt++;
		command[cnt] = command[cnt - 1] + 1;
		cnt++;
		command[cnt] = rand() % (320 - command[cnt - 1]) + command[cnt - 1];
		cnt++;
		command[cnt] = command[cnt - 1] + 1;
		cnt++;
	}
}
/*先进先出置换算法*/
void oncefifo(int a)
{
	int i;
	int p=0;//指向队首的指令
	int b = a / 10;
	int flag=0;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//表示页面在内存中
		{
			M[i].access = 1;
			flag = 1;
			break;
		}
		if (M[i].pagenumber == -1)//表示页面不在内存中，且物理块为空
		{
			M[i].access = 1;
			M[i].pagenumber = b;
			p = (p + 1) % 4;
			unfindpage++;
			flag = 1;
			break;
		}
	}
	if (flag == 0)//进行页面置换
	{
		M[p].pagenumber = b;
		M[p].access = 1;
		unfindpage++;
	}
}
void FIFO()
{
	random();
	int i;
	float rate;
	for (i = 0;i < 320;i++)
	{
		oncefifo(command[i]);
	}
	rate = unfindpage /320.0;
	cout << "先进先出置换算法所得缺页率为：" << rate<<endl;
	system("pause");
}
/*时钟置换算法*/
void onceclock(int a)
{
	int i;
	int p=0;
	int b = a / 10;
	int flag = 0;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//表示页面在内存中
		{
			M[i].access = 1;
			flag = 1;
			break;
		}
		if (M[i].pagenumber == -1)//表示页面不在内存中，且物理块为空
		{
			M[i].access = 1;
			M[i].pagenumber = b;
			p = (p + 1) % 4;
			unfindpage++;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		while (M[p].access != 0)
		{
			M[p].access = 0;
			p = (p + 1) % 4;
		}
		M[p].pagenumber = b;
		M[p].access = 1;
		p = (p + 1) % 4;
		unfindpage++;
	}
}
void CLOCK()
{
	random();
	int i;
	float rate;
	for (i = 0;i < 320;i++)
	{
		onceclock(command[i]);
	}
	rate = unfindpage / 320.0;
	cout << "时钟置换算法所得缺页率为：" << rate << endl;
	system("pause");
}
/*最近最久未使用置换算法*/
void oncelru(int a)
{
	int b = a / 10;
	int flag = 0;
	int i,j;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//页面在内存中，更新时间
		{
			M[i].time = 0;
			M[i].access = 1;
			flag = 1;
			for (j = 0;j < 4;j++)
			{
				if (j != i&&M[j].pagenumber != -1)//其他未被访问的页面的时间加一
				{
					M[j].time++;
				}
			}
			break;
		}
		if (M[i].pagenumber == -1)//页面不在内存中，且物理块为空
		{
			M[i].time = 0;
			M[i].pagenumber = b;
			M[i].access = 1;
			unfindpage++;
			flag = 1;
			for (j = 0;j < 4;j++)
			{
				if (j != i&&M[j].pagenumber != -1)
				{
					M[j].time++;
				}
			}
			break;
		}
	}
		if (flag == 0)//页面不在内存中,进行置换
		{
			sort(M, M + 4, cmp1);
			M[0].time=0;
			M[0].access = 1;
			M[0].pagenumber = b;
			unfindpage++;
			for (j = 1;j < 4;j++)
			{
				M[j].time++;
			}
		}
}
void LRU()
{
	random();
	int i;
	float rate;
	for (i = 0;i < 320;i++)
	{
		oncelru(command[i]);
	}
	rate = unfindpage / 320.0;
	cout << "最近最久未使用置换算法所得缺页率为：" << rate << endl;
	system("pause");
}
/*最近最少访问置换算法*/
void oncelfu(int a)
{
	int b = a / 10;
	int flag = 1;
	int i;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//页面在内存中
		{
			M[i].counter++;
			flag = 1;
			M[i].access = 1;
			break;
		}
		if (M[i].pagenumber = -1)
		{
			M[i].counter++;
			M[i].pagenumber = b;
			M[i].access = 1;
			flag = 1;
			unfindpage++;
			break;
		}
	}
	if (flag == 0)
	{
		sort(M, M + 4, cmp2);
		M[0].pagenumber = b;
		M[0].counter=1;
		M[i].access = 1;
		unfindpage++;
	}
}
void LFU()
{
	random();
	int i;
	float rate;
	for (i = 0;i < 320;i++)
	{
		oncelfu(command[i]);
	}
	rate = unfindpage / 320.0;
	cout << "最近最少访问置换算法所得缺页率为：" << rate << endl;
	system("pause");
}
void showmemory()//显示当前内存的分配情况
{
	cout << endl;
	cout<<"--------当前内存的分配情况------------"<<endl;
	cout << "    " << "页号" << "    " << "访问位" << "   " << endl;
	int i;
	for (i = 0;i < 4;i++)
		cout <<"    "<< M[i].pagenumber << "       " << M[i].access << endl;
}
void menu()
{
	cout << "    " << "***********************************" << endl;
	cout << "    " << "*******页面置换模拟程序设计********" << endl;
	cout << "    " << "************************************" << endl;
	cout << "    " << "************************************" << endl;
	cout << "    " << "********1.FIFO页面置换算法*********" << endl;
	cout << "    " << "********2.CLOCK页面置换算法********" << endl;
	cout << "    " << "********3.LRU页面置换算法**********" << endl;
	cout << "    " << "********4.LFU页面置换算法**********" << endl;
	cout << "    " << "********5.显示当前内存分配情况********" << endl;
	cout << "    " << "********6.退出程序**********" << endl;
	cout << "    " << "**************************" << endl;
}
int main()
{
	init();
	int choice;
	int control=1;
	while (control)
	{
		menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			FIFO();
			unfindpage = 0;
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 2:
			system("cls");
			CLOCK();
			unfindpage = 0;
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 3:
			system("cls");
			LRU();
			unfindpage = 0;
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 4:
			system("cls");
			LFU();
			unfindpage = 0;
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 5:
			system("cls");
			showmemory();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 6:
			control = 0;
			break;
		}
	}
}