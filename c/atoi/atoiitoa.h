#ifndef __ATOIITOA_H_CR4__
#define __ATOIITOA_H_CR4__

#define IS_LITTLE_ENDIAN() ((char*)'1' - 48)


char * Itoa(int n, char *buffer, int radix);

int Atoi(const char *nptr);

char *Itoa36(int value, char *string, int radix);

int Atoi36(const char *nptr, int radix);

int AtoiVsAtoi(char *str);

void TestAtoi(char *str);

void InTwoOutOfThree(char arr1[], char arr2[], char arr3[]);

int IsLittleEndian();



#endif
