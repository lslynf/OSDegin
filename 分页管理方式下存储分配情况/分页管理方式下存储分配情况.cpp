/*��ҳ����ʽ�´洢�������ģ��*/
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
int count = 10;//��ʼռ�ÿ�
typedef struct job
{
	int page[64];//ҳ��
	int jobname;
	int size;
	int present;//��ʾ��ҵ��״̬��ִ�л��ǽ���
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
void showbitgraph()//��ʾλʾͼ
{
	cout << "λʾͼ���£�" << endl;
	int i, j;
	for (i = 0;i < 8;i++)
	{
		for (j = 0;j < 8;j++)
		{
			cout << bitgraph[i][j] << " ";
		}
		cout << endl;
	}
	cout << "��ʱ�ڴ����ѱ�ռ�õ������һ���У�" << ::count << "��" << endl;
}
void  memoryallocate()//�ڴ����
{
	int i, j, k = 0;
	jobnode p = new JN;
	jobnode q = head;
	cout << "��������ҵ�����ƣ�" << endl;
	cin >> p->jobname;
	cout << "��������ҵ������ڴ��С��" << endl;
	cin >> p->size;
	p->present = 1;
	if (p->size > 64 - ::count)
		cout << "��ҵ������ڴ��С�������㣬����ʧ��" << endl;
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
void memoryrecycle()//�ڴ����
{
	int i;
	int m, n, symbol = 0;
	int id;
	cout << "������ִ�н�����ҵ�����ƣ�" << endl;
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
			cout << "�ڴ���ճɹ���" << endl;
			showbitgraph();
		}
		r = r->next;
	}
}
void showjob()//��ʾ��ǰ�ж�����ҵ
{
	jobnode x;
	x = head->next;
	cout << "��ǰ�ڴ��е���ҵΪ��" << endl;
	while (x != NULL)
	{
		if(x->present==1)
		cout << "��ҵ" << x->jobname << " ";
		x = x->next;
	}
	cout << endl;
}
void showpagetable()//��ʾҳ��
{
	int a;
	int i;
	int symbol = 0;
	cout << "����������Ҫ�鿴����ҵ���ƣ�" << endl;
	cin >> a;
	jobnode present = head;
	for (present = head;present != NULL;present = present->next)
	{
		if (a == present->jobname)
		{
			cout << "ҳ��" << "   " << "���" << endl;
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
		cout << "����ҵ�����ڴ��У��޷���ʾ��ҳ��" << endl;
	}
	else
		cout << "ҳ����ʾ���ϣ�" << endl;
}
void menu()
{
	cout << "    " << "**************************" << endl;
	cout << "    " << "��ҳ����ʽ�´洢����ģ��" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "**************************" << endl;
	cout << "    " << "********1.��������********" << endl;
	cout << "    " << "********2.��������********" << endl;
	cout << "    " << "********3.��ʾҳ��********" << endl;
	cout << "    " << "********4.��ʾ��ҵ********" << endl;
	cout << "    " << "********5.�˳�����********" << endl;
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
		cout << "��ѡ��������еĲ�����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			memoryallocate();
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 2:
			system("cls");
			memoryrecycle();
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 3:
			system("cls");
			showpagetable();
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 4:
			system("cls");
			showjob();
			cout << "����������1������0" << endl;
			cin >> control;
			system("cls");
			break;
		case 5:
			control = 0;
			break;
		}
	}
}
