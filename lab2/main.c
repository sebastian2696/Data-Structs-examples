#include <stdio.h>
#include <stdlib.h>

#include "mean_median.h"


int main (int argc, char* argv[])
{
	//create a pointer, which will be used to store the array
	int *A;

	//check if the user ran the program correctly
	if (argc < 2) {
		fprintf(stderr, "Usage: mean_median file1 [file2 ...]\n");
	}

	//if the program is run correctly argv[1] will be the first
	//command line argument. ie name of the input file
	char *file = argv[1];

	//open file for reading
	FILE *fp = fopen(file, "rb");
	if (fp == NULL)
		return 1;

	//call read_array function which will allocate space for A
	//read the file and put the numbers in array A
	//the read_array function must return the size of the array
	int n = read_array(fp, &A);
	if (n < 0) {
		return 1;
	}

	//print array A of size n
	print_array(A, n);
	
	//sort
	select_sort(A, n);
	
	//print again
	print_array(A, n);

	//calculate mean and median of array A
	double mean = mean_array(A, n);
	double med = median_array(A, n);

	//print results
	printf("mean = %f med = %f\n", mean, med);

	//cleanup
	free(A);
	fclose(fp);

	return 0;
}
