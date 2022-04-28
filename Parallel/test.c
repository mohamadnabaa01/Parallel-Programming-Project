#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/************************************************** DO NOT MODIFY START! **************************************************/
#define NUM_FILES 60

//IMPORTANT: run ./gen.sh to generate the large input files!
static char * files[NUM_FILES] = {
  "input/small/1KB.1.txt",    "input/small/1KB.2.txt",    "input/small/1KB.3.txt",    "input/small/1KB.4.txt",
  "input/small/1KB.5.txt",    "input/small/1KB.6.txt",    "input/small/1KB.7.txt",    "input/small/1KB.8.txt",
  "input/small/10KB.1.txt",   "input/small/10KB.2.txt",   "input/small/10KB.3.txt",   "input/small/10KB.4.txt",
  "input/small/10KB.5.txt",   "input/small/10KB.6.txt",   "input/small/10KB.7.txt",   "input/small/10KB.8.txt",
  "input/small/100KB.1.txt",  "input/small/100KB.2.txt",   "input/small/100KB.3.txt",  "input/small/100KB.4.txt",
  "input/small/100KB.5.txt",  "input/small/100KB.6.txt",  "input/small/100KB.7.txt",  "input/small/100KB.8.txt",
  "input/large/1MB.1.txt",    "input/large/1MB.2.txt",    "input/large/1MB.3.txt",    "input/large/1MB.4.txt",
  "input/large/10MB.1.txt",   "input/large/10MB.2.txt",   "input/large/10MB.3.txt",   "input/large/10MB.4.txt",
  "input/large/10MB.5.txt",   "input/large/10MB.6.txt",   "input/large/10MB.7.txt",   "input/large/10MB.8.txt",
  "input/large/50MB.1.txt",   "input/large/50MB.2.txt",   "input/large/50MB.3.txt",   "input/large/50MB.4.txt",
  "input/large/50MB.5.txt",   "input/large/50MB.6.txt",   "input/large/50MB.7.txt",   "input/large/50MB.8.txt",
  "input/large/100MB.1.txt",   "input/large/100MB.2.txt",   "input/large/100MB.3.txt",   "input/large/100MB.4.txt",
  "input/large/100MB.5.txt",   "input/large/100MB.6.txt",   "input/large/100MB.7.txt",   "input/large/100MB.8.txt",
  "input/large/500MB.1.txt",   "input/large/500MB.2.txt",   "input/large/500MB.3.txt",   "input/large/500MB.4.txt",
  "input/large/500MB.5.txt",   "input/large/500MB.6.txt",   "input/large/500MB.7.txt",   "input/large/500MB.8.txt",
};

static int checksums[NUM_FILES] = { -1 };

void print_checksums() {
  for(int i=0; i<NUM_FILES; i++)
    printf("%s: %d\n", files[i], checksums[i]);
}

/************************************************** DO NOT MODIFY END! **************************************************/

int checksum(const char * fname) {
  int c; long checksum = 0;
  
  FILE *file;
  file = fopen(fname, "r");
  while ((c = fgetc(file)) != EOF) {
    checksum += c;
  }
  fclose(file);
  if(checksum > 0) return checksum % 255;
  return 0;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  MPI_Barrier(MPI_COMM_WORLD);
  double start_time = MPI_Wtime();
  
  int files_per_proc = NUM_FILES / world_size;
  int files_per_proc_remainder = NUM_FILES % world_size;
  
  int low = files_per_proc * rank;
  if(rank != 0)
    low += files_per_proc_remainder;

  int high = low + files_per_proc;
  if(rank == 0)
    high += files_per_proc_remainder;

  for(int i=low; i<high; i++)
    checksums[i] = checksum(files[i]);

  MPI_Gather(checksums + low, high-low, MPI_INT, checksums, high-low, MPI_INT, 0, MPI_COMM_WORLD);
  double end_time = MPI_Wtime();

  if(rank == 0) {
    print_checksums();
    printf("Total time: %fs\n",end_time-start_time);
  }
  
  MPI_Finalize();
}