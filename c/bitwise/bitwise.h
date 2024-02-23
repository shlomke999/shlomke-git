#ifndef __FILES_H_CR4__
#define __FILES_H_CR4__


/*calculate sum of x * (2^y)*/
long Pow2(unsigned int x, unsigned int y);

/*check if n is power of 2*/
int IsSquaredNoLoop(unsigned int n);

/*check if n is power of 2 using a loop*/
int IsSquared(unsigned int n);

/*add 1 to a given number*/
int AddOne(int x);

/*get array of ints and print the numbers that have exactlly 3 bits on.*/
void ThreeBitsOn(int arr[], int n);

/*reveres bits in any given number using a loop*/
unsigned int ByteMirror(unsigned int a);

/*reveres bits in a given 1 byte number without a loop*/
unsigned char ByteMirrorNoLoop(unsigned char x);

/*get a char, return 1 if bits 2 and 6 are on*/
int IsBothOn(unsigned char x);

/*get a char, return 1 if at least one of bits 2 and 6 are on*/
int IsOneOn(unsigned char x);

/*get a char, swap its 3rd and 5th bits.*/
int SwapBits(unsigned char x);

/*get a number, find nearest lower number that devieded by 16.*/
unsigned int Divisible16(unsigned int n);

/* # swap two variables without a third one.*/
void Swap(int *x, int *y);

/* # description: count set bits of a number.*/
int CountSetBits(unsigned int x);

/* # description: count set bits of a number, without a loop.*/
int CountSetBitsNoLoop(int n);


#endif

