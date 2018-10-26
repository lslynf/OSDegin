/*进程调度模拟*/
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<iostream>
#define maxsize 10
using namespace std;
/*优先级调度*/
struct node//用于优先级调度
{
	int ID;
	int priority;//优先级
	int cputime;//已经占用CPU的时间runtime
	int alltime;//进程还需要的运行时间needtime
	char state;//进程的状态E,R,F
}process[maxsize];
int n;//进程的个数；
bool cmp(node a, node b)
{
	return a.priority > b.priority;
}
void output()
{
	cout << "进程ID" << "  " << "进程优先级" << "  " << "已运行时间" << "  " << "还需运行时间" << "  " << "进程状态" << endl;
	int i;
	for (i = 0;i < n;i++)
	{
		cout << process[i].ID << "        " << process[i].priority << "            " << process[i].cputime << "          " << process[i].alltime << "               " << process[i].state;
		cout << endl;
	}
}
void input()
{
	int i;
	cout << "请输入进程的总数：" << endl;
	cin >> n;
	cout << "请输入各进程的ID, 优先数，所需运行时间：" << endl;
	for (i = 0;i < n;i++)//初始化
	{
		cin >> process[i].ID >> process[i].priority >> process[i].alltime;
		process[i].state = 'R';
		process[i].cputime = 0;
	}
	sort(process, process + n, cmp);
	cout << "进程创建成功！初始状态（按优先级排列）是：" << endl;
	output();
	cout << endl;
}
void runprocess()
{
	int i;
	if (process[0].alltime>0)
	{
		cout << "当前正在运行的进程是：" << process[0].ID << endl;
		process[0].priority--;
		process[0].cputime++;
		process[0].alltime--;
		process[0].state = 'E';
	}
	else
	{
		for (i = 0;i < n;i++)//优先级已经减为负值了，去查看仍没有运行完成的进程
		{
			if (process[i].alltime>0)
			{
				cout << "当前正在运行的进程是：" << process[i].ID << endl;
				process[i].priority--;
				process[i].cputime++;
				process[i].alltime--;
				process[i].state = 'E';
			}
		}
	}
	for (i = 1;i < n;i++)//设置其他进程的状态
	{
		if (process[i].priority>0||process[i].alltime)
			process[i].state = 'R';
		else
			process[i].state = 'F';
	}
	sort(process, process + n, cmp);
	cout << "----------当前各进程的情况-----------" << endl;
	output();
	cout << endl;
}
void DPschedule()
{
	input();
	cout << "进程调度开始!" << endl;
	cout << endl;
	int cnt = 0;
	int i;
	char ch;
	while (cnt <= n)
	{
		ch = getchar();
		if (process[0].alltime > 0)
		{
			runprocess();
		}
		else
		{
			process[0].priority = -1;//撤销该进程
			process[0].state = 'F';
			cout << "进程" << process[0].ID << "已经运行完成" << endl;
			sort(process, process + n, cmp);//按优先级排序
			runprocess();
		}
		for (i = 0;i < n;i++)
		{
			if (process[i].alltime <= 0)
			{
				process[i].priority = -1;
				process[i].state = 'F';
				cout << "进程" << process[i].ID << "已经运行完成" << endl;
				cnt++;
			}
		}
		cout << "请按键继续运行进程" << endl;
	}
}
/*时间片轮转调度*/
typedef struct PCB
{
	int name;
	int runtime;
	int needtime;
	int alltime;
	char state;
	struct PCB*next;
}PCB,*PCBnode;
PCBnode p, q, head;
int cnt;//记录当前还有多少进程
int chip;
void creatpcb()
{
	head = new PCB;
	head= NULL;
	p = new PCB;
	p = head;
	int i;
	cout << "请输入进程的总数：" << endl;
	cin >> n;
	cout << "请依次输入各进程的信息，进程ID，进程所需运行时间" << endl;
	for (i = 0;i < n;i++)
	{
		q = new PCB;
		cin >> q->name >> q->needtime;
		q->runtime = 0;
		q->alltime = q->needtime;
		q->state = 'R';
		if (i == 0)
		{
			head = p = q;
		}
		else
		{
			p->next = q;
			p = q;
			if (i == n - 1)
				p->next = NULL;
		}
	}
}
void showpcb()
{
	cout << "------------当前各进程的运行情况------------" << endl;
	cout << "进程ID" << "    " << "已运行的时间" << "     " << "还需运行的时间" << "    " << "进程的状态" << endl;
	PCBnode t;
	t = head;
	while (t != NULL)
	{
		cout << t->name << "          " << t->runtime << "                  " << t->needtime << "                " << t->state;
		cout << endl;
		t = t->next;
	}
}
void runpcb()
{
	head->runtime+=chip;//每次运行头结点的进程，然后把此进程放到队尾，更换头结点
	head->needtime-=chip;
	head->state = 'E';
	if (head->runtime >= head->alltime)
	{
		cnt--;
		cout << "进程" << head->name << "已经运行完成!" << endl;
		cout << endl;
		system("pause");
		head = head->next;
		if (head == NULL)
		{
			cout << "所有进程都运行完成！" << endl;
			cout << endl;
			system("pause");
			return;
		}
		head->state = 'E';
	}
	system("cls");
	PCBnode x;//指向头指针的下一个节点
	x = head->next;
	cout << "进程" << head->name << "正在运行" << endl;
	cout << "在就绪队列中的进程是：";
	while (x != NULL)
	{
		cout << "进程" << x->name;
		x = x->next;
	}
	cout << endl;
	showpcb();
	PCBnode y;
	y = head;
	while (y->next != NULL)
	{
		y = y->next;
	}
	head->state = 'R';
	y->next = head;
	head = head->next;//把刚运行完的头结点放到队尾
	y->next->next = NULL;
	system("pause");
}
void RRschedule()
{
	creatpcb();
	cnt = n;
	cout << "请按键继续运行进程" << endl;
	system("pause");
	while (cnt)
	{
		runpcb();
	}

}
void menu()
{
	cout << "    " << "********************************" << endl;
	cout << "    " << "**********进程调度模拟**********" << endl;
	cout << "    " << "********************************" << endl;
	cout << "    " << "********************************" << endl;
	cout << "    " << "********1.动态优先级调度********" << endl;
	cout << "    " << "********2.时间片轮转调度********" << endl;
	cout << "    " << "********3.退出程序********" << endl;
	cout << "    " << "********************************" << endl;
}
int main()
{
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
			   DPschedule();
			   cout << "若继续程序按1，否则按0" << endl;
			   cin >> control;
			   system("cls");
			   break;
		   case 2:
			   system("cls");
			   cout << "请输入时间片：" << endl;
			   cin >> chip;
			   RRschedule();
			   cout << "若继续程序按1，否则按0" << endl;
			   cin >> control;
			   system("cls");
			   break;
		   case 3:
			   control = 0;
			   break;
		}
	}
}