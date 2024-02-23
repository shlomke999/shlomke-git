#include <string.h> /* strcmp */
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <math.h> /* pow */

#include "../include/hash_table.h"

#define UNUSED(x) (void)(x)
#define SIZE (500)

struct hash_table
{
    size_t index_amount;
    hashfunc_t hashFunc;
    cmpfunc_t hashcmp;      /*string compare function*/
    slist_t **bucket_list;
};


size_t HashFunc(char *str)
{
	size_t i = 0, size = 0;
	const int p = 53; /* closest prime to */
	const size_t m = (pow(10, 9) + 9); /* very big prime */
	long hash_value = 0, power = 1;
	size = strlen(str);
	for (i = 0; i < (size - 1); ++i)
	{
		hash_value = (hash_value + (str[i] - 'a' + 1) * power) % m;
		power = (power * p) % m;
	}
	return hash_value;
}


/*check if keybored input is in hash table*/
void IsInDict(hash_table_t *table)
{
	char input[64] = {"good luck"};
	while('0' != *input)
	{
		fscanf(stdin, "%s", input);
		if ('0' == *input)
		{
			break;
		}
		if (!HashFind(table, input))
		{
			printf("Your spelling sucks! XD\n");
		}
	}
}



	void SpellCheck()
{
	char *buffer = (char *)malloc(1000000);
	char *keep = buffer;
	FILE *dict = fopen("/usr/share/dict/words", "r");
	int indicator = 0;
	hash_table_t *table = HashCreate(1600, (hashfunc_t)HashFunc, (cmpfunc_t)strcmp);
	while (EOF != fscanf(dict, "%s", buffer))
	{
		indicator += HashInsert(table, buffer);
		buffer += (strlen(buffer) + 1);
	}
	if (indicator)
	{
		printf("Insert Failed\n");
	}
	IsInDict(table);
	HashDestroy(table);
	fclose(dict);
	free(keep);
	keep = NULL;
	return;
}




int PrintData(void *data, void *param)
{
    UNUSED(param);
    printf(" %s  \n", (char *)data);
    return 0;
}


int main(void)
{
	char *result = NULL;
	int i = 0, test = 0;
	char str[] = {"shani"};
	FILE *file = fopen("/usr/share/dict/words", "r"); /*dictionary*/
	char *buffer = (char *)malloc(99990);
	char *words = buffer;
	long key = HashFunc(str);
									/************  create  test  *******************/
									
	hash_table_t *hash_table = HashCreate(SIZE, (hashfunc_t)HashFunc, (cmpfunc_t)strcmp);

	for (i = 0; i < SIZE; ++i)
	{
							/********************	 size test  ******************/
		printf ("hash table size is: %ld\n", HashSize(hash_table));
		printf ("\n");
		
							/*************	 is empty test   ******************/	
		printf ("return 1 if hash table is empty: %d\n", HashIsEmpty(hash_table));
		printf ("\n");
		
		
		
							/*******************	 insert test  ****************/
		fscanf(file, "%s", buffer);
		test += HashInsert(hash_table, buffer);
		buffer += (strlen(buffer) + 1);
		if (test)
		{
			printf("insert faild\n");
		}
		

		
		
							/*******************	find test *******************/
		result = (char *)HashFind(hash_table, "Adolph");							
		printf ("try to find element - Adolph - in the list: %s\n", result);
		printf ("\n");
		result = (char *)HashFind(hash_table, "API");							
		printf ("try to find element - API - in the list: %s\n", result);
		printf ("\n");
	}	


							/********************	 foreach test  *********************/	
		 HashForEach(hash_table, PrintData, 0);
		 printf ("\n");
		 
		SpellCheck();	
							/********************	 remove  test  *****************/
		HashRemove(hash_table, "API");
		printf ("                			   ************   remove test:  *************  removing API now:\n");
		printf ("\n");	
		result = (char *)HashFind(hash_table, "API");							
		printf ("try to find element - API - in the list: %s\n", result);
		printf ("\n");





						/***********************   destroy   ***********************/									
		HashDestroy(hash_table);
		fclose(file);
		free(words);
		words = NULL;









		/*** hash func  ***/
key %= 1000;
printf("the hash key is: %ld\n", key);	
return (0);
}










