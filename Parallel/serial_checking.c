#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define SIZE 26
#define LENGTH 100
int main(void)
{
    FILE *file;
    file = fopen("string.txt", "r"); // open the file fname
    if (!file)                       // if open failed
        return -1;
    double start_time, end_time;
    int string_length = 0;
    fscanf(file, "%d\n", &string_length);
    printf("Length of string is: %d\n", string_length);
    char string[string_length + 1];
    fscanf(file, "%[^\n]\n", string); // read the contents of the file and put in string
    printf("The string is: %s\n", string);

    start_time = clock();

    int check_occurences[SIZE];
    for (int i = 0; i < SIZE; i++)
        check_occurences[i] = 0;

    for (int i = 0; i < string_length; i++)
        check_occurences[string[i] - 'a']++;

    for (int i = 0; i < SIZE; i++)
        if (check_occurences[i] != 0)
            printf("The char %c is repeated %d times in the string\n", ((char)(i + 'a')), check_occurences[i]);

    end_time = clock();

    printf("Time complexity: %d", start_time - end_time);
    return 0;
}
