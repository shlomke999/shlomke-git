#include <stdio.h>
#include <stdlib.h>
 



/* STATUS: APPROVED.
/* by: michael aponin. 
*/
void NullifyMatrix(int row,int col,int array[row][col])
{
    int i = 0; 
    int j = 0; 
    int k = 0;
    
    int *rowptr = malloc(sizeof(int)*row) ; 

    int *colptr = malloc(sizeof(int)*col) ;
    
    for (i=0; i<row ; i++)
    {
        for (j=0; j<col ; j++)
        {
            if (array[i][j] == 0 )
            {
            	rowptr[k] = i;
                colptr[k] = j;
            	
            	++k;
            }
        }
    }
    
    for (i=0; i<k ; i++)
    {
        for (j=0; j<col ; j++)
        {
            array[rowptr[i]][j]=0;
        }
        for (j=0; j<row ; j++)
        {
            array[j][colptr[i]]=0;
        }
    }        	
    
    free(rowptr);
    free(colptr);
    rowptr = NULL; 
    colptr = NULL; 
}

int main()
{
    int array[3][4] = {{0,1,2,3},{4,5,3,8},{4,6,10,0} };
    
    NullifyMatrix(3,4,array);
    
    
    
    return 0;
}

