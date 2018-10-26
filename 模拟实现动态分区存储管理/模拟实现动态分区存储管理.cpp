/*模拟实现动态分区存储管理*/
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#define maxsize 20
#define maxmemory 1000
using namespace std;
typedef struct blanktable//空闲分区表同时记录分配情况
{
	int jobID;
	int startadress;
	int length;
	int state;//0表示可用，1表示不可用
	struct blanktable *next;
}BT,*BTnode;
/*typedef struct allocationtable//已分配分区表
{
	int jobid;
	int startadress;
	int length;
}AT[maxsize];//改成链表形式，增加已分配
*/
BTnode head=NULL;
void init()
{
	head = new BT;
	head->next = NULL;
	head->startadress = 0;
	head->length = maxmemory;
	head->state = 0;
	head->jobID = 0;
}
void firstfit()//首次适应算法
{
	BTnode newtask=new BT;
	cout << "请输入作业的名称：" << endl;
	cin >> newtask->jobID;
	cout << "请输入作业所需的内存大小：" << endl;
	cin >> newtask->length;
	BTnode p = new BT;
	p = head;
	while (p->length < newtask->length || p->state == 1)
	{
		if (p->next != NULL)
			p = p->next;//一直找到满足的空闲分区
		else
		{
			p = p->next;
			break;
		}
	}
	if (p == NULL)//一直找到了最后
		cout << "没有适合的空闲分区，分配内存失败！" << endl;

	else
	{
	    BTnode q;//找到了空闲分区，然后申请一个新的结点，分配空间和空闲区
		q = new BT;
		q->jobID = 0;
		q->startadress = p->startadress + newtask->length;
		q->length = p->length-newtask->length;
		q->state = 0;
		q->next = p->next;
		p->state = 1;
		p->jobID = newtask->jobID;
		p->length = newtask->length;
		p->next = q;
		cout << "分配内存成功！" << endl;
	}
}
void memoryrecycle()
{
	int jobname;
	cout << "请输入要回收的作业：";
	cin >> jobname;
	BTnode front = NULL;
	BTnode present = head;
	BTnode rear = present->next;
	while (present->jobID != jobname)
	{
		front = present;
		if (present->next != NULL)
		{
			present = present->next;
		}
		else
		{
			present = present->next;
			break;
		}
		rear = present->next;
	}
	if(present==NULL)
	{ 
		cout << "该作业不在内存中，请重新输入正确的作业！" << endl;
	}
	else
	{
		if (rear != NULL&&front != NULL)
		{
			if (front->state == 0 && rear->state == 0)//前后相邻的两个分区都得空闲的
			{
				front->length = front->length + present->length + rear->length;
				front->next = rear->next;
				delete present;
				delete rear;
			}
			else if(front->state==0&&rear->state==1)//前面相邻的分区是空闲的，后面相邻的分区不空闲
			{
				front->length = front->length + present->length;
				front->next = present->next;
				delete present;
			}
			else if (front->state == 1 && rear->state == 0)//前面相邻的分区不是空闲的，后面相邻的分区空闲
			{
				present->length = present->length + rear->length;
				present->jobID = 0;
				present->state = 0;
				present->next = rear->next;
				delete rear;
			}
			else if(front->state==1&&rear->state==1)//前后相邻的两个分区都是以分配的
			{
				present->jobID = 0;
				present->state = 0;
			}
		}
		else if (rear != NULL&&front == NULL)
		{
			if (rear->state == 0)
			{
				present->length = present->length + rear->length;
				//present->state = 0;
				//present->jobID = 0;
				present->next = NULL;
				delete rear;
			}
			else
			{
				present->jobID = 0;
				present->state = 0;
			}
		}
		else if (rear == NULL&&front != NULL)
		{
			if (front->state == 0)
			{
				front->length = front->length + present->length;
				front->next = NULL;
				delete present;
			}
			else
			{
				present->jobID = 0;
				present->state = 0;
			}
		}
		else if (rear == NULL&&front == NULL)
		{
			present->jobID = 0;
			present->state = 0;
		}
		cout << "内存回收成功！" << endl;
	}
}
void showBT()
{
	BTnode count = head;
	cout << "作业名称" << "  " << "起始地址" << "  " << "长度" << "   " << "状态" << endl;
	while (count != NULL)
	{
		cout << count->jobID << "         ";
		cout << count->startadress <<"k"<< "        ";
		cout << count->length << "k" << "   ";
		if (count->state == 1)
			cout << "已分配" << "  " << endl;
		else
			cout << "空闲分区" << "  " << endl;
		count = count->next;
	}
}
void menu()
{
	cout << "    " << "**************************" << endl;
	cout << "    " << "模拟实现动态分区存储管理" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "注意：输入的作业号不能为0" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "********1.分配主存********" << endl;
	cout << "    " << "********2.回收主存********" << endl;
	cout << "    " << "********3.显示主存********" << endl;
	cout << "    " << "********4.退出程序********" << endl;
	cout << "    " << "**************************" << endl;
}
int main()
{
	init();
	int choice;
	int control = 1;
	while (control)
	{
		menu();
		cout << "请选择您想要进行的操作：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			firstfit();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			break;
		case 2:
			system("cls");
			memoryrecycle();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			break;
		case 3:
			system("cls");
			showBT();
			cout << "若继续程序按1，否则按0" << endl;
			cin >> control;
			break;
		case 4:
			control = 0;
			break;
		}
		system("cls");
	}
}