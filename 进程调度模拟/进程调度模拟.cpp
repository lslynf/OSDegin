/*���̵���ģ��*/
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<iostream>
#define maxsize 10
using namespace std;
/*���ȼ�����*/
struct node//�������ȼ�����
{
	int ID;
	int priority;//���ȼ�
	int cputime;//�Ѿ�ռ��CPU��ʱ��runtime
	int alltime;//���̻���Ҫ������ʱ��needtime
	char state;//���̵�״̬E,R,F
}process[maxsize];
int n;//���̵ĸ�����
bool cmp(node a, node b)
{
	return a.priority > b.priority;
}
void output()
{
	cout << "����ID" << "  " << "�������ȼ�" << "  " << "������ʱ��" << "  " << "��������ʱ��" << "  " << "����״̬" << endl;
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
	cout << "��������̵�������" << endl;
	cin >> n;
	cout << "����������̵�ID, ����������������ʱ�䣺" << endl;
	for (i = 0;i < n;i++)//��ʼ��
	{
		cin >> process[i].ID >> process[i].priority >> process[i].alltime;
		process[i].state = 'R';
		process[i].cputime = 0;
	}
	sort(process, process + n, cmp);
	cout << "���̴����ɹ�����ʼ״̬�������ȼ����У��ǣ�" << endl;
	output();
	cout << endl;
}
void runprocess()
{
	int i;
	if (process[0].alltime>0)
	{
		cout << "��ǰ�������еĽ����ǣ�" << process[0].ID << endl;
		process[0].priority--;
		process[0].cputime++;
		process[0].alltime--;
		process[0].state = 'E';
	}
	else
	{
		for (i = 0;i < n;i++)//���ȼ��Ѿ���Ϊ��ֵ�ˣ�ȥ�鿴��û��������ɵĽ���
		{
			if (process[i].alltime>0)
			{
				cout << "��ǰ�������еĽ����ǣ�" << process[i].ID << endl;
				process[i].priority--;
				process[i].cputime++;
				process[i].alltime--;
				process[i].state = 'E';
			}
		}
	}
	for (i = 1;i < n;i++)//�����������̵�״̬
	{
		if (process[i].priority>0||process[i].alltime)
			process[i].state = 'R';
		else
			process[i].state = 'F';
	}
	sort(process, process + n, cmp);
	cout << "----------��ǰ�����̵����-----------" << endl;
	output();
	cout << endl;
}
void DPschedule()
{
	input();
	cout << "���̵��ȿ�ʼ!" << endl;
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
			process[0].priority = -1;//�����ý���
			process[0].state = 'F';
			cout << "����" << process[0].ID << "�Ѿ��������" << endl;
			sort(process, process + n, cmp);//�����ȼ�����
			runprocess();
		}
		for (i = 0;i < n;i++)
		{
			if (process[i].alltime <= 0)
			{
				process[i].priority = -1;
				process[i].state = 'F';
				cout << "����" << process[i].ID << "�Ѿ��������" << endl;
				cnt++;
			}
		}
		cout << "�밴���������н���" << endl;
	}
}
/*ʱ��Ƭ��ת����*/
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
int cnt;//��¼��ǰ���ж��ٽ���
int chip;
void creatpcb()
{
	head = new PCB;
	head= NULL;
	p = new PCB;
	p = head;
	int i;
	cout << "��������̵�������" << endl;
	cin >> n;
	cout << "��������������̵���Ϣ������ID��������������ʱ��" << endl;
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
	cout << "------------��ǰ�����̵��������------------" << endl;
	cout << "����ID" << "    " << "�����е�ʱ��" << "     " << "�������е�ʱ��" << "    " << "���̵�״̬" << endl;
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
	head->runtime+=chip;//ÿ������ͷ���Ľ��̣�Ȼ��Ѵ˽��̷ŵ���β������ͷ���
	head->needtime-=chip;
	head->state = 'E';
	if (head->runtime >= head->alltime)
	{
		cnt--;
		cout << "����" << head->name << "�Ѿ��������!" << endl;
		cout << endl;
		system("pause");
		head = head->next;
		if (head == NULL)
		{
			cout << "���н��̶�������ɣ�" << endl;
			cout << endl;
			system("pause");
			return;
		}
		head->state = 'E';
	}
	system("cls");
	PCBnode x;//ָ��ͷָ�����һ���ڵ�
	x = head->next;
	cout << "����" << head->name << "��������" << endl;
	cout << "�ھ��������еĽ����ǣ�";
	while (x != NULL)
	{
		cout << "����" << x->name;
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
	head = head->next;//�Ѹ��������ͷ���ŵ���β
	y->next->next = NULL;
	system("pause");
}
void RRschedule()
{
	creatpcb();
	cnt = n;
	cout << "�밴���������н���" << endl;
	system("pause");
	while (cnt)
	{
		runpcb();
	}

}
void menu()
{
	cout << "    " << "********************************" << endl;
	cout << "    " << "**********���̵���ģ��**********" << endl;
	cout << "    " << "********************************" << endl;
	cout << "    " << "********************************" << endl;
	cout << "    " << "********1.��̬���ȼ�����********" << endl;
	cout << "    " << "********2.ʱ��Ƭ��ת����********" << endl;
	cout << "    " << "********3.�˳�����********" << endl;
	cout << "    " << "********************************" << endl;
}
int main()
{
	int control = 1;
	int choice;
	while (control)
	{
		menu();
		cout << "��ѡ��������еĲ�����" << endl;
		cin >> choice;
		switch (choice)
		{
		   case 1:
			   system("cls");
			   DPschedule();
			   cout << "����������1������0" << endl;
			   cin >> control;
			   system("cls");
			   break;
		   case 2:
			   system("cls");
			   cout << "������ʱ��Ƭ��" << endl;
			   cin >> chip;
			   RRschedule();
			   cout << "����������1������0" << endl;
			   cin >> control;
			   system("cls");
			   break;
		   case 3:
			   control = 0;
			   break;
		}
	}
}