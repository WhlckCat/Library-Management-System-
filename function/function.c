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
 * 函数描述：显示菜单
 * 函数参数：无
 * 函数返回值：无
*/
void menu()
{
	//system("clear");

	printf("\t\t-----------------------------------------------\n");
	printf("\t\t  1、增加图书                    2、删除图书\n");
	printf("\t\t  3、查看图书                    4、查找图书\n");
	printf("\t\t  5、借书                        6、还书\n");
	printf("\t\t  7、借书情况                    8、退出系统\n");
	printf("\t\t----------------------------------------------\n");
}

/**
 * 函数描述：图书馆初始化，存放一些图书
 * 函数参数：无
 * 函数返回值：无
*/
void init()
{
	//初始化学生和书本的表头
	Init_stu_book_list(&bookhead,&stuhead);
    Fileinit();
    Fscan_book(fbook, bookhead);
    Fscan_stu(fstu, stuhead);
	Fileclose();
}

/**
 * 函数描述：显示图书馆所有书本
*/
void ShowBook()
{
	int ret = Traverse_bookLink(bookhead);
	if (SUCCESS == ret)
	{
		printf("\t\t 输出成功\n");
	}
	else
	{
		printf("\t\t 输出失败\n");
	}
}

/**
 * 函数描述：增加图书
 * 函数参数：无
 * 函数返回值：无
*/
void addbook()
{
	printf("\t\t 请输入书名：");
	scanf("%s", bookName);
	int booknumber = 0;
	printf("\t\t 请输入要储存的本数：");
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
 * 函数描述：删除图书
 * 函数参数：无
 * 函数返回值：无
*/
void deletebook()
{
	printf("\t\t 请输入书名：");
	scanf("%s", bookName);
	int ret = Locate_book(bookhead, bookName);

	if (ret == FAILURE)
	{
		printf("\t\t 此书不存在\n");
	}
	else
	{
		Delete_book(bookhead, bookName);
		printf("\t\t 删除成功\n");
	}

	ShowBook();
}

/**
 * 函数描述：找书
 * 函数参数：无
 * 函数返回值：无
*/
void findbook()
{
	printf("\t\t 请输入书名：");
	scanf("%s", bookName);
	int ret;
	ret = search_book(bookhead, bookName);
	
	if (ret == FAILURE)
	{
		printf("\t\t 书本不存在\n");
	}
	else
	{
		Locate_book(bookhead, bookName);
	}
	
}

/**
 * 函数描述：还书
 * 函数参数：无
 * 函数返回值：无
*/
void ReturnBook()
{
	printf("\t\t 请输入学号");
	int id;
	scanf("%d", &id);
	int ret;
	ret = search_stu(stuhead, id);
	if (ret == FAILURE || ret == FALSE)//id不存在
	{
		printf("\t\t id不存在，无法还书\n");
	}
	else//id存在
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
		if(head->count != 0)//id有欠书
		{
			printf("\t\t 姓名：%-10s ID：%-10d 借书本数：%-3d\n", head->name, head->id, head->count);
			int i = 0;
			for (i = 0; i < head->count; i++)//输出欠的书
			{
				printf("\t\t 书名：%-10s 本数：1\n", head->book[i]);
			}
			printf("\t\t 输入要还的书：");
			scanf("%s",bookName);
			int bookresult = search_book(bookhead, bookName);

			if(bookresult != FAILURE)//图书馆存在这本书的记录
			{
				for (i = 0; i < head->count; i++)//还书
				{	
					if (strcmp(bookName, head->book[i]) == 0)
					{
						//学生信息修改
						printf("\t\t 还书成功\n");
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
						//printf("\t\t 还书成功1\n");
						
						//图书馆书籍存储信息修改
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
						//printf("\t\t 还书成功2\n");
						head_book->count++;
						head_book->number--;
						head_book->flag = 1;
						break;
					}
				}
			}
			else//图书馆不存在书的记录
			{
				printf("\t\t 输入错误\n");
			}

		}
		else//id无欠书
		{
			printf("\t\t 无欠书\n");
		}
		
	}

}

/**
 * 函数描述：学生借书情况
 * 函数参数：无
 * 函数返回值：无
*/
void StuBorrowState()
{	
	int id;
	printf("\t\t 输入ID:");
	scanf("%d",&id);
	//查询学号，判断在不在
	int result;
	result = Locate_stu(stuhead, id);
	
	if (result == FAILURE)//不在
	{
		printf("\t\t 查无此人\n");
	}
}

/**
 * 函数描述：借书
 * 函数参数：无
 * 函数返回值：无
*/
void BorrowBook()
{
	pstu head;
	pbook head_book;
	int id = 0;

	printf("\t\t 请输入学号：");
	scanf("%d", &id);

	//遍历g_student数组，判断学生是否借过书
	int result;
	result = search_stu(stuhead, id);  //判断ID是否存在
	if (result == FAILURE)    //不存在，给新的学生申请内存
	{
		printf("\t\t 未查询到您，请注册\n");
		char name[32] = {0};

		printf("\t\t 请输入姓名：");//输入姓名
		scanf("%s", name);
		printf("\t\t 请输入学号：");
		scanf("%d", &id);
		int sturesult = search_stu(stuhead, id);
		while (sturesult != FAILURE)
		{
			printf("\t\t 学号已被注册，请重新输入学号\n");
			printf("\t\t 请输入学号：");
			scanf("%d", &id);
			sturesult = search_stu(stuhead, id);
		}

		InsertStuLink(stuhead, name, id);

		printf("\t\t 要借哪本书：");
		scanf("%s", name);

		//判断书存不存在
		result = search_book(bookhead, name);
		if (FAILURE == result)   //书本不存在
		{
			printf("\t\t 书本不存在，借书失败\n");
			return;
		}
		else          //书本存在
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
			if (0 == head_book->count)    //书本全借出
			{
				head_book->flag = 0;
				printf("\t\t 书本已全部借出\n");
			}
			else
			{
				head_book->count--;
				head_book->number++;
				if (0 == head_book->count)
				{
					head_book->flag = 0;      //书本不可借
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
				strcpy(head->book[head->count], name);   //保存书名
				head->count++;    //借书的本数加一
				printf("\t\t 借书成功\n");
			}
		}
	}
	else                 //存在，判断借书是否达到上限
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

		if (head->count < 5)//未达上限，允许借书
		{
			printf("\t\t 输入要借的书名：");
			scanf("%s", bookName);
			int bookresult;
			bookresult = search_book(bookhead, bookName);
			if(bookresult != FAILURE)//找到书本
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
					//学生信息修改
					head->count++;
					head->book[head->count - 1] = (char *)malloc(sizeof(char) * 32);
					strcpy(head->book[head->count - 1], bookName);
					//图书馆信息修改
					head_book->count--;
					head_book->number++;
					if (head_book->count == 0)
					{
						head_book->flag = 0;
					}
					printf("\t\t 借书成功\n");
				}
				else
				{
					printf("\t\t 书本已全部借完\n");
				}
				
			}
			else
			{
				printf("\t\t 没找到书，快滚\n");
			}
		}
		else
		{
			printf("\t\t 已达借书上限，请先归还书本\n");
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
