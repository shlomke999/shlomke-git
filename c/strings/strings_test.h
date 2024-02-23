#ifndef __STRING_F__
#define __STRING_F__

/* compare two strings, return 0 if the s1 and s2 are equal, a negative value if 
s1 is less than s2; a positive value if s1 is greater than s2. */
int StrCmp(const char *s1, const char *s2);
/* get string length excluding nul char */
size_t StrLen (const char *s);
/*copy source string to dest string up to n number of characters*/
char *StrnCpy(char *dest, const char *src, size_t n);
/* compare two strings up to position n*/
int StrnCmp(char const *str1_ptr, char const *str2_ptr, size_t n);
/*same as the one before but case insensitive*/
int StrCaseCmp(const char *s1, const char *s2);
/*search for c character in *s string, return a pointer to first occurence, or 
null if not found*/
char *StrChr(const char *s, int c);
/* duplicates source string to a newly allocated (with malloc) string, return a 
pointer to the new string*/
char *StrDup(const char *s);
/*append crs string to dest string, rewriting its null terminaator, including
append src null terminator at the end*/
char *StrCat(char *dest, const char *src);
/*same as the one before but up to n number of appends*/
char *StrnCat(char *dest, const char *src, size_t n);
/* find substring (needle) in string(haystack), return pointer to location in 
heystack or NULL if not found*/		
char *StrStr(const char *haystack, const char *needle);






















#endif 		
