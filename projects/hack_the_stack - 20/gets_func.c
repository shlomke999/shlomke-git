#include <stdio.h>
#include <string.h>

/*through the cli run the program and make it run PrivilegedAction func*/
void PrivilegedAction()
{
    printf("you made it!\n");
}

int IsAllowedUser(char *username)
{
    return 0;
}

int main () 
{
    char username[8];
    int allow = 0;

    printf("Enter your username, please: ");
    gets(username, 8, stdin);

    if (IsAllowedUser(username)) 
    {
        allow = 1;
    }

    if (allow)
    {
        PrivilegedAction();
    }

    return 0;
}
