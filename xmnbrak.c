/* gcc -Wall -std=c99 -pedantic -o xmnbrak nrutil-ansi.c bessj0.c mnbrak.c xmnbrak.c -lm */
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include "nr.h"

float func(float x)
{
	return bessj0(x);
}

int main(void)
{
	float ax,bx,cx,fa,fb,fc;
	int i;

	for (i=1;i<=1000;i++){
//		ax=i*0.5;
//		bx=(i+1)*0.5;
		ax=i*6.6;
		bx=(i+i)*3;
		mnbrak(&ax,&bx,&cx,&fa,&fb,&fc,func);
		printf("\n%4d %12s %12s %12s\n",i,"a","b","c");
		printf("%3s %14.6f %12.6f %12.6f\n","x",ax,bx,cx);
		printf("%3s %14.6f %12.6f %12.6f\n","f",fa,fb,fc);
	}
	return 0;
}
