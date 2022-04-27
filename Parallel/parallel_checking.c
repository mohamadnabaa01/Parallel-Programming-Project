#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

typedef struct occurrence_t{
    int index;
    char character;
    int occurrence;
} CharacterOccurrence;


int main(int argc, char** argv){
    int rank = 0, size = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start, end;
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    FILE *file;
    file = fopen("string.txt", "r"); // open the file fname
    if (!file)                       // if open failed
        return -1;
    int number_of_characters = 0;
    fscanf(file, "%d\n", &number_of_characters);
    printf("Length of string is: %d\n", number_of_characters);
    char string[number_of_characters];
    fscanf(file, "%[^\n]\n", string); // read the contents of the file and put in string
    printf("The string is: %s\n", string);

    int num_of_chars_per_processor = number_of_characters / size;


}

