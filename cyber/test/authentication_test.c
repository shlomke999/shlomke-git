#include <stdio.h> /*printf */

#include "../include/authentication.h"


int main()
{	
	printf("add user test:\n");	
	printf("%d \n" ,AuthAddUser("libby","NoPassword") );
	
	printf("%d \n" ,AuthAddUser("liraz","admin") );
   

	printf("delete user test:\n");		
	printf("%d \n" ,AuthDeleteUser("lulan") );
	
	printf("%d \n" ,AuthDeleteUser("lol") );
	
	printf("%d \n" ,AuthDeleteUser("noam") );
	
	
	printf("Authenticate  test:\n");			
	printf("%d \n" ,AuthAuthenticate("libby","NoPassword") );
	printf("%d \n" ,AuthAuthenticate("liraz","admin") );
	printf("%d \n" ,AuthAuthenticate("nimrod","kol") );

	
	
	return 0; 
	
}

