#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printLine(char* line, int lineLength, int maxLineLength) {
    int spacesToAdd = maxLineLength - lineLength;
    int spaceCount = 0;

    for (int i = 0; i < lineLength; i++) {
        if (line[i] == ' ') {
            spaceCount++;
        }
    }

    if (spaceCount == 0) {
        int padding = (maxLineLength - lineLength) / 2;
        // Adjust the padding for centering single words
        if ((maxLineLength - lineLength) % 2 != 0) {
            padding++;
        }
        for (int i = 0; i < padding; i++) {
            printf(" ");
        }
        printf("%s\n", line);
    } else {
        int wordStart = 0;
        int extraSpaces = spacesToAdd % spaceCount;
        int spacesPerGap = spacesToAdd / spaceCount;

        for (int i = 0; i < lineLength; i++) {
            printf("%c", line[i]);
            if (line[i] == ' ') {
                for (int j = 0; j < spacesPerGap; j++) {
                    printf(" ");
                }
                if (extraSpaces > 0) {
                    printf(" ");
                    extraSpaces--;
                }
                wordStart = i + 1;
            }
        }
        printf("\n");
    }
}

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

    char line[1024];
    while(fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        int wordStart = 0;
        int lineLength = strlen(line);
        for(int i = 0; i <= lineLength; i++) {
            if(line[i] == ' ' || line[i] == '\0') {
                int wordLength = i - wordStart;
                if(wordLength > maxLineLength) {
                    printf("Error. The word processor can’t display the output.\n");
                    fclose(file);
                    return 3;
                }
                wordStart = i + 1;
            }
        }

        char tempLine[1024] = "";
        wordStart = 0;
        for(int i = 0; i <= lineLength; i++) {
            if(line[i] == ' ' || line[i] == '\0' || line[i] == '-') {
                int wordLength = i - wordStart + (line[i] == '-' ? 1 : 0);

                if(strlen(tempLine) + wordLength + (line[i] == '-' ? 1 : 0) > maxLineLength) {
                    printLine(tempLine, strlen(tempLine) - 1, maxLineLength);
                    strcpy(tempLine, "");
                }

                strncat(tempLine, &line[wordStart], wordLength);
                if(line[i] == '-') {
                    strcat(tempLine, "-");
                } else {
                    strcat(tempLine, " ");
                }
                wordStart = i + 1;
            }
        }
        printLine(tempLine, strlen(tempLine) - 1, maxLineLength);
    }

    fclose(file);
    return 0;
}


