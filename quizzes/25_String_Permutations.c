#include <stdio.h>
#include <string.h>
 

void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
/* 
approved by elad.

2. l = Starting index of the string
3. r = Ending index of the string. 
*/
void Permute(char *str, int l, int r)
{
    int i = 0;
    if (l == r)
    {
        printf("%s\n", str);
    }
    else 
    {
        for (i = l; i <= r; i++) 
        {
            swap((str + l), (str + i));
            Permute(str, l + 1, r);
            swap((str + l), (str + i)); 
        }
    }
}
 

int main()
{
    char str[] = "ABCDEF";
    int n = strlen(str);
    Permute(str, 0, n - 1);
    
    return 0;
}
