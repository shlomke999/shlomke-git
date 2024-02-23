#define _DEFAULT_SOURE          /*may be rquired for to compile with strdup()*/
#include <stdio.h>		/* printf() 				*/
#include <string.h>		/* std string funcs for testing 	*/
#include <strings.h>		/* strcasecmp() for testing StrCaseCmp 	*/ 
#include <stdlib.h>		/* for free after StrDup testing	*/
#include "strings.h"

#define MAX_LEN  32		/* size for write-testing bufers */
#define N_OFFSET 5		/* n test argument offset from i */


#define MAX_LEN  32		/* size for write-testing bufers */
#define N_OFFSET 5		/* n test argument offset from i */

int main()
{
	char *a_c_ptr = NULL, *b_c_ptr = NULL;
	char *inputs_a[]  = { "abc", "a", "","ABC", "A", "aaaaaaaaaffgfdsgd" };
	char *inputs_b[]  = { "A", "ada","kjkjfghgfgfdjghjf", "a", "", "ABC" };
	char *needles[]   = {"", "a",     "ing",  "oo",  "apple", "apples"};
	char *heystacks[] = {"", "ada", "thing", "dood", "apple", "apple"};
	int is_palindrome_heystack_result[] = { 1, 1, 0, 1, 0, 0 };
	size_t i = 0, std_result = 0, my_result = 0;
	char *found = NULL;
	char str_empty1[MAX_LEN] = {0};
	char str_empty2[MAX_LEN] = {0};




	for (i = 0; (sizeof (inputs_a) / sizeof (inputs_a[0]) ) > i; ++i)
	{
		size_t n_input = N_OFFSET - i;
		/* StrLen */
		if (StrLen(inputs_a[i]) != strlen(inputs_a[i]) )
		{
			printf("Strlen failed on input[%lu]\n", i);
		}
		if (StrCmp(inputs_a[i], inputs_b[i]) != strcmp(inputs_a[i],
		inputs_b[i])) 
		{
			printf("StrCmp failed on input[%lu]\n", i);	
		}
		/*StrCpy*/
		if (0 != strcmp(
			StrCpy (str_empty1, inputs_a[i]),
			strcpy (str_empty2, inputs_a[i]))
		   )
		printf ("StrCpy failed on input[%lu]\n", i);
		memset(str_empty1, '\0', MAX_LEN);
		memset(str_empty2, '\0', MAX_LEN);
		/* StrNCpy */
		if (0 != strcmp (
			strncpy(str_empty1, inputs_a[i], n_input), 
			StrnCpy(str_empty2, inputs_a[i], n_input)
			)
		)
		{	
			printf("StrCpy failed on input[%lu]\n", i);	
			printf("input_a[%lu]: %s\n", i, inputs_a[i]);
			printf("str_empty2: %s\n", str_empty2);
		}
		memset(str_empty1, '\0', MAX_LEN);
		memset(str_empty2, '\0', MAX_LEN);
		/* StrnCmp */
		std_result = strncmp(inputs_a[i], inputs_b[i], n_input);
		my_result  = StrnCmp(inputs_a[i], inputs_b[i], n_input);
		if (std_result != my_result)
		{
			printf("StrNCmp failed on input[%lu]\n", i);	
			printf("input_a[%lu]: %s\n", i, inputs_a[i]);
			printf("input_b[%lu]: %s\n", i, inputs_b[i]);
			printf("n_input: %lu\n", n_input);
			printf("strncmp: %lu\n", std_result);
			printf("StrNCmp: %lu\n", my_result);
		}
		/* StrCaseCmp */
		if (StrCaseCmp(inputs_a[i], inputs_b[i]) !=
			strcasecmp(inputs_a[i], inputs_b[i])
			)
		{
			printf("StrCaseCmp failed on input[%lu]\n", i);
			printf("input_a[%lu]: %s\n", i, inputs_a[i]);
			printf("input_b[%lu]: %s\n", i, inputs_b[i]);
			printf("strcasecmp: %d\n", strcasecmp(inputs_a[i],
				inputs_b[i]));
			printf("StrCaseCmp: %d\n", StrCaseCmp(inputs_a[i],
				inputs_b[i]));
		}
		/* StrChr */
		if (strchr(str_empty1, ('a' + (int)i)) !=
			StrChr(str_empty2, ('a' + (int)i))
			)
		{
			printf("StrChr failed on input[%lu]\n", i);	
		}
		/* StrDup */
		a_c_ptr = StrDup(inputs_a[i]); 
		/* strdup requires non standard compiling
		b_c_ptr = strdup(inputs_a[i]); */
		if (0 != strcmp(a_c_ptr, inputs_a[i]))
		{
			printf("%s\n%s\n", a_c_ptr, inputs_a[i]);
			printf("StrDup failed on input[%lu]\n", i);	
		}
		if (!a_c_ptr)
		{
			free(a_c_ptr);
			a_c_ptr = NULL;
		}
		if (!b_c_ptr)
		{
			free(b_c_ptr);
			a_c_ptr = NULL;
		}
		/* StrCat */
		strcpy(str_empty1, inputs_a[i]);
		strcpy(str_empty2, inputs_a[i]);
		
		strcat(str_empty1, inputs_b[i]);
		StrCat(str_empty2, inputs_b[i]);
		
		if (0 != strcmp(str_empty1, str_empty2))
		{	
			printf("StrCat failed on input[%lu]\n", i);	
		}
		memset(str_empty1, '\0', MAX_LEN);
		memset(str_empty2, '\0', MAX_LEN);	
		/* StrnCat */
		strcpy(str_empty1, inputs_b[i]);
		strcpy(str_empty2, inputs_b[i]);
		
		strncat(str_empty1, inputs_a[i], n_input);
		StrnCat(str_empty2, inputs_a[i], n_input);
		
		if (0 != strcmp(str_empty1, str_empty2))
		{	
			printf("StrNCat failed on input[%lu]\n", i);	
		}
		memset(str_empty1, '\0', MAX_LEN);
		memset(str_empty2, '\0', MAX_LEN);
		/* StrStr */
		if (strstr(heystacks[i], needles[i]) !=
			StrStr(heystacks[i], needles[i])
			)
		{
			printf("StrStr failed on input[%lu]\n", i);
			found = StrStr(heystacks[i], needles[i]);
			if (found)
			{
				printf("%s\n",found);
			}
			else
			{
				printf("\"%s\" was not found in \"%s\".\n",
					needles[i],heystacks[i]);
			}
		}
		/*IsPalindrome  */
		std_result = is_palindrome_heystack_result[i];
		my_result  = IsPalindrome(heystacks[i]); 
		if (std_result != my_result)
		{
			printf("IsPalindrome failed on input[%lu]\n", i);	
			printf("heystacks[%lu]: %s\n", i, heystacks[i]);
			printf("std_result: %lu\n", std_result);
			printf("my_result: %lu\n", my_result);
		}

		



		


	}

	return 0;
}
	

