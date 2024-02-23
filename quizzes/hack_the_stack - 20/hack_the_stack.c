#include <stdio.h>


void func2(void  *arg) 
{
    long f2;
    printf("Enter func2\n");
 
    /* AREA2 */

	 *(&f2 + 3) = *(long *)((long *)arg + 3	) ;   /* change the return address of func2 to return address of func1 */
	
	 *(long *)((long *)arg + 3 ) = *(long *)((long *)arg + 7 ) ;   /*change func1 return to return address of main, and skipping mains last print*/

 	/*same as before in a little diff ways: */
/* 
    *(&f2 + 3) = *(long *)((long *)arg + 3	) ;   	
	*(long *)((long *)arg + 3 ) = *(long *)((long *)arg + 7 ) ; 
*/

/*
	*(long *)((long*)arg - 1) = *(long *)((long *) arg + 3);
	*(long *)((long *) arg + 3) = *(long *)((long *) arg + 7);
*/    
    
/* 
    *(&f2 + 3) = *(&f2 + 7 );   	
	*(long *)((long *)arg + 3 ) = *(long *)((long *)arg + 7 ); 
*/
/*
     *(&f2 + 3) = *(&f2 + 7 );   	
	 *(&f2 + 7 ) = *(&f2 + 11 );
*/	 
/*                                                           the coolest way:
	  *(long *)((long*)arg - 1) = *(long *)((long *) arg + 3);
      *(&f2) = (func2 + 296);
      *(size_t *)(arg + 24) = *(&f2);
*/

	  

    
    printf("Exit func2\n");
}

void func1() 
{
    long f1;
    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");
}
 
int main()
{
    const long x = 1;
    long y = 5;
 
    /* AREA1          
    (*(long *)&x) = 1337;     
    (*(&y + 1) = 1337);
    */

 
    printf("x = %lu\n",x);
    func1();
 
    printf("Exit main\n");
    return 0;
}
