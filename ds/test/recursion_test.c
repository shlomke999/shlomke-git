#include <stdlib.h> /* malloc */
#include <stddef.h> /* NULL size_t */
#include <stdio.h> /*printf */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */


#include "../include/recursion.h"







/* #############################                    
status: approved          
reviewer: Adi            
description: this func create a stack 
return: ptr to stack or 0 if failed      
special notes: uses malloc          
#############################*/












#define AMOUNT 5


static void Print(Node *head)
{
	printf("List:\n");
	while(NULL != head->next)
	{
		printf("%d -> ", head->val);
		head = head->next;
	}
	printf("%d\n", head->val);
}


int main()
{
	int i = 0, nodes = 10;
	Node *head = NULL, *list = NULL;
	char *str1 = "hello", str2[20] = "shlomke ", *str3 = "helklo", buffer[20];
	
	int int1 = 1 ;
	int int2 = 0 ;
	int int3 = 5 ;
	int int4 = 4 ;
	int int5 = -2 ;
	stack_t *my_stack_ptr  = NULL; 
	void *peek_ptr  = NULL;

	
	for (i=0 ; i < 5 ; ++i)	
		{
			printf("fibonacci recursion:\n");
		    printf("%d\n " , FibonacciRecursion(i)); 
			printf("fibonacci loop:\n");
		    printf("%d\n " , Fibonacci(i)); 
		}
		printf ("\n");
	
	 /*  * Checking the FlipList function  */
	printf ("		***flip list test***\n\n");
	list = (Node *)malloc(sizeof(Node));
	head = list;
	for(i = 0; i < nodes; ++i)
	{
		head->val = i;
		head->next = (Node *)malloc(sizeof(Node));
		head = head->next;
	}
	head->val = i;
	head->next = NULL;

	Print(list);
	list = FlipList(list);
	Print(list);

	head = list;
	while(NULL != head)
	{
		list = head->next;
		free(head);
		head = list;
	}
	printf ("\n");
	
	
	
									/*stack tests*/
	printf ("		***stack sort test***\n\n");
	
	my_stack_ptr = StackCreate(5 , 4);
	
	StackPush(my_stack_ptr , &int1 ); 
	
	StackPush(my_stack_ptr , &int2 ); 
	
	StackPush(my_stack_ptr , &int3 ); 
		
	StackPush(my_stack_ptr , &int4 ); 
			
	StackPush(my_stack_ptr , &int5 ); 
	
		printf("stack size is %ld \n" , StackSize(my_stack_ptr));
	SortStack(my_stack_ptr);
		printf("stack size is %ld \n" , StackSize(my_stack_ptr));
	
	printf("%d \n" , *(int *) StackPeek(my_stack_ptr));
	StackPop(my_stack_ptr);
	

	printf("%d \n" , *(int *) StackPeek(my_stack_ptr));
	StackPop(my_stack_ptr);
	

	printf("%d \n" , *(int *) StackPeek(my_stack_ptr));
	StackPop(my_stack_ptr);
	

	printf("%d \n" , *(int *) StackPeek(my_stack_ptr));
	StackPop(my_stack_ptr);
	

	printf("%d \n" , *(int *) StackPeek(my_stack_ptr));
	StackPop(my_stack_ptr);
	
	
	StackDestroy(my_stack_ptr);
		printf("\n" );




	
	
										/* strlen test */
	printf ("		***strlen test***\n\n");
	printf ("our strlen:\n");
	printf("%ld\n", StrLen(str1));
	printf ("original strlen:\n");
	printf("%ld\n", strlen(str1));  
	
	printf ("\n\n\n");
										/* strcmp test */
	printf ("		***strcmp test***\n\n");
	printf ("our strcmp\n");
	printf("%d\n", StrCmp(str1, str2));
	printf ("original strcmp\n");
	printf("%d\n", strcmp(str1, str2));  
	
	printf ("our strcmp:\n");
	printf("%d\n", StrCmp(str1, str3));
	printf ("original strcmp:\n");
	printf("%d\n", strcmp(str1, str3));  
	
	printf ("\n\n\n");
											/* strcpy test */
	printf ("***		strcpy test***\n\n");
	printf ("our strcpy:\n");
	printf("%s\n", StrCpy(buffer, str3));
	printf ("original strcpy:\n");
	printf("%s\n", StrCpy(buffer, str3));
	printf ("\n\n\n");

											/* strcat test */
											printf ("***strcat test***\n\n");	
	printf ("our strcat:\n");
	printf("%s \n",StrCat(str2, str1));
	printf ("\n\n\n");

											/* strstr test */
	printf ("		***strstr test***\n\n");	
	printf ("original strstr:\n");
	printf("%s \n",strstr(str2, str1));
	printf ("our strstr:\n");
	printf("%s \n",StrStrRecursive(str2, str1));
	printf ("\n");
	
											
											
	
	

	return 0;
}

