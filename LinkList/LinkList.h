#ifndef _LINKLIST_H
#define _LINKLIST_H

#define SUCCESS    10001
#define FAILURE    10000
#define TURE       10002
#define FALSE      10003

//书本数据链表
struct book
{
    char name[32];
    int count;         //可借本数
    int number;        //已借本数
    int sum;           //总数
    int flag;          //是否可借
    struct book *next;
};
typedef struct book book;
typedef book *pbook;

//学生数据链表
struct student
{
    char name[32];
    int id;
    char *book[5];
    int count;
    struct student *next;
};
typedef struct student stu;
typedef stu *pstu;

int Init_stu_book_list(pbook *book_h, pstu *stu_h);
int InsertStuLink(pstu h, char stu_name[32], int stu_id);
int InsertBookLink(pbook h, char book_name[32], int book_count);
int Traverse_stuLink(pstu h);
int Traverse_bookLink(pbook h);
int Locate_stu(pstu h, int id);
int Locate_book(pbook h, char name[32]);
int Delete_book(pbook h, char name[32]);
int search_book(pbook h, char name[32]);
int add_book_num(pbook h, char book_name[32], int book_count);
int search_stu(pstu h, int id);


#endif