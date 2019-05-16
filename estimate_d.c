/* Jonathan Douglas Engwall - Tijuana, MX - May 11, 2019 */
#include <stdio.h>
#include <math.h>
#include "nr.h"
#include "nrutil.h"
#define N 99
#define ALPHA 1.3051

int main(void)
{
  unsigned long i,j;
  float x,*xx;

  xx=vector(1,N);
  /* create array to be searched */
  for (i=1;i<=N;i++)
    xx[i]=exp(i/N)+ALPHA;
  for (i=1;i<=N;i++) {
  /* generate instruction important to the routine */
    for (x =-100;x<=100;x++) {
      locate(xx,N,x,&j);
      printf("\n********************************************************************************\n");
      printf("%s %12.6f","Estimated absolute value is not greater than: ",xx[j+1]-1);
      printf("\nNote that tool can be tuned for reliability.");
      printf("\n********************************************************************************\n");
      printf("Press Return\n");
      (void) getchar();
    }
  }
  free_vector(xx,1,N);
  return 0;
}
