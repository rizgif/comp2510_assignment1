#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print a line with justified text based on a maximum line length.
void printLine(char *line, int lineLength, int maxLineLength)
{
    int spacesToAdd = maxLineLength - lineLength; // Additional spaces needed for justification
    int spaceIndexes[20];                         // Indexes of spaces within the line
    int spaceCount = 0;                           // Counter for the number of spaces

    // Increments the number of spaces
    for (int i = 0; i < lineLength; i++)
    {
        if (line[i] == ' ')
        {
            spaceCount++;
        }
    }

    // If the line has no spaces, center it
    if (spaceCount == 0)
    {
        int padding = (maxLineLength - lineLength) / 2; // Calculate how much padding is needed

        // Padding for centering a word
        if ((maxLineLength - lineLength) % 2 != 0)
        {
            padding++;
        }
        for (int i = 0; i < padding; i++)
        {
            printf(" ");
        }
        printf("%s\n", line);
    }
    else
    {
        // Line has spaces, handling extraSpaces
        int wordStart = 0;
        int extraSpaces = spacesToAdd % spaceCount;
        int spacesPerGap = spacesToAdd / spaceCount;

        for (int i = 0; i < lineLength; i++)
        {
            printf("%c", line[i]);
            if (line[i] == ' ')
            {
                for (int j = 0; j < spacesPerGap; j++)
                {
                    printf(" ");
                }
                // Distribute remaining extra spaces if there are any
                if (extraSpaces > 0)
                {
                    printf(" ");
                    extraSpaces--;
                }
                wordStart = i + 1;
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    // Validate number of command-line arguments
    if (argc != 3)
    {
        printf("Usage: %s <lineLength> <filename>\n", argv[0]);
        return 1;
    }

    int maxLineLength = atoi(argv[1]); // Maximum allowed line length
    char *filename = argv[2];

    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (!file)
    {
        perror("Error opening file");
        return 2;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0; // Remove newline character from the line

        // Validation: Ensure no word in the line exceeds maxLineLength
        int wordStart = 0;
        int lineLength = strlen(line);
        for (int i = 0; i <= lineLength; i++)
        {
            if (line[i] == ' ' || line[i] == '\0')
            {
                int wordLength = i - wordStart;
                if (wordLength > maxLineLength)
                {
                    printf("Error. The word processor can’t display the output.\n");
                    fclose(file);
                    return 3; // Return a unique error code
                }
                wordStart = i + 1;
            }
        }

        // Construct justified lines from the input line
        char tempLine[1024] = ""; // Initialize a temporary line to store formatted text
        wordStart = 0;            // Initialize the word start position

        // Loop through the characters in the input line
        for (int i = 0; i <= lineLength; i++)
        {
            if (line[i] == ' ' || line[i] == '\0' || line[i] == '-')
            {
                // Calculate the length of the current word, including the hyphen (if present)
                int wordLength = i - wordStart + (line[i] == '-' ? 1 : 0);

                // If adding the current word to tempLine exceeds the maximum line length, print tempLine
                if (strlen(tempLine) + wordLength + (line[i] == '-' ? 1 : 0) > maxLineLength)
                {
                    printLine(tempLine, strlen(tempLine) - 1, maxLineLength); // Print the current formatted line
                    strcpy(tempLine, "");                                     // Clear the tempLine for the next line
                }

                // Append the current word to tempLine
                strncat(tempLine, &line[wordStart], wordLength); // Copy the word from input to tempLine
                if (line[i] == '-')
                {
                    strcat(tempLine, "-"); // Add a hyphen if the word ended with a hyphen
                }
                else
                {
                    strcat(tempLine, " "); // Add a space to separate words
                }
                wordStart = i + 1; // Update the word start position for the next word
            }
        }

        printLine(tempLine, strlen(tempLine) - 1, maxLineLength); // Print the last line (if any)

        fclose(file); // Close the file after reading
        return 0;
    }
}