#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkList.h"

/**
 * ������������ʼ��ѧ�����鱾����
 * ����������ѧ�������ͷ��ַ���鱾�����ͷ��ַ
 * ��������ֵ��FAILURE SUCCESS
*/
int Init_stu_book_list(pbook *book_h, pstu *stu_h)
{
    if (book_h == NULL || stu_h == NULL)
    {
        printf("��ʼ��ʧ��\n");
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
 * ����������ѧ���������Ԫ��
 * ����������ѧ�������ͷ ѧ���� ѧ��ID
 * ��������ֵ��FAILURE SUCCESS
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
 * �����������鱾�������Ԫ��
 * �����������鱾�����ͷ ���� �鱾����
 * ��������ֵ��FAILURE SUCCESS
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
 * �������������ѧ��������Ļ
 * ����������ѧ�������ͷ
 * ��������ֵ��FAILURE SUCCESS
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
        printf("\t\t ѧ������: %-10s ѧ��: %-10d �ѽ豾����%-3d", n->name, n->id, n->count);
        printf("�ѽ�������");
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
 * ��������������鱾������Ļ
 * �����������鱾�����ͷ
 * ��������ֵ��FAILURE SUCCESS
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
        printf("\t\t ������%-10s �ɽ豾����%-3d �ѽ豾����%-3d �ܱ�����%-3d �Ƿ�ɽ裺%-4s", 
                n->name, n->count, n->number, n->sum, (n->flag == 1) ? "�ɽ�" : "���ɽ�");
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
 * ������������λѧ��
 * ����������ѧ�������ͷ ѧ��ID
 * ��������ֵ��FAILURE SUCCESS
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
            printf("\t\t ѧ��������%-10s ѧ�ţ�%-10d �ѽ豾����%-3d", h->name, h->id, h->count);
            printf("�ѽ�������");
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
 * ������������λ�鱾
 * �����������鱾�����ͷ �鱾
 * ��������ֵ��FAILURE SUCCESS
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
            printf("\t\t ������%-10s �ɽ豾����%-3d �ѽ豾����%-3d �ܱ�����%-3d �Ƿ�ɽ裺%-4s", 
                    h->name, h->count, h->number, h->sum, (h->flag == 1) ? "�ɽ�" : "���ɽ�");
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
 * ����������ɾ���鱾
 * �����������鱾�����ͷ �鱾
 * ��������ֵ��FAILURE SUCCESS
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