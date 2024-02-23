#include <stdio.h>

#include "../include/slist.h"



int IsMatch(const void *data, void *param)
{
  	if(*(int *)data == *(int *)param)
  	{
    		return 1;
  	}
  	return 0;
}


int Add(void *data, void *param) 
{
    	int *value = data;
    	*value += *(int *)param;
    	return 0;
}


int PrintList(void *data ,void *param)
{
	(*(int*)data >= 10) ? printf("    %d\n  <****> \n" , *((int *)data)) :
	  	printf("    %d\n  <***> \n" , *((int *)data));

  	return 0;
}

int main(void)
{
  slist_t *my_list = SListCreate();
  int i = 0 ,nums[] = {1 , 2 , 3, 4 , 5 , 6 , 7 , 8 ,9 ,10};
  slist_iter_t head = SListStart(my_list);
  int a = 10;
  for(i = 9; i >= 0; --i)
  {
  							/*slist insert before*/
     SListInsertBefore(head, (void *)&nums[i]);  
  }
  
  							/*slist size*/
  printf("%d\n", SListSize(my_list));
  
  
                            /*slist find*/
  if(SListFind(SListStart(my_list), SListEnd(my_list), IsMatch, &nums[6]))
  {
  	printf("found iter %d\n",nums[6]);
  }
  
  							/*slist for each*/
  
 	 (SListForEach(SListStart(my_list), SListEnd(my_list), Add, &a));
 	 (SListForEach(SListStart(my_list), SListEnd(my_list), PrintList, NULL));
  
  
  
  							/*slist destroy*/
  SListDestroy(my_list);
  
  
  
  return 0;
}




