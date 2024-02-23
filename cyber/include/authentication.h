#ifndef __AUTHENTICATION_H_CR4__ 
#define __AUTHENTICATION_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */

#define PATH "./auth.cr4"

typedef enum return_value
{
	AUTHENTICATED = 0,
	AUTHENTICATION_FAILED = 1,
	SYSTEM_ERROR = 2
}status;

/*
 * Description : AddUser inserts an encrypted version of a user crdentials into 
					the clients data base.
 * Arguments : 'user' ia a user name, 'password' is a user's passwerd,
 * Special notes : using this function will create a maintanence file in user 
					device.
					do not use ':' in your password.
 * Return : return value 0 indicating successful insertion, and 2 indicating 
 			failure due to system failure.
 */
status AuthAddUser(char *user, char *password);

/* 
 * Description : DeleteUser deletes data about a user from the user's data base.
 * Arguments : 'user' ia a user name, 'password' is a user's passwerd,
				'data_base' is the pointer to the data structure.
 * Return : return value 0 indicating successful deletion and 2 indicating 
 			failure due to system failure. 
 */
int AuthDeleteUser(char *user);

/* 
 * Description : Authenticate looks for the data given about a user, 
 					in the existing data from the user's data base.
					if a user data exists, the user is authenticated.
 * Arguments : 'user' ia a user name, 'password' is a user's passwerd,
				'data_base' is the pointer to the data structure.
 * Return : return value 0 indicating successful authentication, 1 indicating
 			failed authentication and 2 indicating failure due to system failure.
 */
status AuthAuthenticate(char *user, char *password);

#endif /* __AUTHENTICATION_H_CR4__ */
