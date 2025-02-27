#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
// Matrix Ai has dimension p[i-1] x p[i]
// for i = 1..n
int MatrixChainOrder(int p[], int n)
{

	/* For simplicity of the program, one
	extra row and one extra column are
	allocated in m[][]. 0th row and 0th
	column of m[][] are not used */
	int m[n][n];
	int s[n][n];

	int i, j, k, L, q;

	/* m[i, j] = Minimum number of scalar
	multiplications needed to compute the
	matrix A[i]A[i+1]...A[j] = A[i..j] where
	dimension of A[i] is p[i-1] x p[i] */

	// cost is zero when multiplying
	// one matrix.
	for (i = 1; i < n; i++)
	{
		m[i][i] = 0;
		s[i][i] = 0;
	}
	// L is chain length.
	for (L = 2; L < n; L++)
	{
		for (i = 1; i < n - L + 1; i++)
		{
			j = i + L - 1;
			m[i][j] = INT_MAX;
			for (k = i; k <= j - 1; k++)
			{
				// q = cost/scalar multiplications
				q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
			//cout<<"m value:"<<m[i][j]<<" ";
			//cout<<"   s value: "<<s[i][j]<<"   ";
		}
	}
	//cout<<"\n"<<"Final value ";
	// for (int i = 1; i < n; i++)
	// {
	// 	for (int j = 1; j < i; j++)
	// 	{
	// 		printf("-\t");
	// 	}
	// 	for (int j = i; j < n; j++)
	// 	{
	// 		printf("%d\t", m[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// for (int i = 1; i < n; i++)
	// {
	// 	for (int j = 1; j < i; j++)
	// 	{
	// 		printf("- ");
	// 	}
	// 	for (int j = i; j < n; j++)
	// 	{
	// 		printf("%d ", s[i][j]);
	// 	}
	// 	printf("\n");
	// }
	printf("\n");
	printf("\nMinimum number of multiplications is  : %d", m[1][n - 1]);
	return m[1][n - 1];
}

// Driver Code
int main()
{
	//srand(time(0));
	FILE *fptr;
	fptr = fopen("./dp_matrixchain.txt", "w");
	fprintf(fptr,"n,avg_time_take_ms\n");
	for (int n = 3; n <= 22; n++)
	{
		float sum=0.0000,avg=0.0000;
		for (int i = 0; i < 2; i++)
		{
			int a[n];
			for (int j = 0; j < n; j++)
			{
				a[j] = rand() % 10 + 1;
			}
			// printf("\nArray elements are : \n");
			// for (int j = 0; j < 6; j++)
			// {
			// 	printf("%d , ", a[j]);
			// }
			float start_time = clock();
			//printf("\nMatrix table and table for bracket is : \n");
			int x = MatrixChainOrder(a, n);
			printf("\n");
			float end_time = clock();
			sum=(end_time - start_time) * 1000 / CLOCKS_PER_SEC+sum;
			printf("n is %d Run %d: %f ms\n", n, i + 1, (end_time - start_time) * 1000 / CLOCKS_PER_SEC);
		}
		avg=sum/2;
		fprintf(fptr,"%d,%0.4f\n",n,avg);
	}
	fclose(fptr);
	return 0;
}
