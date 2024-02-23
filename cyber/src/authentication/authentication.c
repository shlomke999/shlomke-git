#define  _GNU_SOURCE    /*get line*/

#include <stddef.h> /* Used for size_t type */
#include <string.h> /*strchr*/
#include <stdio.h> /*get line func*/
#include <crypt.h> /*salt and crypt */


#include "../../include/authentication.h"

#define MAXPASSLEN 74
#define MAXUSERLEN 32
#define PATHTEMP "./authtemp.cr4"

 

 
 /*helper func to check password validity*/
 static status CheckInput(const char *str, size_t maxlen)
 {
 	size_t i = 0;
	
	if (maxlen < strlen(str))
	{
		return AUTHENTICATION_FAILED;
	}	
	while (i < strlen(str))
	{
		if (*str == ':' || *str == '$')
		{
			return AUTHENTICATION_FAILED;
		}
		++str;
		++i;
	}
	return AUTHENTICATED;
 }
 
 
 /*helper func to make sure the user not exist already, and username length obays our reqirements*/ 
 static status IsUserNotExist(char *user)
{	
	char *end_of_username = NULL; 
	char *line = NULL ;
	size_t len = 0 ;
	
	FILE *file = fopen(PATH, "r"); 
	if (file == NULL)
    {
        return SYSTEM_ERROR;
    }
    if (CheckInput(user, MAXUSERLEN))
    {
    	return AUTHENTICATION_FAILED;
    }
    
    while(getline(&line, &len, file) != -1)   /*enter full line from file*/
    {
    	end_of_username = strchr(line, (int)':');
    	
    	if (0 == strncmp(user, line, end_of_username - line) && strlen(user) == (size_t)(end_of_username - line)) /*in case the username is longer, don't return failure*/
    	{
 		    fclose(file);
  		    free(line);  /*free getline's malloc*/
    		return AUTHENTICATION_FAILED;
    	}
    }    
    
    return AUTHENTICATED; 
}

/* Status : approved.
 * Reviewer : ran.
 * Description : AddUser inserts an encrypted version of a user crdentials into 
					the clients data base.
 * Arguments : 'user' ia a user name, 'password' is a user's passwerd,
 * Special notes : using this function will create a maintanence file in user 
					device.
					do not use ':' in your password.
 * Return : return value 0 indicating successful insertion, and 2 indicating 
 			failure due to system failure.
 */
status AuthAddUser(char *user, char *password)
{
	char *salt = NULL; 
	char *new_crypt = NULL;
	FILE *file = NULL; 
	status user_exist_result = AUTHENTICATED; 
	status check_password_input_result = CheckInput(password, MAXPASSLEN);
	
	if (CheckInput(password, MAXPASSLEN))
	{
		return check_password_input_result;
	}
	
	
	user_exist_result = IsUserNotExist(user); 	
	if (AUTHENTICATED != user_exist_result)
	{
		return user_exist_result;
	}
			
	file = fopen(PATH, "a+"); 
	if (file == NULL)
    {
        return SYSTEM_ERROR;
    }
    
    salt = crypt_gensalt(NULL, 8 ,NULL, 0);
    new_crypt = crypt(password, salt); 
    printf ("example hash + salt: %s\n", new_crypt);
    
    fprintf(file, user);
    fprintf(file, ":");
    fprintf(file, new_crypt);
    fprintf(file, "\n");
    
	fclose(file);
	
	return AUTHENTICATED;	
}


/* Status : approved.
 * Reviewer : ran.
 * Description : DeleteUser deletes data about a user from the user's data base.
 * Arguments : 'user' ia a user name, 'password' is a user's passwerd,
 * Return : return value 0 indicating successful deletion and 2 indicating 
 			failure due to system failure. 
 */
int AuthDeleteUser(char *user)
{
	char *end_of_username = NULL; 
	char *line = NULL ;
	size_t len = 0 ;
	FILE *temp_file = NULL;
	FILE *file= NULL;
	
	file = fopen(PATH, "r");
	if (NULL == file)
	{
		return SYSTEM_ERROR;
	}
	temp_file = fopen(PATHTEMP, "a+");
	if (NULL == temp_file)
	{
		return SYSTEM_ERROR;
	}
	
	while (getline(&line, &len, file) != -1)
	{
		end_of_username = strchr(line, (int)':');
		if (0 == strncmp(user, line, end_of_username - line) && strlen(user) == (size_t)(end_of_username - line))
		{
			continue;
		}
		fprintf(temp_file, line);
		fprintf(temp_file, "\n");
	}
	free(line);
	fclose(file);
	fclose(temp_file);
	remove(PATH);
	rename(PATHTEMP, PATH);
	
	return 0;
}


/* 
   Status : approved.
 * Reviewer : ran.
 * Description : Authenticate looks for the data given about a user, 
 					in the existing data in the user's data base.
					if a user data exists, the user is authenticated.
 * Arguments : 'user' ia a user name, 'password' is a user's passwerd,
				'data_base' is the pointer to the data structure.
 * Return : return value 0 indicating successful authentication, 1 indicating
 			failed authentication and 2 indicating failure due to system failure.
 */
status AuthAuthenticate(char *user, char *password)
{
	char *user_crypt = NULL;	
	char *start_salt = NULL; 
	char *end_of_username = NULL; 
	
	char *line = NULL ;
	size_t len = 0 ;
	
	FILE *file;

	file = fopen(PATH, "r"); 
	if (NULL == file)
    {
        return SYSTEM_ERROR;
    }
    
    while(getline(&line, &len, file) != -1)
    {
    	end_of_username = strchr(line, (int)':');
    	
    	if (0 == strncmp(user, line, end_of_username - line) && strlen(user) == (size_t)(end_of_username - line))   /*if username found - check the password*/
    	{
			start_salt = end_of_username + 1;   
			
			/* removing the '/n' for hash */
			*(start_salt + strlen(start_salt) - 1) = '\0';
			
			user_crypt = crypt(password, start_salt);
			
			if ( 0 == strncmp(user_crypt, start_salt, strlen(user_crypt)) ) 
			{
				free(line);
				fclose(file);
				return AUTHENTICATED;
			}
			
			free(line);
			fclose(file);
			return AUTHENTICATION_FAILED; 
    	}
    	
    }
	
	free(line);
	
	fclose(file);
	
 	return AUTHENTICATION_FAILED; 		
}


void Authenticator( char *user, char *password)
{
    if(AUTHENTICATED == AuthAuthenticate(user, password))
    {
        printf("user has been authenticated. \n");
    }

}







