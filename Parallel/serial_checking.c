#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 26
#define LENGTH 100
int main(void)
{
    FILE *file;
    file = fopen("string.txt", "r"); // open the file fname
    if (!file)                       // if open failed
        return -1;
    int string_length = 0;
    fscanf(file, "%d", &string_length);
    printf("Length of string is: %d", string_length);
    char string[string_length];
    fscanf(file, "%[^\n]\n", string); // read the contents of the file and put in string
    printf("The string is: %s", string);

    int check_occurences[SIZE];
    for (int i = 0; i < SIZE; i++)
        check_occurences[i] = 0;

    for (int i = 0; i < string_length; i++)
        check_occurences[string[i] - 'a']++;

    for (int i = 0; i < SIZE; i++)
        if (check_occurences[i] != 0)
            printf("The char %c is repeated %d times in the string", ((char)(i + 'a')), check_occurences[i]);

    return 0;
}
