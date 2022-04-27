#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <string.h>

#define TOTAL_CHARS 26

typedef struct OccurrenceCheck
{
    char character;
    int occurrence;
} occurrence_num;

occurrence_num nums[TOTAL_CHARS];

int main(int argc, char **argv)
{
    int rank = 0, size = 0;
    int number_of_characters = 0;
    char *string;
    int all_characters_checked = 0;
    for (int i = 0; i < TOTAL_CHARS; i++)
    {
        nums[i].character = (char)('a' + i);
        nums[i].occurrence = 0;
    }

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
    string = (char *)malloc(sizeof(char) * number_of_characters);
    fscanf(file, "%[^\n]\n", string);

    MPI_Bcast(string, number_of_characters, MPI_CHAR, 0, MPI_COMM_WORLD);

    int num_of_chars_per_processor = number_of_characters / size;

    // MPI_Scatter(string, number_of_characters, MPI_CHAR, received_chars_per_processor, num_of_chars_per_processor, MPI_CHAR, 0, MPI_COMM_WORLD);

    int low = num_of_chars_per_processor * rank;
    int high = low + num_of_chars_per_processor - 1;

    for (int i = low; i <= high; i++)
    {
        int index = (int)string[i] - 'a';
        nums[index].occurrence++;
        all_characters_checked++;
        printf("%d\n", all_characters_checked);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (all_characters_checked == number_of_characters)
    {
        printf("%d\n", all_characters_checked);
        for (int i = 0; i <= TOTAL_CHARS; i++)
        {
            printf("The char %c is repeated %d times in the string\n", nums[i].character, nums[i].occurrence);
        }
    }
    end = MPI_Wtime();

    printf("Execution time: %f\n", end - start);
    MPI_Finalize();
}
