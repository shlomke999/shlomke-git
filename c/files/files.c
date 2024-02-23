#include <stdio.h>  /*for print*/
#include <stdlib.h> /*for exit*/
#include <string.h> /*for strcmp*/
#include "files.h"

void Print(int x)
{
	printf("%d\n", x);
}


/* 
exercise 1.
Status : approved
reviewer : 	michel the 1st
description : create struct array, go through its elements and call print 
function for each element.
return : void
special notes :
*/
void PrintStruct()
{
	struct print_me
	{		
		int x; 
		void (*pf)(int);
	};
	struct print_me arr[10];
	
	int i = 0;
	
	while (i < 10)
	{
		arr[i].x = (i + 5);
		arr[i].pf = &Print;
		++i;	
	}
	
	i = 0;
	while (i < 10)
	{
		arr[i].pf(arr[i].x);
		++i;	
	}
}

/* 
exercise 2.1.
Status : approved
reviewer : 	michel the 1st
description : open a file, write to it and do all kind of operations depending 
on the input.
return : int
special notes :
*/
int WriteToFile(char *filename)
{
	int n = 100;
	char buff[101];	
	FILE *my_file = NULL;
	while(1)
	{
		my_file = fopen(filename, "a");
		if(NULL == my_file)
		{
			return 1;
		}
		fgets(buff, n, stdin);
		fputs(buff, my_file);
		fclose(my_file);
	}
	return 0;
}


enum return_v RemoveFile(char *file, char *nada)
{
	if(0 == remove(file))
	{
		return SUCCESS;
	}
	return FILE_NOT_REMOVED;
}


enum return_v Count(char *file, char *nada)
{
	char c;
	int counter = 0;
	FILE *file_p = NULL;
	
	file_p = fopen(file, "r");
	if(NULL == file_p)
	{
		return FILE_ERROR;
	}
	
	while (EOF != (c = fgetc(file_p)))
	{
		if ('\n' == c)
		{
			++counter;
		}
	}
	printf("%d lines\n", counter);
	return SUCCESS;
}


enum return_v Prepend(char *file, char *str)
{
	char c;
	FILE *temp_file = NULL;
	FILE *file_p = NULL;
	
	temp_file = fopen("temp_file.txt", "a");
	if(NULL == temp_file)
	{
		return FILE_ERROR;
	}
	
	file_p    = fopen(file, "r");
	if(NULL == file_p)
	{
		return FILE_ERROR;
	}
	
	fputs(str+2, temp_file);
	
	while(EOF != (c = fgetc(file_p)))
	{
		fputc(c, temp_file);
	}
	
	fclose(file_p);
	fclose(temp_file);
	remove(file);
	rename("temp_file.txt", file);
	return SUCCESS;
}


enum return_v Append(char *file, char *str)
{
	FILE *file_p = NULL;
	
	file_p = fopen(file, "a");
	if(NULL == file_p)
	{
		return FILE_ERROR;
	}
	
	fputs(str, file_p);
	fclose(file_p);
	return SUCCESS;
}


enum return_v Exit(char *file, char *nada)
{
	return EXIT;
}


/* 
exercise 2.2 - 2.3.
Status : approved
reviewer : 	michel the 1st
description : open a file, write to it and do all kind of operations depending 
on the input.
return : void
special notes :
*/
void FWriteSpecial(char *filename)
{
	enum return_v val;
	struct funcs
	{
		char *str;
		int (*p_strncmp)(const char*, const char*, size_t);
		enum return_v (*p_special)(char*, char*);		
	};
	int i = 0, n = 100;
	int fflag = 0;
	char buff[101];	
	
	struct funcs arr[4] =
	{
		{"-remove", strncmp, RemoveFile},
		{"-count",  strncmp, Count },
		{"-exit" ,  strncmp, Exit  },
		{"< ",      strncmp, Prepend},
	};
	
	while (1)
	{
		fflag = 0;
		val = SUCCESS;
		fgets(buff, n, stdin);
		for (i = 0; i < 4; i++)
		{
			if(0 == arr[i].p_strncmp(arr[i].str, buff, strlen(arr[i].str)))
			{
				val = arr[i].p_special(filename, buff);
				fflag = 1;
				break;
			}
		}
		if(fflag == 0 )
		{
			val = Append(filename, buff);
		}
		if(val != SUCCESS)
		{
			break;
		}
	}
	
	switch(val)
	{
		case SUCCESS:
		case EXIT:
			printf("exiting program\n");
			break;
		case FILE_ERROR:
			printf("file error occured\n");
			break;
		case FILE_NOT_REMOVED:
			printf("file not removed\n");
			break;
		default:
			printf("an error happened\n");
			break;
	}
}

