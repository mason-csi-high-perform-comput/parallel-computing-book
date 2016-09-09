/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2013-6
   %%%%
   %%%% indexed.c : MPI_Type_indexed
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

  if (ntids<2) {
    printf("This program needs at least two processes\n");
    return -1;
  }
  int sender = 0, receiver = 1, the_other = 1-mytid,
    count = 5,totalcount = 15;
  int *source,*target;
  int *displacements,*blocklengths;

  displacements = (int*) malloc(count*sizeof(int));
  blocklengths = (int*) malloc(count*sizeof(int));
  source = (int*) malloc(totalcount*sizeof(int));
  target = (int*) malloc(count*sizeof(int));

  displacements[0] = 2; displacements[1] = 3; displacements[2] = 5;
  displacements[3] = 7; displacements[4] = 11;
  for (int i=0; i<count; ++i)
    blocklengths[i] = 1;
  for (int i=0; i<totalcount; ++i)
    source[i] = i;

  MPI_Datatype newvectortype;
  if (mytid==sender) {
    MPI_Type_indexed(count,blocklengths,displacements,MPI_INT,&newvectortype);
    MPI_Type_commit(&newvectortype);
    MPI_Send(source,1,newvectortype,the_other,0,comm);
    MPI_Type_free(&newvectortype);
  } else if (mytid==receiver) {
    MPI_Status recv_status;
    int recv_count;
    MPI_Recv(target,count,MPI_INT,the_other,0,comm,
      &recv_status);
    MPI_Get_count(&recv_status,MPI_INT,&recv_count);
    ASSERT(recv_count==count);
  }
  
  if (mytid==receiver) {
    int i=3,val=7;
    if (target[i]!=val)
      printf("location %d %d s/b %d\n",i,target[i],val);
    i=4; val=11;
    if (target[i]!=val)
      printf("location %d %d s/b %d\n",i,target[i],val);
  }
  if (mytid==0)
    printf("Finished\n");

  MPI_Finalize();
  return 0;
}