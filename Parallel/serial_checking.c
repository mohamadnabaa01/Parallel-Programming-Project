#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 26
#define LENGTH 100
int main(void) {
    char  check_occurences[SIZE];
    for(int i=0;i<SIZE;i++){
        check_occurences[i]=0;
    }
    char characters[LENGTH];
    for(int i = 0; i<LENGTH; i++)
        characters[i] = getRandomCharacter();

    char* s = (char*) malloc(sizeof(char)*LENGTH);
    for(int i = 0; i<LENGTH; i++){
        s[i] = characters[i];
    }
    printf("%d", s);
    
    return 0;
}

char getRandromCharacter(){
    char c = (char) rand() % (90-65) + 65;
    return c; 
}

