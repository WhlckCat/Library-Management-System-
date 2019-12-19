#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LinkList/LinkList.h"
#include "FileManagement.h"

FILE *fstu;
FILE *fbook;

int Fprint_stu(FILE *fstu, pstu h)
{
    h = h->next;
    while(h)
    {
        fprintf(fstu, "%s %d %d ", h->name, h->id, h->count);
        for (int i = 0; i < h->count; i++)
            fprintf(fstu, "%s ", h->book[i]);
        h = h->next;
    }

    return SUCCESS;
}

int Fprint_book(FILE *fbook, pbook h)
{
    h = h->next;
    while(h)
    {
        fprintf(fbook, "%s %d %d %d %d", h->name, h->count, h->number, h->sum, h->flag);
        h = h->next;
    }

    return SUCCESS;
}

int Finsert_stu(pstu h,stu studentType)
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

    strcpy(m->name, studentType.name);
    m->id = studentType.id;
    m->count = studentType.count;
    for (int i = 0; i < m->count; i++)
    {
        m->book[i] = (char *)malloc(sizeof(char) * 32);
        strcpy(m->book[i], studentType.book[i]);
    }
    m->next = h->next;
    h->next = m;

    return SUCCESS;
}

int Finsert_book(pbook h, book bookType)
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

    strcpy(m->name, bookType.name);
    m->count = bookType.count;
    m->number = bookType.number;
    m->sum = bookType.sum;
    m->flag = bookType.flag;
    m->next = h->next;
    h->next = m;

    return SUCCESS;
}

int Fscan_stu(FILE *fstudent, pstu h)
{
    stu studentType;
    int flag = getc(fstudent);//确认指针是否指向文件末尾

    while(flag != EOF)
    {
        fseek(fstudent, -1L, SEEK_CUR);
        fscanf(fstudent, "%s%d%d", studentType.name, &studentType.id, &studentType.count);
        for(int i = 0; i < studentType.count; i++)
        {
            studentType.book[i] = (char *)malloc(sizeof(char) * 32);
            fscanf(fstudent, "%s", studentType.book[i]);
        }
        Finsert_stu(h, studentType);
        flag = getc(fstudent);
    }

    return 0;
}

int Fscan_book(FILE *fbook, pbook h)
{
    book bookType;
    int flag = getc(fbook);

    while(flag != EOF)
    {
        fseek(fbook, -1L, SEEK_CUR);
        fscanf(fbook, "%s%d%d%d%d", bookType.name, &bookType.count, &bookType.number, &bookType.sum, &bookType.flag);
        Finsert_book(h, bookType);
        flag = getc(fbook);
    }

    return SUCCESS;
}

void Fileinit()
{
    fstu = fopen("stu_doc", "a+");
    if (NULL == fstu)
    {
        printf("\t\t 无法打开学生信息文件\n");
        exit(0);
    }
    fbook = fopen("book_doc", "a+");
    if (NULL == fbook)
    {
        printf("\t\t 无法打开书本信息文件\n");
        exit(0);
    }
}

int Fileclose()
{
    if (fclose(fstu) != 0)
        fprintf(stderr, "\t\t 关闭学生信息文件失败\n");
    if (fclose(fbook) != 0)
        fprintf(stderr, "\t\t 关闭书本信息文件失败\n");

    return 0;
}

void FileopenNew()
{
    fstu = fopen("stu_doc", "w");
    if (NULL == fstu)
    {
        printf("\t\t 无法打开学生信息文件\n");
        exit(0);
    }
    fbook = fopen("book_doc", "w");
    if (NULL == fbook)
    {
        printf("\t\t 无法打开书本信息文件\n");
        exit(0);
    }
}