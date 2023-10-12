#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getNextToken(char **str) {
    while (**str == ' ') {
        (*str)++;
    }

    if (**str == '\0') {
        return NULL;
    }

    char *start = *str;

    while (**str != '\0' && **str != ' ') {
        (*str)++;
    }

    char *token = (char*)malloc((*str - start + 1) * sizeof(char));
    strncpy(token, start, *str - start);
    token[*str - start] = '\0';
    if (**str != '\0') {
        (*str)++;
    }

    return token;
}

void printLine(char *line, int maxLineLength) {
    int lineLength = strlen(line);
    if (line[lineLength - 1] == ' ') {
        line[lineLength - 1] = '\0';
        lineLength--;
    }

    if (strchr(line, ' ') == NULL) {
        int padding = (maxLineLength - lineLength) / 2;
        int extraSpace = (maxLineLength - lineLength) % 2;
        for (int i = 0; i < padding + extraSpace; i++) printf(" ");
        printf("%s\n", line);
        return;
    }

    int spacesToAdd = maxLineLength - lineLength;
    int spaceCount = 0;
    for (int i = 0; i < lineLength; i++) {
        if (line[i] == ' ') spaceCount++;
    }
    int extraSpaces = spacesToAdd % spaceCount;
    int spacesPerGap = spacesToAdd / spaceCount;

    for (int i = 0; i < lineLength; i++) {
        printf("%c", line[i]);
        if (line[i] == ' ') {
            for (int j = 0; j < spacesPerGap; j++) printf(" ");
            if (extraSpaces > 0) {
                printf(" ");
                extraSpaces--;
            }
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <lineLength> <filename>\n", argv[0]);
        return 1;
    }

    int maxLineLength = atoi(argv[1]);
    FILE *file = fopen(argv[2], "r");
    if (!file) {
        perror("Error opening file");
        return 2;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char tempLine[1024] = "";
        char *cursor = line;
        char *token = getNextToken(&cursor);

        while (token) {
            char *hyphenPos = strchr(token, '-');
            if (hyphenPos) {
                *hyphenPos = '\0';
                char *firstPart = token;
                char *secondPart = hyphenPos + 1;
                strcat(tempLine, firstPart);
                strcat(tempLine, "- ");
                printLine(tempLine, maxLineLength);
                strcpy(tempLine, secondPart);
                strcat(tempLine, " ");
            } else {
                int prospectiveLength = strlen(tempLine) + strlen(token) + 1;
                if (prospectiveLength > maxLineLength) {
                    tempLine[strlen(tempLine) - 1] = '\0';  // Remove trailing space
                    printLine(tempLine, maxLineLength);
                    strcpy(tempLine, "");
                }
                strcat(tempLine, token);
                strcat(tempLine, " ");
            }
            token = getNextToken(&cursor);
        }

        if (strlen(tempLine) > 0) {
            printLine(tempLine, maxLineLength);
        }
    }
    char *ANum = "A01174802_A00874466_A01357980"; // A numbers of everyone. AXXXX_AXXXX_AXXX format.

        FILE *outputFile = fopen(ANum, "w");

        if (outputFile == NULL)
        {
            printf("Failed to create the output file.\n");
            return 1;
        }

    fclose(outputFile);
    fclose(file);
    return 0;
}