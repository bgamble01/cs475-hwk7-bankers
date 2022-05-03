#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures
  if(argc>2||argc<2){
		printf("Usage: ./bankers <filename>\n");
		return 0;
	}
  int i;
  int j;
  int check;
  int **max;
  int **alloc;
  int *avail;

  FILE *fp =fopen(argv[1],"r");
  if (fp == NULL){
    perror("Error opening file ");
    return 0;
  }

  fscanf(fp, "%d", &NRES);
  fscanf(fp, "%d", &NPROC);
  
  /* printf("%d\n", NRES);
  printf("%d\n", NPROC);
  printf("\n"); */
	max = (int**)malloc((NPROC)*sizeof(int*));
	for(i=0;i<NPROC;i++){
		max[i]=(int*)malloc((NRES)*sizeof(int));
	}
	
  alloc = (int**)malloc((NPROC)*sizeof(int*));
	for(i=0;i<NPROC;i++){
		alloc[i]=(int*)malloc((NRES)*sizeof(int));
	}

  avail = malloc((NRES)*sizeof(int));
  
  //reading in available
  for(i=0;i<NRES;i++){
    fscanf(fp,"%d",&avail[i]);
  }

  //reading in max
  for(i=0;i<NPROC;i++){
    for(j=0;j<NRES;j++){
      fscanf(fp,"%d",&max[i][j]);
    }
  }

  //reading in allocated
  for(i=0;i<NPROC;i++){
    for(j=0;j<NRES;j++){
      fscanf(fp,"%d",&alloc[i][j]);
    }
  }
  
  //sanity check 1
  int *temp = malloc((NRES)*sizeof(int));
  for(i=0;i<NPROC;i++){
    vadd(temp,alloc[i]);
  }
  check = vcomp(temp,avail);
  if(check==0){
    for	(i = 0; i < NRES; i++){
		  free(max[i]);
	  }
	  free(max);
	  for	(i = 0; i < NRES; i++){
		  free(alloc[i]);
	  }
    free(alloc);
    free(avail);
    free(temp);
    printf("Integrity test failed: allocated resources exceed total resources\n");
    return 0;
  }

  vsub(avail,temp);

  
  //sanity check 2
  for(i=0;i<NPROC;i++){
    check = vcomp(alloc[i],max[i]);
    if (check ==0){
      for	(i = 0; i < NRES; i++){
		    free(max[i]);
	    }
	    free(max);
	    for	(i = 0; i < NRES; i++){
		    free(alloc[i]);
	    }
      free(alloc);
      free(avail);
      free(temp);
      printf("Integrity test failed: allocated resources exceed demands\n");
      return 0;
    }
  }
  // TODO: Run banker's safety algorithm
  int ** need = (int**)malloc((NPROC)*sizeof(int*));
	for(i=0;i<NPROC;i++){
		need[i]=(int*)malloc((NRES)*sizeof(int));
	}

  for(i=0;i<NPROC;i++){
    for(j=0;j<NRES;j++){
      need[i][j]=(max[i][j]) - (alloc[i][j]);
    }
  }

  int *ans = malloc((NPROC)*sizeof(int));
  int *f = malloc((NPROC)*sizeof(int));


 /*  printV(avail);
  printf("\n");
  printM(max);
  printf("\n");
  printM(alloc); 
  printf("\n");
  printM(need);

 */
  int uns = safety(avail,alloc,need,f,ans,0);
  if(uns==0){
    printf("System is unsafe! Some threads can't finish\n");
  }
  
  //free mem
	for	(i = 0; i < NRES; i++){
		free(max[i]);
    free(alloc[i]);
    free(need[i]);
	}
	free(max);
  free(need);
  free(alloc);
  free(avail);
  free(temp);
  free(ans);
  free(f);
  return 0;
}
