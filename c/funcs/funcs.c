#include<stdio.h> /*for get char function*/
#include<stdlib.h>/*to use exit*/

#include"funcs.h"

/* Status : approved
reviewer : nimrod
description : print T-pressed or A-pressed is user press it and ESC to exit 
return : void
special notes :*/

void IfelseKey()
{
	char c;
	system("stty -icanon -echo");
	while(1)
	{
		c = getchar();
		if('A' == c)
		{
			printf("A-pressed\n");
		}
		else if('T' == c)
		{
			printf("T-pressed\n");
		}
		else if(27 == c)
		{
			system("stty icanon echo");
			exit(0);
		}
	}

}

/* Status : approved
reviewer : nimrod
description : print T-pressed or A-pressed is user press it and ESC to exit 
return : void
special notes :*/
void SwitchKey()
{
	char c;
	system("stty -icanon -echo");
	
	while (1)
	{
		c = getchar();
		
		switch (c)
		{
			case ('A'):
				printf("A-Pressed\n");
				break;
			case ('T'):
				printf("T-Pressed\n");
				break;
			case (27):
				system("stty icanon echo");
				exit(0);
		}
	}
	

}



void CharA()
{
	printf("A-pressed");
}

void CharT()
{
	printf("T-pressed");
}

void CharEsc()
{
	system("stty icanon echo");
	exit(0);
}

void EmptyFunc(){}


void LutKey()
{
	typedef void(*Key) (void);
	char c;
	int i = 0;
	Key arr[128];

	for (; i < 128; ++i)
	{
		arr[i] = EmptyFunc;
	}
	
	arr['A'] = CharA;
	arr['T'] = CharT;
	arr[27] = CharEsc;
	system("stty -icanon -echo");
	while (1)
	{
		c = getchar();
		arr[(unsigned char)c]();
	}	
}




