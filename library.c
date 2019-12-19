#include <stdio.h>
#include <stdlib.h>
#include "function/function.h"

int main()
{
	char choice[2] = {0};
	init();

	while (1)
	{
		menu();	
		scanf("%s", choice);

		switch(choice[0])
		{
			case '1':
				addbook();
				break;
			case '2':
				deletebook();
				break;
			case '3':
				ShowBook();
				break;
			case '4':
				findbook();
				break;
			case '5':
				BorrowBook();
				break;
			case '6':
				ReturnBook();
				break;
			case '7':
				StuBorrowState();
				break;
			case '8':
				exit_system();
				break;
		}
	}

	return 0;
}
