#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Text Justification and Output Formatting
void printLine(char* line, int lineLength, int maxLineLength) {
 
}

int main(int argc, char* argv[]) {

    //File I/O and Command Line Argument Parsing

    if(argc != 3) {
        printf("Usage: %s <lineLength> <filename>\n", argv[0]);
        return 1;
    }
    
    int maxLineLength = atoi(argv[1]);
    char* filename = argv[2];
    
    FILE* file = fopen(filename, "r");
    if(!file) {
        perror("Error opening file");
        return 2;
    }

    //Text Processing and Word Wrapping




    fclose(file);
    return 0;
}

