#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LinkList/LinkList.h"
#include "../FileManagement/FileManagement.h"
#include "function.h"

pbook bookhead;
pstu stuhead;
extern FILE *fstu;
extern FILE *fbook;
char bookName[32] = {0};

/**
 * ������������ʾ�˵�
 * ������������
 * ��������ֵ����
*/
void menu()
{
	//system("clear");

	printf("\t\t-----------------------------------------------\n");
	printf("\t\t  1������ͼ��                    2��ɾ��ͼ��\n");
	printf("\t\t  3���鿴ͼ��                    4������ͼ��\n");
	printf("\t\t  5������                        6������\n");
	printf("\t\t  7���������                    8���˳�ϵͳ\n");
	printf("\t\t----------------------------------------------\n");
}

/**
 * ����������ͼ��ݳ�ʼ�������һЩͼ��
 * ������������
 * ��������ֵ����
*/
void init()
{
	//��ʼ��ѧ�����鱾�ı�ͷ
	Init_stu_book_list(&bookhead,&stuhead);
    Fileinit();
    Fscan_book(fbook, bookhead);
    Fscan_stu(fstu, stuhead);
	Fileclose();
}

/**
 * ������������ʾͼ��������鱾
*/
void ShowBook()
{
	int ret = Traverse_bookLink(bookhead);
	if (SUCCESS == ret)
	{
		printf("\t\t ����ɹ�\n");
	}
	else
	{
		printf("\t\t ���ʧ��\n");
	}
}

/**
 * ��������������ͼ��
 * ������������
 * ��������ֵ����
*/
void addbook()
{
	printf("\t\t ������������");
	scanf("%s", bookName);
	int booknumber = 0;
	printf("\t\t ������Ҫ����ı�����");
	scanf("%d", &booknumber);

	int ret = search_book(bookhead, bookName);
	if (FAILURE == ret)
	{
		InsertBookLink(bookhead, bookName, booknumber);
	}
	else
	{
		add_book_num(bookhead, bookName,booknumber);
	}

	ShowBook();
}

/**
 * ����������ɾ��ͼ��
 * ������������
 * ��������ֵ����
*/
void deletebook()
{
	printf("\t\t ������������");
	scanf("%s", bookName);
	int ret = Locate_book(bookhead, bookName);

	if (ret == FAILURE)
	{
		printf("\t\t ���鲻����\n");
	}
	else
	{
		Delete_book(bookhead, bookName);
		printf("\t\t ɾ���ɹ�\n");
	}

	ShowBook();
}

/**
 * ��������������
 * ������������
 * ��������ֵ����
*/
void findbook()
{
	printf("\t\t ������������");
	scanf("%s", bookName);
	int ret;
	ret = search_book(bookhead, bookName);
	
	if (ret == FAILURE)
	{
		printf("\t\t �鱾������\n");
	}
	else
	{
		Locate_book(bookhead, bookName);
	}
	
}

/**
 * ��������������
 * ������������
 * ��������ֵ����
*/
void ReturnBook()
{
	printf("\t\t ������ѧ��");
	int id;
	scanf("%d", &id);
	int ret;
	ret = search_stu(stuhead, id);
	if (ret == FAILURE || ret == FALSE)//id������
	{
		printf("\t\t id�����ڣ��޷�����\n");
	}
	else//id����
	{	
		pstu head;
		pbook head_book;
		head = stuhead->next;
		while(head)
		{
			if (head->id == id);
			{
				break;
			}
            head = head->next;
		}
		if(head->count != 0)//id��Ƿ��
		{
			printf("\t\t ������%-10s ID��%-10d ���鱾����%-3d\n", head->name, head->id, head->count);
			int i = 0;
			for (i = 0; i < head->count; i++)//���Ƿ����
			{
				printf("\t\t ������%-10s ������1\n", head->book[i]);
			}
			printf("\t\t ����Ҫ�����飺");
			scanf("%s",bookName);
			int bookresult = search_book(bookhead, bookName);

			if(bookresult != FAILURE)//ͼ��ݴ����Ȿ��ļ�¼
			{
				for (i = 0; i < head->count; i++)//����
				{	
					if (strcmp(bookName, head->book[i]) == 0)
					{
						//ѧ����Ϣ�޸�
						printf("\t\t ����ɹ�\n");
						int j;
						for (j = i; j < head->count - i; j++)
						{
							if (i != head->count - 1)
							{
								if (j == 4)
								{
									break;
								}
								strcpy(head->book[j], head->book[j + 1]);
							}
							else
							{
								break;
							}	
						}
						head->count--;
						//printf("\t\t ����ɹ�1\n");
						
						//ͼ����鼮�洢��Ϣ�޸�
						head_book = bookhead->next;
						while(head_book)
						{
							if ((strcmp(head_book->name,bookName)) == 0)
							{
								break;
							}
							else
							{
								head_book = head_book->next;
							}
						}
						//printf("\t\t ����ɹ�2\n");
						head_book->count++;
						head_book->number--;
						head_book->flag = 1;
						break;
					}
				}
			}
			else//ͼ��ݲ�������ļ�¼
			{
				printf("\t\t �������\n");
			}

		}
		else//id��Ƿ��
		{
			printf("\t\t ��Ƿ��\n");
		}
		
	}

}

/**
 * ����������ѧ���������
 * ������������
 * ��������ֵ����
*/
void StuBorrowState()
{	
	int id;
	printf("\t\t ����ID:");
	scanf("%d",&id);
	//��ѯѧ�ţ��ж��ڲ���
	int result;
	result = Locate_stu(stuhead, id);
	
	if (result == FAILURE)//����
	{
		printf("\t\t ���޴���\n");
	}
}

/**
 * ��������������
 * ������������
 * ��������ֵ����
*/
void BorrowBook()
{
	pstu head;
	pbook head_book;
	int id = 0;

	printf("\t\t ������ѧ�ţ�");
	scanf("%d", &id);

	//����g_student���飬�ж�ѧ���Ƿ�����
	int result;
	result = search_stu(stuhead, id);  //�ж�ID�Ƿ����
	if (result == FAILURE)    //�����ڣ����µ�ѧ�������ڴ�
	{
		printf("\t\t δ��ѯ��������ע��\n");
		char name[32] = {0};

		printf("\t\t ������������");//��������
		scanf("%s", name);
		printf("\t\t ������ѧ�ţ�");
		scanf("%d", &id);
		int sturesult = search_stu(stuhead, id);
		while (sturesult != FAILURE)
		{
			printf("\t\t ѧ���ѱ�ע�ᣬ����������ѧ��\n");
			printf("\t\t ������ѧ�ţ�");
			scanf("%d", &id);
			sturesult = search_stu(stuhead, id);
		}

		InsertStuLink(stuhead, name, id);

		printf("\t\t Ҫ���ı��飺");
		scanf("%s", name);

		//�ж���治����
		result = search_book(bookhead, name);
		if (FAILURE == result)   //�鱾������
		{
			printf("\t\t �鱾�����ڣ�����ʧ��\n");
			return;
		}
		else          //�鱾����
		{
			head_book = bookhead->next;
			while(head_book)
			{
				if ((strcmp(head_book->name,name)) == 0)
				{
					break;
				}
				else
				{
					head_book = head_book->next;
				}
			}
			if (0 == head_book->count)    //�鱾ȫ���
			{
				head_book->flag = 0;
				printf("\t\t �鱾��ȫ�����\n");
			}
			else
			{
				head_book->count--;
				head_book->number++;
				if (0 == head_book->count)
				{
					head_book->flag = 0;      //�鱾���ɽ�
				}
				head = stuhead->next;
				while(head)
				{
					if (head->id == id)
					{
						break;
					}
					else
					{
						head = head->next;
					}
				}

				head->count = 0;
				head->book[head->count] = (char *)malloc(sizeof(char) * 32);
				if (NULL == head->book[head->count])
				{
					printf("malloc failure!\n");
					return;
				}
				strcpy(head->book[head->count], name);   //��������
				head->count++;    //����ı�����һ
				printf("\t\t ����ɹ�\n");
			}
		}
	}
	else                 //���ڣ��жϽ����Ƿ�ﵽ����
	{
		head = stuhead->next;
		while(head)
		{
			if (head->id == id)
			{
				break;
			}
				head = head->next;
		}

		if (head->count < 5)//δ�����ޣ��������
		{
			printf("\t\t ����Ҫ���������");
			scanf("%s", bookName);
			int bookresult;
			bookresult = search_book(bookhead, bookName);
			if(bookresult != FAILURE)//�ҵ��鱾
			{
				head_book = bookhead->next;
				while(head_book)
				{
					if ((strcmp(head_book->name,bookName)) == 0)
					{
						break;
					}
					else
					{
						head_book = head_book->next;
					}
				}

				if (head_book->count != 0)
				{
					//ѧ����Ϣ�޸�
					head->count++;
					head->book[head->count - 1] = (char *)malloc(sizeof(char) * 32);
					strcpy(head->book[head->count - 1], bookName);
					//ͼ�����Ϣ�޸�
					head_book->count--;
					head_book->number++;
					if (head_book->count == 0)
					{
						head_book->flag = 0;
					}
					printf("\t\t ����ɹ�\n");
				}
				else
				{
					printf("\t\t �鱾��ȫ������\n");
				}
				
			}
			else
			{
				printf("\t\t û�ҵ��飬���\n");
			}
		}
		else
		{
			printf("\t\t �Ѵ�������ޣ����ȹ黹�鱾\n");
		}
		
	}

}

void exit_system()
{
	FileopenNew();
    Fprint_book(fbook, bookhead);
    Fprint_stu(fstu, stuhead);
	Fileclose();
    exit(0);
}
