#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CHARS 26

typedef struct OccurrenceCheck
{
    char character;
    int occurrence;
} occurrence_num;

int main(int argc, char **argv)
{
    int rank = 0, size = 0;
    occurrence_num nums[TOTAL_CHARS];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < TOTAL_CHARS; i++)
    {
        nums[i].character = (char)('a' + i);
        nums[i].occurrence = 0;
    }
    char *string;
    int number_of_characters = 0;

    if (rank == 0)
    {
        FILE *file;
        file = fopen("string.txt", "r"); // open the file fname
        if (!file)                       // if open failed
            return -1;
        fscanf(file, "%d\n", &number_of_characters);
        printf("Length of string is: %d\n", number_of_characters);
        string = (char *)malloc(sizeof(char) * number_of_characters);
        fscanf(file, "%[^\n]\n", string);
    }

    double start, end;
    printf("Before barrier rank %d\n\n", rank);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("After barrier rank %d\n", rank);
    start = MPI_Wtime();

    // MPI_Bcast(&number_of_characters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Bcast(string, number_of_characters, MPI_CHAR, 0, MPI_COMM_WORLD);

    // int num_of_chars_per_processor = number_of_characters / size;

    // // MPI_Scatter(string, number_of_characters, MPI_CHAR, received_chars_per_processor, num_of_chars_per_processor, MPI_CHAR, 0, MPI_COMM_WORLD);

    // int low = num_of_chars_per_processor * rank;
    // int high = low + num_of_chars_per_processor - 1;

    // for (int i = low; i <= high; i++)
    // {
    //     int index = (int)string[i] - 'a';
    //     nums[index].occurrence+=1;
    // }


    // MPI_Barrier(MPI_COMM_WORLD);
    // if (rank == 0)
    // {
    //     for (int i = 0; i <= TOTAL_CHARS; i++)
    //     {
    //         printf("The char %c is repeated %d times in the string\n", nums[i].character, nums[i].occurrence);
    //     }
    // }
    // end = MPI_Wtime();

    // if (rank == 0)
    // {
    //     printf("Execution time: %f\n", end - start);
    // }
    MPI_Finalize();
}
