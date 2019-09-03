/* gcc -Wall -std=c99 -pedantic -o xjacobi nrutil-ansi.c jacobi.c xjacobi.c -lm */
#include <stdio.h>
#include<stdlib.h>
#include "nr.h"
#include "nrutil.h"

#define NP 20
#define NMAT 3
//#define NMAT 5

int main(void)
{
	int i,j,k,kk,l,ll,nrot;
	static float a[3][3]=
		{1.0,2.0,3.0,
		2.0,2.0,3.0,
		3.0,3.0,3.0};
	static float b[5][5]=
		{-2.0,-1.0,0.0,1.0,2.0,
		-1.0,-1.0,0.0,1.0,2.0,
		0.0,0.0,0.0,1.0,2.0,
		1.0,1.0,1.0,1.0,2.0,
		2.0,2.0,2.0,2.0,2.0};
//	static float b[7][7]=
//		{-4.0,-3.0,-2.0,-1.0,0.0,1.0,2.0,
//		-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0,
//		-2.0,1.0,0.0,1.0,2.0,3.0,4.0,
//		0.0,0.0,0.0,0.0,1.0,3.0,2.0,
//		4.0,3.0,2.0,1.0,0.0,-1.0,-2.0,
//		3.0,2.0,1.0,0.0,-1.0,-2.0,-3.0,
//		2.0,1.0,0.0,-1.0,-2.0,-3.0,-4.0};
	static float c[NP][NP]=
		{10.0,9.0,8.0,6.2,1.0,-2.2,-3.0,-5.0,-6.1,-7.0,
		8.2,7.0,6.0,3.0,1.0,-2.0,-2.8,-3.2,-4.1,-5.5,
		8.0,7.0,5.0,4.0,1.0,-1.6,-2.1,-2.4,-3.3,-4.1,
		5.4,4.2,3.2,2.0,1.0,-1.1,-1.2,-2.1,-3.0,-3.6,
		9.0,8.0,7.0,5.2,0.0,-1.2,-2.0,-4.0,-5.1,-6.0,
		7.2,6.0,5.0,4.0,0.0,-1.0,-1.8,-3.2,-4.1,-5.5,
		7.0,5.0,4.0,3.0,0.0,-0.6,-1.1,-1.4,-2.3,-3.1,
		4.4,3.2,2.2,1.0,0.0,-0.1,-0.2,-1.1,-2.0,-2.6,
		4.0,3.1,2.7,1.1,3.2,2.2,2.0,1.0,0.0,-1.0,
		1.0,2.0,3.0,4.0,5.0,4.0,3.0,2.0,1.0,0.0,
		0.0,1.0,2.0,3.0,4.0,5.0,4.0,3.0,2.0,1.0,
		-1.0,0.0,1.0,2.0,2.2,3.2,1.1,2.7,3.1,4.0,
		-2.6,-2.0,-1.1,-0.2,-0.1,0.0,1.0,2.2,3.2,4.4,
		-3.1,-2.3,-1.4,-1.1,-0.6,0.0,3.0,4.0,5.0,7.0,
		-5.5,-4.1,-3.2,-1.8,-1.0,0.0,4.0,5.0,6.0,7.2,
		-6.0,-5.1,-4.0,-2.0,-1.2,0.0,5.2,7.0,8.0,9.0,
		-3.6,-3.0,-2.1,-1.2,-1.1,1.0,2.0,3.2,4.2,5.4,
		-4.1,-3.3,-2.4,-2.1,-1.6,1.0,4.0,5.0,7.0,8.0,
		-5.5,-4.1,-3.2,-2.8,-2.0,1.0,3.0,6.0,7.0,8.2,
		-7.0,-6.1,-5.0,-3.0,-2.2,1.0,6.2,8.0,9.0,10.0};
	float *d,*r,**v,**e;
	static int num[4]={0,3,5,20};
//	static int num[4]={0,5,7,20};

	d=vector(1,NP);
	r=vector(1,NP);
	v=matrix(1,NP,1,NP);
	for(i=1;i<=NMAT;i++) {
		if (i ==1) e=convert_matrix(&a[0][0],1,num[i],1,num[i]);
		else if ( i == 2 ) e=convert_matrix(&b[0][0],1,num[i],1,num[i]);
		else if ( i == 3 ) e=convert_matrix(&c[0][0],1,num[i],1,num[i]);
		jacobi(e,num[i],d,v,&nrot);
		printf("matrix number %2d\n",i);
		printf("number of JACOBI rotations: %3d\n",nrot);
		printf("eigenvalues: \n");
		for (j=1;j<=num[i];j++) {
			printf("%12.6f",d[j]);
			if ((k % 5 ) == 0) printf("\n");
//			if ((k % 7 ) == 0) printf("\n");
		}
		printf("\neigenvectors:\n");
		for (j=1;j<=num[i];j++) {
			printf("%9s %3d \n","number",j);
			for (k=1;k<=num[i];k++) {
				printf("%12.6f",v[k][j]);
				if ((k % 5) == 0) printf("\n");
//				if ((k % 7) == 0) printf("\n");
			}
			printf("\n");
		}
		/* eigenvector test */
		printf("eigenvector test\n");
		for (j=1;j<=num[i];j++) {
			for (l=1;l<=num[i];l++) {
				r[l]=0.0;
				for (k=1;k<=num[i];k++) {
					if (k > l) {
						kk=l;
						ll=k;
					} else {
						kk=k;
						ll=l;
					}
					r[l] += (e[ll][kk]*v[k][j]);
				}
			}
			printf("vector number %3d\n",j);
			printf("%11s %14s %10s\n",
			"vector","mtrx*vec.","ratio");
			for (l=1;l<=num[i];l++)
				printf("%12.6f %12.6f %12.6f\n",
					v[l][j],r[l],r[l]/v[l][j]);
		}
		printf("press RETURN to continue...\n");
		(void) getchar();
		free_convert_matrix(e,1,num[i],1,num[i]);
	}
	free_matrix(v,1,NP,1,NP);
	free_vector(r,1,NP);
	free_vector(d,1,NP);
	return 0;
}
