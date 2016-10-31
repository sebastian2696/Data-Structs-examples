#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> /* SIZE_MAX */
#include <string.h>
#include <math.h>
#include <limits.h>



void select_sort(int A[], size_t n)
{
	//Your code goes here!
	int min,i;
	int j;
	int m=0;
	//int k;
	for (i=0; i < n; ++i)
	{
    //Find minimum element in the unsorted array
    //Assume it's the first element
    	min = i;
 
    //Loop through the array to find it
    	for (j= i + 1; j < n; ++j)
    	{
    		if (A[j] < A[min])
    		{
        	//Found new minimum position, if present
        		min = j;
    		}
    	}
    	//Swap the values
    	//swap (A[i], A[min_ele_loc]);
    	m = A[i];
    	A[i] = A[min];
    	A[min] = m;
    	
	}	
}

int read_array(FILE *fp, int *p_A[])
{
	//Your code goes here!
	int ch, lines=0;
	int i;
    do
    {
        ch = fgetc(fp);
        if(ch == '\n') lines++;   
    } while( ch != EOF );
//    lines = 10;
//    printf("%d\n",lines);
	//n = sizeof(*p_A)/sizeof(*p_A[0]);
	//*p_A = malloc(sizeof(int *)* INT_MAX);
	*p_A = malloc(sizeof(int *)* lines);
	rewind(fp);
	if ( p_A == NULL )
	{
    	/* we have a problem */
    	printf("So Sad\nExiting the program....\n");
		exit(1);
    	return -1;
	}
	for (i=0;i<lines;i++)
	{
		fscanf(fp,"%i", &((*p_A)[i]));
//		printf("%d",*(p_A)[i]);
	}
	return lines;
}

void print_array(const int *A, int n)
{
	//Your code goes here!
	int i;
	for(i=0;i<n; i++)
	{
	printf("%d ",A[i]);	
	}
	printf("\n");
}

double mean_array(const int *A, int n)
{
	//Your code goes here!
	double mean = 0;
	int i;
	for (i = 0; i < n; ++i)
	{
		mean = mean + A[i];
	}
	mean = mean / n;
	return mean;
	
}

double median_array(const int *A, int n)
{
	//Your code goes here!
	 if(n%2==0) {
        // if there is an even number of elements, return mean of the two elements in the middle
        return((A[n/2] + A[n/2 - 1]) / 2.0);
    } else {
        // else return the element in the middle
        return A[n/2];
    }	
    	
}
