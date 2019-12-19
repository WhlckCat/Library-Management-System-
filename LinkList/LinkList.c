#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkList.h"

/**
 * 函数描述：初始化学生，书本链表
 * 函数参数：学生链表表头地址，书本链表表头地址
 * 函数返回值：FAILURE SUCCESS
*/
int Init_stu_book_list(pbook *book_h, pstu *stu_h)
{
    if (book_h == NULL || stu_h == NULL)
    {
        printf("初始化失败\n");
    }

    *stu_h = (pstu)malloc(sizeof(stu) * 1);
    *book_h = (pbook)malloc(sizeof(book) * 1);
    if (NULL == *stu_h || NULL == *book_h)
    {
        return FAILURE;
    }

    (*stu_h)->next = NULL;
    (*book_h)->next = NULL;

    return SUCCESS;
}

/**
 * 函数描述：学生链表插入元素
 * 函数参数：学生链表表头 学生名 学生ID
 * 函数返回值：FAILURE SUCCESS
*/
int InsertStuLink(pstu h, char stu_name[32], int stu_id)
{
    if (NULL == h)
    {
        return FAILURE;
    }

    pstu m = (pstu)malloc(sizeof(stu) * 1);
    if (NULL == m)
    {
        return FAILURE;
    }
    strcpy(m->name, stu_name);
    m->id = stu_id;
    m->next = h->next;
    h->next = m;

    return SUCCESS;
}

/**
 * 函数描述：书本链表插入元素
 * 函数参数：书本链表表头 书名 书本本数
 * 函数返回值：FAILURE SUCCESS
*/
int InsertBookLink(pbook h, char book_name[32], int book_count)
{
    if (NULL == h)
    {
        return FAILURE;
    }

    pbook m = (pbook)malloc(sizeof(stu) * 1);
    if (NULL == m)
    {
        return FAILURE;
    }
    strcpy(m->name, book_name);
    m->sum = book_count;
    m->count = book_count;
    m->number = 0;
    m->flag = 1;
    m->next = h->next;
    h->next = m;
}

/**
 * 函数描述：输出学生链表到屏幕
 * 函数参数：学生链表表头
 * 函数返回值：FAILURE SUCCESS
*/
int Traverse_stuLink(pstu h)
{
    if (NULL == h)
    {
        return FAILURE;
    }

    pstu n = h->next;
    while(n)
    {
        printf("\t\t 学生姓名: %-10s 学号: %-10d 已借本数：%-3d", n->name, n->id, n->count);
        printf("已借书名：");
        int i;
        for (i = 0; i < n->count; i++)
        {
            printf("%-10s ", n->book[i]);
        }
        printf("\n");

        n = n->next;
    }

    return SUCCESS;
}

/**
 * 函数描述：输出书本链表到屏幕
 * 函数参数：书本链表表头
 * 函数返回值：FAILURE SUCCESS
*/
int Traverse_bookLink(pbook h)
{
    if (NULL == h)
    {
        return FAILURE;
    }

    pbook n = h->next;
    while(n)
    {
        printf("\t\t 书名：%-10s 可借本数：%-3d 已借本数：%-3d 总本数：%-3d 是否可借：%-4s", 
                n->name, n->count, n->number, n->sum, (n->flag == 1) ? "可借" : "不可借");
        printf("\n");

        n = n->next;
    }

    return SUCCESS;
}

int add_book_num(pbook h, char book_name[32], int book_count)
{
    if(NULL == h)
    {
        return FAILURE;
    }

    h = h->next;
    while(h)
    {
        if ((strcmp(h->name,book_name)) == 0)
        {
            h->count += book_count;
            h->sum += book_count;
            h->flag = 1;
        }
        else
        {
            h = h->next;
        }   
    }
    return FAILURE;
}

/**
 * 函数描述：定位学生
 * 函数参数：学生链表表头 学生ID
 * 函数返回值：FAILURE SUCCESS
*/
int Locate_stu(pstu h, int id)
{
    if(NULL == h)
    {
        return FAILURE;
    }

    h = h->next;
    while(h)
    {
        if (h->id == id)
        {
            printf("\t\t 学生姓名：%-10s 学号：%-10d 已借本数：%-3d", h->name, h->id, h->count);
            printf("已借书名：");
            int i;
            for (i = 0; i < h->count; i++)
            {
                printf("%-10s ", h->book[i]);
            }
            printf("\n");
            
            return SUCCESS;
        }
        else
        {
            h = h->next;
        }
    }

    return FAILURE;
}

/**
 * 函数描述：定位书本
 * 函数参数：书本链表表头 书本
 * 函数返回值：FAILURE SUCCESS
*/
int Locate_book(pbook h, char name[32])
{
    if(NULL == h)
    {
        return FAILURE;
    }

    h = h->next;
    while(h)
    {
        if ((strcmp(h->name,name)) == 0)
        {
            printf("\t\t 书名：%-10s 可借本数：%-3d 已借本数：%-3d 总本数：%-3d 是否可借：%-4s", 
                    h->name, h->count, h->number, h->sum, (h->flag == 1) ? "可借" : "不可借");
            printf("\n");

            return SUCCESS;
        }
        else
        {
            h = h->next;
        }
        
    }

    return FAILURE;
}

int search_book(pbook h, char name[32])
{
    if(NULL == h)
    {
        return FALSE;
    }

    h = h->next;
    while(h)
    {
        if ((strcmp(h->name,name)) == 0)
        {
            return SUCCESS;
        }
        else
        {
            h = h->next;
        }
    }

    return FAILURE;
}

int search_stu(pstu h, int id)
{
    if(NULL == h)
    {
        return FALSE;
    }

    h = h->next;
    while(h)
    {
        if (h->id == id)
        {
            return SUCCESS;
        }
        else
        {
            h = h->next;
        }
    }

    return FAILURE;
}

/**
 * 函数描述：删除书本
 * 函数参数：书本链表表头 书本
 * 函数返回值：FAILURE SUCCESS
*/
int Delete_book(pbook h, char name[32])
{
    if (NULL == h)
    {
        return FAILURE;
    }

    pbook n = h->next;
    int n_count = 0;
    while(n)
    {
        if ((strcmp(n->name, name)) == 0)
        {
            pbook pro_n = h->next;
            int i;
            for (i = 0; i < n_count - 1; i++)
            {
                pro_n = pro_n->next;
            }
            pro_n->next = n->next;
            n->next = NULL;
            free(n);
            return n_count;
        }
        n = n->next;
        n_count++;
    }

    return FALSE;
}