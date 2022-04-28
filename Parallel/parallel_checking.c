#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CHARS 26

// typedef struct OccurrenceCheck
// {
//     char character;
//     int occurrence;
// } occurrence_num;

int main(int argc, char **argv)
{
    int rank = 0, size = 0;
    // occurrence_num nums[TOTAL_CHARS];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // for (int i = 0; i < TOTAL_CHARS; i++)
    // {
    //     nums[i].character = (char)('a' + i);
    //     nums[i].occurrence = 0;
    // }
    int chars_occurrences[TOTAL_CHARS];
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    char *string;
    int number_of_characters = 0;

    FILE *file;
    file = fopen("string.txt", "r"); // open the file fname
    if (!file)                       // if open failed
        return -1;
    fscanf(file, "%d\n", &number_of_characters);
    printf("Length of string is: %d\n", number_of_characters);
    string = (char *)malloc(sizeof(char) * number_of_characters);
    fscanf(file, "%[^\n]\n", string);

    // MPI_Bcast(&number_of_characters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Bcast(string, number_of_characters, MPI_CHAR, 0, MPI_COMM_WORLD);

    int num_of_chars_per_processor = number_of_characters / size;

    int low = num_of_chars_per_processor * rank;
    int high = low + num_of_chars_per_processor;

    for (int i = low; i < high; i++)
    {
        int index = (int)string[i] - 'a';
        chars_occurrences[index]++;
        // nums[index].occurrence++;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    printf("Rank %d:\n", rank);
    for (int i = 0; i <= TOTAL_CHARS; i++)
    {
        printf("The char %c is repeated %d times in the string\n", (char) i + 'a', chars_occurrences[i]);
    }

    if (rank == 0)
    {
        double end = MPI_Wtime();
        printf("Execution time: %f\n", end - start);
    }

    MPI_Finalize();
}
