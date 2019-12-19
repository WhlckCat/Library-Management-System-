#ifndef _FILEMANAGEMENT_H
#define _FILEMANAGEMENT_H

int Fprint_stu(FILE *fstu, pstu h);
int Fprint_book(FILE *fbook, pbook h);
int Finsert_stu(pstu h,stu studentType);
int Finsert_book(pbook h, book bookType);
int Fscan_stu(FILE *fstudent, pstu h);
int Fscan_book(FILE *fbook, pbook h);
void Fileinit();
int Fileclose();
void FileopenNew();

#endif