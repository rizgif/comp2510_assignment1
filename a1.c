#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print a line with justified text based on a maximum line length.
void printLine(char *line, int lineLength, int maxLineLength)
{
  int spacesToAdd = maxLineLength - lineLength; // Additional spaces needed for justification
  int spaceCount = 0;                           // Counter for the number of spaces

  // Increments the number of spaces
  for (int i = 0; i < lineLength; i++)
  {
    if (line[i] == ' ')
    {
      spaceCount++;
    }
  }

  if (spaceCount == 0)
  {
    int totalPadding = maxLineLength - lineLength; // Calculate the total padding needed
    int paddingBefore = totalPadding / 2;          // Padding before and after the line

    // If totalPadding is odd, distribute the extra space to paddingBefore
    if (totalPadding % 2 != 0)
    {
      paddingBefore++;
    }
    int paddingAfter = totalPadding - paddingBefore - 1;
    for (int i = 0; i < paddingBefore; i++)
    {
      printf(" ");
    }
    printf("%s", line);
    for (int i = 0; i < paddingAfter; i++)
    {
      printf(" ");
    }
    printf("\n");
  }

  else
  {
    // Line has spaces, handling extraSpaces
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
      }
    }
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
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
        // Calculate the length of the current word
        int wordLength = i - wordStart;

        // If adding the current word to tempLine exceeds the maximum line length, print tempLine
        if (strlen(tempLine) + wordLength > maxLineLength)
        {
            printLine(tempLine, strlen(tempLine) - 1, maxLineLength); // Print the current formatted line
            strcpy(tempLine, "");                                     // Clear the tempLine for the next line
        }

        // Append the current word to tempLine
        strncat(tempLine, &line[wordStart], wordLength); // Copy the word from input to tempLine
        if (line[i] == '-' && line[i+1] != ' ')
        {
            strcat(tempLine, "- "); // Split the compound word into two words with the hyphen
        } 
        else
        {
            strcat(tempLine, " "); // Add a space to separate words
        }
        wordStart = i + 1; // Update the word start position for the next word
    }
}

    printLine(tempLine, strlen(tempLine) - 1, maxLineLength); // Print the last line (if any)
    char *ANum = "A01174802_A00874466_A01357980"; // A numbers of everyone. AXXXX_AXXXX_AXXX format.

        FILE *outputFile = fopen(ANum, "w");

        if (outputFile == NULL)
        {
            printf("Failed to create the output file.\n");
            return 1;
        }

    fclose(outputFile);
    fclose(file); // Close the file after reading
    return 0;
  }
}