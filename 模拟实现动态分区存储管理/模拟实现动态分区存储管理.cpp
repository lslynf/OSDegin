/*ģ��ʵ�ֶ�̬�����洢����*/
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#define maxsize 20
#define maxmemory 1000
using namespace std;
typedef struct blanktable//���з�����ͬʱ��¼�������
{
	int jobID;
	int startadress;
	int length;
	int state;//0��ʾ���ã�1��ʾ������
	struct blanktable *next;
}BT,*BTnode;
/*typedef struct allocationtable//�ѷ��������
{
	int jobid;
	int startadress;
	int length;
}AT[maxsize];//�ĳ�������ʽ�������ѷ���
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
void firstfit()//�״���Ӧ�㷨
{
	BTnode newtask=new BT;
	cout << "��������ҵ�����ƣ�" << endl;
	cin >> newtask->jobID;
	cout << "��������ҵ������ڴ��С��" << endl;
	cin >> newtask->length;
	BTnode p = new BT;
	p = head;
	while (p->length < newtask->length || p->state == 1)
	{
		if (p->next != NULL)
			p = p->next;//һֱ�ҵ�����Ŀ��з���
		else
		{
			p = p->next;
			break;
		}
	}
	if (p == NULL)//һֱ�ҵ������
		cout << "û���ʺϵĿ��з����������ڴ�ʧ�ܣ�" << endl;

	else
	{
	    BTnode q;//�ҵ��˿��з�����Ȼ������һ���µĽ�㣬����ռ�Ϳ�����
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
		cout << "�����ڴ�ɹ���" << endl;
	}
}
void memoryrecycle()
{
	int jobname;
	cout << "������Ҫ���յ���ҵ��";
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
		cout << "����ҵ�����ڴ��У�������������ȷ����ҵ��" << endl;
	}
	else
	{
		if (rear != NULL&&front != NULL)
		{
			if (front->state == 0 && rear->state == 0)//ǰ�����ڵ������������ÿ��е�
			{
				front->length = front->length + present->length + rear->length;
				front->next = rear->next;
				delete present;
				delete rear;
			}
			else if(front->state==0&&rear->state==1)//ǰ�����ڵķ����ǿ��еģ��������ڵķ���������
			{
				front->length = front->length + present->length;
				front->next = present->next;
				delete present;
			}
			else if (front->state == 1 && rear->state == 0)//ǰ�����ڵķ������ǿ��еģ��������ڵķ�������
			{
				present->length = present->length + rear->length;
				present->jobID = 0;
				present->state = 0;
				present->next = rear->next;
				delete rear;
			}
			else if(front->state==1&&rear->state==1)//ǰ�����ڵ��������������Է����
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
		cout << "�ڴ���ճɹ���" << endl;
	}
}
void showBT()
{
	BTnode count = head;
	cout << "��ҵ����" << "  " << "��ʼ��ַ" << "  " << "����" << "   " << "״̬" << endl;
	while (count != NULL)
	{
		cout << count->jobID << "         ";
		cout << count->startadress <<"k"<< "        ";
		cout << count->length << "k" << "   ";
		if (count->state == 1)
			cout << "�ѷ���" << "  " << endl;
		else
			cout << "���з���" << "  " << endl;
		count = count->next;
	}
}
void menu()
{
	cout << "    " << "**************************" << endl;
	cout << "    " << "ģ��ʵ�ֶ�̬�����洢����" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "ע�⣺�������ҵ�Ų���Ϊ0" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "********1.��������********" << endl;
	cout << "    " << "********2.��������********" << endl;
	cout << "    " << "********3.��ʾ����********" << endl;
	cout << "    " << "********4.�˳�����********" << endl;
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
		cout << "��ѡ������Ҫ���еĲ�����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			firstfit();
			cout << "����������1������0" << endl;
			cin >> control;
			break;
		case 2:
			system("cls");
			memoryrecycle();
			cout << "����������1������0" << endl;
			cin >> control;
			break;
		case 3:
			system("cls");
			showBT();
			cout << "����������1������0" << endl;
			cin >> control;
			break;
		case 4:
			control = 0;
			break;
		}
		system("cls");
	}
}