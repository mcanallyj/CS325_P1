#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>


//Algorithm 1: Enumeration
struct sumHolder {
	int value;
	int i;
	int j;
};


struct sumHolder findMaxSum(int * A, int n, int i) {
	int z = 0;

	struct sumHolder returnSum;

	//if n = 1
	//return A[n]
	if (n == 1) {
		returnSum.value = A[i+0];
		returnSum.i = i+0;
		returnSum.j = i+0;
	} else 
	//if n = 2
	//return greater of A[0], A[1] or sum of A[0] and A[1], along with i, j
	if (n == 2) {
		int sum1 = A[i+0];
		int sum2 = A[i+1];
		int sum3 = A[i+0] + A[i+1];
		if (sum1 > sum2 && sum1 > sum3) {
			returnSum.value = sum1;
			returnSum.i = i+0;
			returnSum.j = i+0;
		} else if (sum2 > sum1 && sum2 > sum3) {
			returnSum.value = sum2;
			returnSum.i = i+1;
			returnSum.j = i+1;
		} else {
			returnSum.value = sum3;
			returnSum.i = i+0;
			returnSum.j = i+1;
		}
		//printf("returned value=%d, i=%d, j=%d\n", returnSum.value, returnSum.i, returnSum.j);
		return returnSum;
	} else {
	//if n > 2
	//k = n/2
	//return greater of findMaxSum(A[0..k-1]) and findMaxSum(A[k..n-1])
	
		int k = n/2;
		//printf("k=%d\n", k);
		//find max sum from first half
		struct sumHolder leftMax = findMaxSum(A, k, i);
		//printf("rSum1.value=%d, rsum1.i=%d, rsum1.j=%d, n=%d, k=%d\n", rSum1.value, rSum1.i, rSum1.j, n, k);
		
		//find max sum from second half
		struct sumHolder rightMax = findMaxSum(A, n-k, k+i);
		//printf("rSum2.value=%d, rsum2.i=%d, rsum2.j=%d\n", rSum2.value, rSum2.i, rSum2.j);
		
		struct sumHolder centerMax;
		int crossSum = 0;
		int sum = 0;

		//printf("leftMax=%d, i=%d, j=%d -- rightMax=%d, i=%d, j=%d\n", leftMax.value, leftMax.i, leftMax.j, rightMax.value, rightMax.i, rightMax.j);
		int left_sum = -1000000000;
		int right_sum = -1000000000;
		

			
		sum = 0;
		for (z = k-1; z >= 0; z--) {
			sum = sum + A[z+i];
			//printf("\nLEFT k=%d z=%d sum=%d\n", k, z, sum);
			if (sum > left_sum) {
				left_sum = sum;
				centerMax.i = z+i;
			}
		}
		sum = 0;
		for (z = k; z < n; z++) {
			sum = sum + A[z+i];
			//printf("\nRIGHT k=%d z=%d sum=%d\n", k, z, sum);
			if (sum > right_sum) {
				right_sum = sum;
				centerMax.j = z+i;
			}
		}

		//printf("left_sum=%d right_sum=%d i=%d j=%d\n", left_sum, right_sum, centerMax.i, centerMax.j);
		centerMax.value = left_sum + right_sum;


		//printf("Left=%d Right=%d Center=%d\n", leftMax.value, rightMax.value, centerMax.value);
		if (rightMax.value >= leftMax.value && rightMax.value >= centerMax.value) {
			returnSum = rightMax;
		} else if (leftMax.value >= rightMax.value && leftMax.value >= centerMax.value) {
			returnSum = leftMax;
		} else {
			returnSum = centerMax;
		}

	}
	
	/*
	for (z=0; z < n; z++) {
		printf("%d ", A[z+i]);
	}
	printf("  ** returnSum.value=%d, i=%d, j=%d\n", returnSum.value, returnSum.i, returnSum.j);
	*/
	return returnSum;

}

struct sumHolder * getMaxSub_Enum(int * A, struct sumHolder * x, int n) {
	//Algorithm 1: Enumeration
	int i, j, k, sum;
	i = j = k = 0;
	
	x->value = 0;

	for (j=0; j<n; j++) {
			
		for (i=0; i<j; i++) {
				
			sum = 0;
			//printf("i=%d, j=%d", i, j);
			for (k=i; k<j+1; k++) {
				sum+=A[k];
			}
			//printf(" sum=%d\n", sum);
			if (sum > x->value) {
				x->value = sum;
				x->i = i;
				x->j = j; 
			}
		}
	}
	return x;
}

struct sumHolder * getMaxSub_SmartEnum(int * A, struct sumHolder * x, int n) {
	
	int i, j, sum;
	i = j = 0;
	x->value = 0;

	for (i=0; i<n; i++) {
		sum = 0;
		for (j=i; j<n; j++) {
			//printf("i=%d, j=%d", i, j);
			sum+=A[j];
			//printf(" sum=%d, largestSum.value=%d\n", sum, largestSum.value);
			if (sum > x->value) {
				x->value = sum;
				x->i = i;
				x->j = j; 
			}
		}
	}
	return x;
}

struct sumHolder * getMaxSub_Linear(int * A, struct sumHolder * x, int n) {
	int z, reset, sum;
	sum = reset = 0;
	x->value = sum = A[0];
	x->i = 0;
	x->j = 0;

	for (z=1; z<n; z++) {

		//reset beginning of sub array
		if (reset == 1) {
			x->i = z;
			reset = 0;
		}

		//add next element
		sum+=A[z];
		
		//check if sum is greater than last recorded biggest subarray
		if (x->value <= sum) {
			x->value = sum;
			x->j = z;

		}
		//printf("subArray[%d]=%d i=%d j=%d largestSum.value=%d sum=%d\n", z, subArray[z], largestSum.i, largestSum.j, largestSum.value, sum);
	
		if (sum < 0) {
			//reset sum
			sum = 0;
			//flag subarray beginning to be set to next element
			reset = 1;
		}


	}
	return x;
}

int main() {

	FILE *fin;
	FILE *fout;
	char line[256];

	fin = fopen("MSS_Problems.txt", "r");
	if (fin == NULL) {
		perror("Error opening input file");
		return -1;
	}

	fout = fopen("MSS_Results.txt", "w");
	if (fout == NULL) {
		perror("Error opening output file");
		return -1;
	}

	struct sumHolder largestSum;
	
	int i, j, k, sum, n;
	i = j = k = sum = n = 0;
	char num[256];
	int subArray[256];

	while (fgets(line, sizeof(line), fin)) {
		//int subArray[256] = {0};
		//for each character in line (terminated by '\n')
		k = n = j = 0;
		for (i = 0; line[i] != '\n'; i++) {
			
			//if character is number or '-'
			if ((line[i] > 47 && line[i] < 58) || line[i] == 45) {
				
				//character added to word array
				num[j] = line[i];
				j++;
			} else {
				
				//if character is not a number and word array is not empty
				if (j != 0) {
					
					//null terminate for parsing
					num[j] = '\0';
					
					//add parsed word to integer array
					subArray[k] = atoi(num);
					k++;
					n++;
					j = 0;  
				}
			}
		}

		subArray[k] = '\0';

		fprintf(fout, "Provided Array is: [ ");
		for (i=0; i<n; i++) {
			fprintf(fout, "%d ", subArray[i]);
		}
		fprintf(fout, "]");


		fprintf(fout, "\n\n Algorithm 1: Enumeration\n");
		
		largestSum = *getMaxSub_Enum(subArray, &largestSum, n);
		fprintf(fout, "  - Largest sum is: %d, which starts at index %d and ends at %d\n", largestSum.value, largestSum.i, largestSum.j);
		fprintf(fout, "  - Numbers included in sum are: [ ");
		for (j=largestSum.i; j<(largestSum.j)+1; j++) {
			fprintf(fout, "%d ", subArray[j]);
		}
		fprintf(fout, "]\n\n Algorithm 2: Smart Enumeration\n");

		largestSum = *getMaxSub_SmartEnum(subArray, &largestSum, n);
		fprintf(fout, "  - Largest sum is: %d, which starts at index %d and ends at %d\n", largestSum.value, largestSum.i, largestSum.j);
		fprintf(fout, "  - Numbers included in sum are: [ ");
		for (j=largestSum.i; j<(largestSum.j)+1; j++) {
			fprintf(fout, "%d ", subArray[j]);
		}
		fprintf(fout, "]\n\n Algorithm 3: Divide and Conquer\n");

		largestSum = findMaxSum(subArray, n, 0);
		fprintf(fout, "  - Largest sum is: %d, which starts at index %d and ends at %d\n", largestSum.value, largestSum.i, largestSum.j);
		fprintf(fout, "  - Numbers included in sum are: [ ");
		for (j=largestSum.i; j<(largestSum.j)+1; j++) {
			fprintf(fout, "%d ", subArray[j]);
		}

		fprintf(fout, "]\n\n Alogrithm 4: Linear\n");
		largestSum = *getMaxSub_Linear(subArray, &largestSum, n);
		fprintf(fout, "  - Largest sum is: %d, which starts at index %d and ends at %d\n", largestSum.value, largestSum.i, largestSum.j);
		fprintf(fout, "  - Numbers included in sum are: [ ");
		for (j=largestSum.i; j<(largestSum.j)+1; j++) {
			fprintf(fout, "%d ", subArray[j]);
		}
		fprintf(fout, "]\n\n\n");

	}



	return 0;
}