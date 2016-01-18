/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2013-6
   %%%%
   %%%% allreduce.c
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc,char **argv) {

#include "globalinit.c"

  //snippet allreducec
  float myrandom,sumrandom;
  myrandom = (float) rand()/(float)RAND_MAX;
  // add the random variables together
  MPI_Allreduce(&myrandom,&sumrandom,
  		1,MPI_FLOAT,MPI_SUM,comm);
  // the result should be approx ntids/2:
  if (mytid==ntids-1)
    printf("Result %6.9f compared to .5\n",sumrandom/ntids);
  //snippet end

  MPI_Finalize();
  return 0;
}
