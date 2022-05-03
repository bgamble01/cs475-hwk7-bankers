#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here
int safety(int*avail,int**alloc,int**need,int*f,int*ans,int depth){
    int i;
    int path=0;
    if(depth==NPROC){
        printf("SAFE: ");
        for(int j=0;j<NPROC;j++){
            printf("T%d ",ans[j]);
        }
        printf("\n");
        return 1;
    }
    for(i=0;i<NPROC;i++){
        if(f[i]==1){
        }
        else{
            if(vcomp(need[i],avail)==1){
                int * work= vcopyres(avail);
                int * prog = vcopyproc(f);
                int * order = vcopyproc(ans);

                vadd(work,alloc[i]);
                prog[i]=1;
                order[depth]=i;

                path =safety(work,alloc,need,prog,order,depth+1);
                free(work);
                free(prog);
                free(order);
            }
        }
    }
    if (path == 0){
        return 0;
    }
    else{
        return 1;
    }
}
