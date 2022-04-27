#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <string.h>

typedef struct OccurrenceCheck
{
    char character;
    int occurrence;
} occurrence_num;

occurrence_num nums[26];

int main(int argc, char **argv)
{
    int rank = 0, size = 0;
    int number_of_characters = 0;

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
    fscanf(file, "%d\n", &number_of_characters);
    printf("Length of string is: %d\n", number_of_characters);
    for (int i = 0; i < 26; i++)
    {
        nums[i].character = (char)('a' + i);
        nums[i].occurrence = 0;
    }
    char* string = (char*) malloc(sizeof(char) * number_of_characters);
    fscanf(file, "%[^\n]\n", string); // read the contents of the file and put in string

    int num_of_chars_per_processor = number_of_characters / size;

    char *received_chars_per_processor = (char*)malloc(sizeof(char) * num_of_chars_per_processor);

    // MPI_Scatter(string, number_of_characters, MPI_CHAR, received_chars_per_processor, num_of_chars_per_processor, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Bcast(string, number_of_characters, MPI_CHAR, 0, MPI_COMM_WORLD);

    // printf("I am rank %d and i have: %s\n", rank, string);
    int low = num_of_chars_per_processor * rank;
    int high = low + num_of_chars_per_processor- 1;

    // printf("%d %d", low, high);

    for (int i = low; i <= high; i++)
    {
      int index =  ((int)received_chars_per_processor[i] - (int)'a');
        printf("jhhh");
       // nums[index].occurrence++;
        printf("%d", index);
    }

    // if (rank == size - 1)
    // {
    //     for (int i = 0; i < 26; i++)
    //     {
    //         printf("The char %c is repeated %d times in the string\n", nums[i].character, nums[i].occurrence);
    //     }
    // }

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    // printf("Execution time: %f", end - start);
    MPI_Finalize();
}
