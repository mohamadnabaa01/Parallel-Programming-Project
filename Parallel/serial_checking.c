#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 26
#define LENGTH 100
int main(void) {
    FILE *file;
    file = fopen("string.txt", "r");//open the file fname
    if(!file)//if open failed
        return -1;
    char string[256];
    fscanf(file, "%[^\n]\n", string);//read the contents of the file and put in string
    
    char  check_occurences[SIZE];
    for(int i=0;i<SIZE;i++){
        check_occurences[i]=0;
    }

    printf("%d", string);
    return 0;
}

int getRandromNumber(){
    int num = rand() % (90-65) + 65;
    return num; 
}

