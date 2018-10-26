/*ҳ���û�ģ��������*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
using namespace std;
int unfindpage=0;
int sum = 320;
float pagerate;
/*�����ڴ��������Ľṹ*/
struct memoryblock
{
	int pagenumber;//ҳ���
	int access;//����λ
	int time;//����ʱ��
	int counter;//���ʴ���
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
void init()//��ʼ�������
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
/*������ҵָ��ķ�������*/
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
/*�Ƚ��ȳ��û��㷨*/
void oncefifo(int a)
{
	int i;
	int p=0;//ָ����׵�ָ��
	int b = a / 10;
	int flag=0;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//��ʾҳ�����ڴ���
		{
			M[i].access = 1;
			flag = 1;
			break;
		}
		if (M[i].pagenumber == -1)//��ʾҳ�治���ڴ��У��������Ϊ��
		{
			M[i].access = 1;
			M[i].pagenumber = b;
			p = (p + 1) % 4;
			unfindpage++;
			flag = 1;
			break;
		}
	}
	if (flag == 0)//����ҳ���û�
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
	cout << "�Ƚ��ȳ��û��㷨����ȱҳ��Ϊ��" << rate<<endl;
	system("pause");
}
/*ʱ���û��㷨*/
void onceclock(int a)
{
	int i;
	int p=0;
	int b = a / 10;
	int flag = 0;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//��ʾҳ�����ڴ���
		{
			M[i].access = 1;
			flag = 1;
			break;
		}
		if (M[i].pagenumber == -1)//��ʾҳ�治���ڴ��У��������Ϊ��
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
	cout << "ʱ���û��㷨����ȱҳ��Ϊ��" << rate << endl;
	system("pause");
}
/*������δʹ���û��㷨*/
void oncelru(int a)
{
	int b = a / 10;
	int flag = 0;
	int i,j;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//ҳ�����ڴ��У�����ʱ��
		{
			M[i].time = 0;
			M[i].access = 1;
			flag = 1;
			for (j = 0;j < 4;j++)
			{
				if (j != i&&M[j].pagenumber != -1)//����δ�����ʵ�ҳ���ʱ���һ
				{
					M[j].time++;
				}
			}
			break;
		}
		if (M[i].pagenumber == -1)//ҳ�治���ڴ��У��������Ϊ��
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
		if (flag == 0)//ҳ�治���ڴ���,�����û�
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
	cout << "������δʹ���û��㷨����ȱҳ��Ϊ��" << rate << endl;
	system("pause");
}
/*������ٷ����û��㷨*/
void oncelfu(int a)
{
	int b = a / 10;
	int flag = 1;
	int i;
	for (i = 0;i < 4;i++)
	{
		if (M[i].pagenumber == b)//ҳ�����ڴ���
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
	cout << "������ٷ����û��㷨����ȱҳ��Ϊ��" << rate << endl;
	system("pause");
}
void showmemory()//��ʾ��ǰ�ڴ�ķ������
{
	cout << endl;
	cout<<"--------��ǰ�ڴ�ķ������------------"<<endl;
	cout << "    " << "ҳ��" << "    " << "����λ" << "   " << endl;
	int i;
	for (i = 0;i < 4;i++)
		cout <<"    "<< M[i].pagenumber << "       " << M[i].access << endl;
}
void menu()
{
	cout << "    " << "***********************************" << endl;
	cout << "    " << "*******ҳ���û�ģ��������********" << endl;
	cout << "    " << "************************************" << endl;
	cout << "    " << "************************************" << endl;
	cout << "    " << "********1.FIFOҳ���û��㷨*********" << endl;
	cout << "    " << "********2.CLOCKҳ���û��㷨********" << endl;
	cout << "    " << "********3.LRUҳ���û��㷨**********" << endl;
	cout << "    " << "********4.LFUҳ���û��㷨**********" << endl;
	cout << "    " << "********5.��ʾ��ǰ�ڴ�������********" << endl;
	cout << "    " << "********6.�˳�����**********" << endl;
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
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 2:
			system("cls");
			CLOCK();
			unfindpage = 0;
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 3:
			system("cls");
			LRU();
			unfindpage = 0;
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 4:
			system("cls");
			LFU();
			unfindpage = 0;
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 5:
			system("cls");
			showmemory();
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 6:
			control = 0;
			break;
		}
	}
}