#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - Define vector and matrix operations

/**
 * Copies a vector
 * @param vector pointer to a vector
 * @return a cloner version of the vector
 */
int* vcopyres(int *vector)
{
	int * clone = malloc((NRES)*sizeof(int));
    for(int i=0;i<NRES;i++){
        clone[i]=vector[i];
    }
	return clone;
}

int* vcopyproc(int *vector)
{
	int * clone = malloc((NPROC)*sizeof(int));
    for(int i=0;i<NPROC;i++){
        clone[i]=vector[i];
    }
	return clone;
}

/**
 * compares two vectors (checking if the first one always has smaller vals)
 * @param vec1 pointer to the first vector
 * @param vec2 pointer to the second vector
 * @return 0 if there is a problem, or 1 if okay
 */
int vcomp(int* vec1, int* vec2){
	for(int i=0;i<NRES;i++){
        if(vec1[i]>vec2[i]){
			return 0;
		}
    }
	return 1;
}

/**
 * adds two vectors and stores the answer in the first one
 * @param vec1 pointer to the first vector
 * @param vec2 pointer to the second vector
 */
void vadd(int* vec1,int* vec2){
	for(int i=0;i<NRES;i++){
        vec1[i]+=vec2[i];
    }
}

/**
 * subs two vectors and stores the answer in the first one
 * @param vec1 pointer to the first vector
 * @param vec2 pointer to the second vector
 */
void vsub(int* vec1,int* vec2){
	for(int i=0;i<NRES;i++){
        vec1[i]-=vec2[i];
    }
}

/**
 * Prints a given matrix
 * @param matrix pointer to a 2D array
 */
void printM(int **matrix)
{
	int p;
	for	(int i = 0; i < NPROC; i++){
		for (int j = 0; j < NRES; j++){
			p = matrix[i][j];
			printf("[%d]",p);
		}
		printf("\n");	
	}
}

/**
 * Prints a given vector
 * @param vector pointer to a vector
 */
void printV(int *vector)
{
	int p;
	for	(int i = 0; i < NPROC; i++){
		p = vector[i];
		printf("[%d]",p);
	}
	printf("\n");
}
