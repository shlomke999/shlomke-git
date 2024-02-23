#ifndef __FILES_H_CR4__
#define __FILES_H_CR4__

#include <stdio.h>  /*for print*/
#include <stdlib.h> /*for exit*/
#include <string.h> /*for strcmp*/

enum return_v{SUCCESS, FILE_ERROR, FILE_NOT_REMOVED, EXIT};

/* 
exercise 1.
Status : approved
reviewer : 	michel the 1st
description : create struct array, go through its elements and call print 
function for each element.
return : void
special notes :
*/
void PrintStruct();

/* 
exercise 2.1.
Status : approved
reviewer : 	michel the 1st
description : open a file, write to it and do all kind of operations depending 
on the input.
return : void
special notes :
*/
int WriteToFile(char *filename);
enum return_v RemoveFile(char *file, char *nada);  
enum return_v Count(char *file, char *nada);
enum return_v Prepend(char *file, char *str);
enum return_v Append(char *file, char *str);
enum return_v Exit(char *file, char *nada);
void FWriteSpecial(char *filename);

#endif
