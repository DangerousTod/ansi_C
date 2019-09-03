/* gcc -Wall -std=c99 -pedantic -o xgauss nrutil.c gaussj.c xgaussj.c -lm */
/* Compiler executable checksum: aa420de397aec2b7ab2a7ae25509eb7e */
#include <stdio.h>
#include <stdlib.h>
#include "nr.h"

#define NP 20
#define MP 20
#define MAXSTR 80

int main(void)
{
  int j,k,l,m,n;
  float **a,**ai,**u,**b,**x,**t;
  char dummy[MAXSTR];
  FILE *fp;
  char filename[15];
  char ch;

  a=matrix(1,NP,1,NP);
  ai=matrix(1,NP,1,NP);
  u=matrix(1,NP,1,NP);
  b=matrix(1,NP,1,MP);
  x=matrix(1,NP,1,MP);
  t=matrix(1,NP,1,MP);

  printf("Enter data object for gauss jordan \n");
  scanf("%s", filename);
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Must have matrix for gauss jordan \nCannot open file \n");
    printf("Matrix should be in .dat\n");
    exit(0);
  }
/*  if ((fp = fopen("matrx1.dat","r")) == NULL) */
/*    nrerror("Data file matrx1.dat not found\n"); */
/* while (!feof(fp)) { */
  ch = fgetc(fp);
  while (ch != EOF) {
    fgets(dummy,MAXSTR,fp);
    fgets(dummy,MAXSTR,fp);
    fscanf(fp,"%d %d ",&n,&m);
    fgets(dummy,MAXSTR,fp);
    for (k=1;k<=n;k++)
      for (l=1;l<=n;l++) fscanf(fp,"%f ",&a[k][l]);
    fgets(dummy,MAXSTR,fp);
    for (l=1;l<=m;l++)
      for (k=1;k<=n;k++) fscanf(fp,"%f ",&b[k][l]);
    /* save matrices for later testing of results */
    for (l=1;l<=n;l++) {
      for (k=1;k<=n;k++) ai[k][l]=a[k][l];
      for (k=1;k<=m;k++) x[l][k]=b[l][k];
    }
    /* invert matrix */
    /*void gaussj(float **a, int n, float **b, int m);*/
    gaussj(ai,n,x,m);
    printf("\nInverse of matrix a : \n");
    for (k=1;k<=n;k++) {
      for (l=1;l<=n;l++) printf("%12.6f",ai[k][l]);
      printf("\n");
    }
    /* check inverse */
    printf("\na times a-inverse:\n");
    for (k=1;k<=n;k++) {
      for (l=1;l<=n;l++) {
        u[k][l]=0.0;
        for (j=1;j<=n;j++)
          u[k][l] += (a[k][j]*ai[j][l]);
      }
      for (l=1;l<=n;l++) printf("%f12.6f",u[k][l]);
      printf("\n");
    }
    /* check vector solutions */
    printf("\nCheck the following for equality:\n");
    printf("%21s %14s\n","original","matrix*sol'n");
    for (l=1;l<=m;l++) {
      printf("vector %2d: \n",l);
      for (k=1;k<=n;k++) {
        t[k][l]=0.0;
        for (j=1;j<=n;j++)
          t[k][l] += (a[k][j]*x[j][l]);
        printf("%8s %12.6f %12.6f\n"," ",
          b[k][l],t[k][l]);
      }
    }
    printf("************************************\n");
    printf("press RETURN for next problem:\n");
    (void) getchar();
  }
  fclose(fp);
  free_matrix(t,1,NP,1,MP);
  free_matrix(x,1,NP,1,MP);
  free_matrix(b,1,NP,1,MP);
  free_matrix(u,1,NP,1,NP);
  free_matrix(ai,1,NP,1,NP);
  free_matrix(a,1,NP,1,NP);
  return 0;
}
