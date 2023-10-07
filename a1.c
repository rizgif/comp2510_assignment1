#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
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
    
    char line[1000]; // assuming a line won't be longer than 1000 characters
    while(fgets(line, sizeof(line), file)) {
        printf("%s", line); // print each line of the file
    }
    
    printf("\n"); // Add a newline character at the end of the output
    
    fclose(file);
    return 0;
}
