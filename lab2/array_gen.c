#include <stdio.h>
#include <limits.h>
#include <stdlib.h> /* srand */
#include <time.h>

int main(int argc, char* argv[]){

	unsigned long size;
	FILE* fp;
	unsigned long bound = INT_MAX;

	srand(time(NULL));

	if(argc != 3 && argc != 4){
		fprintf(stderr, "Usage: array_gen number_of_integers name_of_the_file [upper bound]\n");
		return 1;
	}

	char* tmp;
	size = strtoul(argv[1], &tmp, 0);
	if(*tmp != '\0'){
		fprintf(stderr, "Please enter a valid size\n");
		return 1;
	}

	fp = fopen(argv[2], "w");
	if(fp == NULL){
		fprintf(stderr, "File open error\n");
		return 1;
	}

	if(argc == 4){
		bound = strtoul(argv[3], &tmp, 0);
		if(*tmp != '\0'){
			fprintf(stderr, "Please enter a valid bound\n");
			return 1;
		}
	}

	int i;	
	for(i = 0 ; i < size ; i++){
		fprintf(fp, "%ld\n", rand() % bound);
	}

	fclose(fp);
	return 0;
}
