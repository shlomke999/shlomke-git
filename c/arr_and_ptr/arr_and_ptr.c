#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Josephus(int size)
{
	int *arr = (int*) malloc(sizeof(int) * size);
	int i = 0;
	int result;
	while (i < size -1)
	{
		arr[i] = i + 1;
		i++;
	}
	arr[i] = 0;
	i = 0;
	while (arr[i] != arr[arr[i]])
	{
		printf("arr[%d] %d\n",i, arr[i]);
		arr[i] = arr[arr[i]];
		printf("arr[%d] %d\n",i, arr[i]);
		i++;
		i = i % size;
	}
	result = arr[i];
	free(arr);
	return result;
	
}


void Free2D_Arr(char ** arr, int size_of_arr){

	int j;
    	for(j = 0; j < size_of_arr; j++)
        	free(arr[j]);
 
    	free(arr);
}


void Free2D_int_Arr(int ** arr, int size_of_arr){

	int j = 0;
    	for(j = 0; j < size_of_arr; j++)
        	free(arr[j]);
 
    	free(arr);
}


int Get_Envp_Len(char **envp){
	int i;
	for(i = 0; envp[i] != 0; i++);
	return i;
}


char **EnvToLower(char **envp)
{

	char **buffer;
	int i = 0, j = 0, envp_len;
	
	envp_len = Get_Envp_Len(envp);
	buffer = (char**)malloc(sizeof(envp) * envp_len);
	
	for (i = 0 ; envp[i] != 0; i++)
	{
		buffer[i] = (char*)malloc(sizeof(char*) * (strlen(envp[i])));
		strcpy(buffer[i], envp[i]);
		
		for (j = 0; '\0' != buffer[i][j]; j++)
		{
			buffer[i][j] = tolower(buffer[i][j]);	
		}
		printf("%s\n", buffer[i]);
	}
/*free the dynamically allocated memory */
	Free2D_Arr(buffer, envp_len);
	return NULL;				
			
}


void Matrix_Sum(int **arr, int *dest_arr, int n , int m )
{
	int i = 0, j = 0, k = 0, sum;
	for (i = 0; i < n; i++){
		sum = 0;
		for (j = 0; j < m; j++)
		{
			sum += arr[i][j];
		}
		dest_arr[k] = sum;
		++k;
	}
}


void c_data_types()
{
	unsigned char u_char;
	char caracter;
	unsigned int u_int;
	int integer;
	unsigned short int u_short_int;
	unsigned long int u_long_int;
	long int long_int;
	long double long_dbl;
	double dbl;
	float floating;
	printf("size of u_char is %d \n",sizeof(u_char));
	printf("size of caracter is %d \n", sizeof(caracter));
	printf("size of unsigned int %d \n", sizeof(u_int));
	printf("size of int is %d \n", sizeof(integer));
	printf("size of unsigned short int  is %d \n", sizeof(u_short_int));
	printf("size of u_long_int is %d \n", sizeof(u_long_int));
	printf("size of long_int is %d \n", sizeof(long_int));
	printf("size of long_dbl is %d \n", sizeof(long_dbl));
	printf("size of dbl is %d \n",sizeof(dbl));
	printf("size of floating is %d \n",sizeof(floating));
}


void init2d_Arr(int **arr, int n, int m)
{
	int i, j;
	for ( i = 0 ; i < n; i++)
	{
		for ( j = 0 ; j < m; j++)
		  arr[i][j] = i + j; 
	}
}


void alloc2darr(int **arr, int n, int m)
{
	int i;
	arr  = (int**)malloc(sizeof(int*) * n);
	for ( i = 0 ; i < n; i++)
	{
		arr[i] =(int*)malloc(sizeof(int) * m);
	}
}


int main(int argc, char **argv, char **envp)
{

	int i, j, n = 7 , m = 9;
	int* dest_arr;
	int **numbers;
		
	printf("here1 \n");
	numbers  = (int**)malloc(sizeof(int*) * n);
	for ( i = 0 ; i < n; i++)
	{
		numbers[i] =(int*)malloc(sizeof(int) * m);
	}
	/*alloc2darr(numbers,n,m);*/
	printf("here2 \n");
	init2d_Arr(numbers, n, m);
	printf("here3 \n");
	dest_arr = (int*) malloc(sizeof(int) * n);
	printf("here4 \n");
	Matrix_Sum(numbers, dest_arr, n, m);
	printf("here5 \n");
	for(i = 0 ; i < n; i++)
	{
		printf("%d\n", dest_arr[i]);
	}
	printf("here6 \n");
	Free2D_int_Arr(numbers, n);
	printf("here7 \n");
	free(dest_arr);
	return 0;
}





	/*EnvToLower(envp);
	printf("%d\n", Josephus(100));
*/



