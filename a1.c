#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print a line with justified text based on a maximum line length.
void printLine(char* line, int lineLength, int maxLineLength) {
    int spacesToAdd = maxLineLength - lineLength;  // Additional spaces needed for justification
    int spaceIndexes[20];  // Indexes of spaces within the line
    int spaceCount = 0;  // Counter for the number of spaces
    int hyphenCount = 0; // Counter for the number of hyphens

    for (int i = 0; i < lineLength; i++) {
        if (line[i] == ' ') {
            spaceCount++;
        } else if (line[i] == '-') {
            hyphenCount++;
        }
    }
    
    // If the line has no spaces, center it
    if(spaceCount == 0) { 
        int padding = (maxLineLength - lineLength) / 2;  // Calculate how much padding is needed
        for(int i = 0; i < padding; i++) {
            printf(" ");
        }
        printf("%s\n", line);
    } else {
      // Line has spaces, handling extraSpaces
        int wordStart = 0;
        int extraSpaces = spacesToAdd % (spaceCount - hyphenCount);
        int spacesPerGap = spacesToAdd / (spaceCount - hyphenCount);

        for (int i = 0; i < lineLength; i++) {
            printf("%c", line[i]);
            if (line[i] == ' ') {
              for (int j = 0; j < spacesPerGap; j++) {
                  printf(" ");
              }
              // Distribute remaining extra spaces if there are any
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
    // Validate number of command-line arguments
    if(argc != 3) {
        printf("Usage: %s <lineLength> <filename>\n", argv[0]);
        return 1;
    }
    
    int maxLineLength = atoi(argv[1]);  // Maximum allowed line length
    char* filename = argv[2];
    
    FILE* file = fopen(filename, "r");  // Open the file for reading
    if(!file) {
        perror("Error opening file");
        return 2;
    }
    
    char line[1024];
    while(fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;  // Remove newline character from the line

        // Validation: Ensure no word in the line exceeds maxLineLength
        int wordStart = 0;
        int lineLength = strlen(line);
        for(int i = 0; i <= lineLength; i++) {
            if(line[i] == ' ' || line[i] == '\0') {
                int wordLength = i - wordStart;
                if(wordLength > maxLineLength) {
                    printf("Error. The word processor can’t display the output.\n");
                    fclose(file);
                    return 3;  // Return a unique error code
                }
                wordStart = i + 1;
            }
        }

        // Construct justified lines from the input line
        char tempLine[1024] = "";
        wordStart = 0;
        for(int i = 0; i <= lineLength; i++) {
            if(line[i] == ' ' || line[i] == '\0') {
                int wordLength = i - wordStart;

                // If adding the word to tempLine exceeds maxLineLength, print tempLine
                if(strlen(tempLine) + wordLength > maxLineLength) {
                    printLine(tempLine, strlen(tempLine) - 1, maxLineLength); 
                    strcpy(tempLine, "");
                }

                // Append the word to tempLine
                strncat(tempLine, &line[wordStart], wordLength);
                strcat(tempLine, " ");
                wordStart = i + 1; 
            }
        }
        printLine(tempLine, strlen(tempLine) - 1, maxLineLength); 
    }
    
    fclose(file);  // Close the file after reading
    return 0;
}