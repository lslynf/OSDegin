/*分页管理方式下存储分配情况模拟*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int bitgraph[8][8] = { { 1,1,0,0,1,1,1,0 },
					 { 0,1,0,1,0,1,0,0 },
					 { 0,0,0,0,0,0,0,0 },
					 { 1,0,0,0,0,0,0,1 },
					 { 0,0,0,0,0,0,0,0 },
					 { 0,0,0,0,0,0,0,0 },
					 { 0,0,0,0,0,0,0,0 },
					 { 0,0,0,0,0,0,0,0 }
					 };
int count = 10;//初始占用块
typedef struct job
{
	int page[64];//页表
	int jobname;
	int size;
	int present;//表示作业的状态，执行还是结束
	struct job *next;
}JN, *jobnode;
jobnode head = NULL;
void init()
{
	head = new JN;
	head->next = NULL;
	memset(head->page, 0, 64);
	head->jobname = 0;
	head->size = 0;
}
void showbitgraph()//显示位示图
{
	cout << "位示图如下：" << endl;
	int i, j;
	for (i = 0;i < 8;i++)
	{
		for (j = 0;j < 8;j++)
		{
			cout << bitgraph[i][j] << " ";
		}
		cout << endl;
	}
	cout << "此时内存中已被占用的物理块一共有：" << ::count << "块" << endl;
}
void  memoryallocate()//内存分配
{
	int i, j, k = 0;
	jobnode p = new JN;
	jobnode q = head;
	cout << "请输入作业的名称：" << endl;
	cin >> p->jobname;
	cout << "请输入作业所需的内存大小：" << endl;
	cin >> p->size;
	p->present = 1;
	if (p->size > 64 - ::count)
		cout << "作业所需的内存大小不能满足，分配失败" << endl;
	else
	{
		int control = 1;
		for (i = 0;i < 8 && control;i++)
		{
			for (j = 0;j < 8 && control;j++)
			{
				if (bitgraph[i][j] == 0)
				{
					p->page[k] = 8 * i + j;
					bitgraph[i][j] = 1;
					::count++;
					k++;
					if (k == p->size)
						control = 0;
				}
			}
		}
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
		p->next = NULL;
	}
	cout << endl;
	/*jobnode r;
	r=head->next;
	while(r!=NULL)
	{
	cout<<r->size<<endl;
	r=r->next;
	}*/
	showbitgraph();
}
void memoryrecycle()//内存回收
{
	int i;
	int m, n, symbol = 0;
	int id;
	cout << "请输入执行结束作业的名称：" << endl;
	cin >> id;
	jobnode point = head->next;
	while (point != NULL)
	{
		if (id == point->jobname)
		{
			for (i = 0;i < point->size;i++)
			{
				m = point->page[i] / 8;
				n = point->page[i] % 8;
				bitgraph[m][n] = 0;
				::count--;
			}
			point->present = 0;
		}
		else
		{
			point->present = 1;
		}
		point = point->next;
	}
	jobnode r = head->next;
	while (r != NULL)
	{
		if (r->present == 0)
		{
			cout << "内存回收成功！" << endl;
			showbitgraph();
		}
		r = r->next;
	}
}
void showjob()//显示当前有多少作业
{
	jobnode x;
	x = head->next;
	cout << "当前内存中的作业为：" << endl;
	while (x != NULL)
	{
		if(x->present==1)
		cout << "作业" << x->jobname << " ";
		x = x->next;
	}
	cout << endl;
}
void showpagetable()//显示页表
{
	int a;
	int i;
	int symbol = 0;
	cout << "请输入你所要查看的作业名称：" << endl;
	cin >> a;
	jobnode present = head;
	for (present = head;present != NULL;present = present->next)
	{
		if (a == present->jobname)
		{
			cout << "页号" << "   " << "块号" << endl;
			for (i = 0;i < present->size;i++)
			{
				cout << i << "     " << present->page[i] << endl;
			} 
			symbol = 1;
		}
		else
		{
			symbol = 0;
		}
	}
	if (symbol == 0)
	{
		cout << "该作业不在内存中，无法显示其页表！" << endl;
	}
	else
		cout << "页表显示如上！" << endl;
}
void menu()
{
	cout << "    " << "**************************" << endl;
	cout << "    " << "分页管理方式下存储分配模拟" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "********1.分配主存********" << endl;
	cout << "    " << "********2.回收主存********" << endl;
	cout << "    " << "********3.显示页表********" << endl;
	cout << "    " << "********4.显示作业********" << endl;
	cout << "    " << "********5.退出程序********" << endl;
	cout << "    " << "**************************" << endl;
}
int main()
{
	init();
	int control = 1;
	int choice;
	while (control)
	{
		menu();
		cout << "请选择您想进行的操作：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			memoryallocate();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 2:
			system("cls");
			memoryrecycle();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 3:
			system("cls");
			showpagetable();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 4:
			system("cls");
			showjob();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			system("cls");
			break;
		case 5:
			control = 0;
			break;
		}
	}
}
