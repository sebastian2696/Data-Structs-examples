#ifndef MEAN_MEDIAN_H
#define MEAN_MEDIAN_H

/**
 * Sort integer array A of size n using Selection Sort
 */
void select_sort(int A[], int n);

/**
 * Read the values in the file pointed by fp into array p_A
 * Return number of values read.(Size of A)
 */
int read_array(FILE *fp, int *p_A[]);

/**
 * Print integer array A of size n
 */
void print_array(const int *A, int n);

/**
 * Return the median of array A
 */
double median_array(const int *A, int n);

/**
 * Return the mean of array A
 */
double mean_array(const int *A, int n);

#endif
