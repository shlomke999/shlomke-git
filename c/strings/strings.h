#ifndef __STRING_F__
#define __STRING_F__
#include<stddef.h>


int StrCmp(const char *s1, const char *s2);
size_t StrLen (const char *s);
char *StrCpy(char *dest, const char *src);
char *StrnCpy(char *dest, const char *src, size_t n);
int StrnCmp(char const *str1_ptr, char const *str2_ptr, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *s, int c);
char *StrDup(const char *s);
char *StrCat(char *dest, const char *src);
char *StrnCat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);
int IsPalindrome(char *s);


char MyToLower(char c);
























#endif 	
