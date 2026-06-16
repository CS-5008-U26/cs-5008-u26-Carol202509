/*
* write a program that reads a csv file and prints out the fields in each line.
*/

#include <stdio.h>
#include <string.h>

void killNewline (char *str) {
    if (strlen(str) > 1 && (str[strlen(str) - 1]) == '\n') {
        str[strlen(str) - 1] = '\0'; // Remove the newline character from the end of the string
    }
}

char *getNextField (char *start, char separator, char *out) {
    // special case: no more fields to read
    if (*start == '\0') {
        return NULL;
    }

    // find the next separator
    char *sepPointer = strchr(start, separator);

    // if there is no separator, then the field goes to the end of the string
    if (sepPointer == NULL) {
        int fieldLength = strlen(start);

        // If the field is enclosed in double quotes, copy only the inside.
        if (fieldLength >= 2 && start[0] == '"' && start[fieldLength - 1] == '"') {
            strncpy(out, start + 1, fieldLength - 2);
            out[fieldLength - 2] = '\0';
        } else {
            strcpy(out, start); // Copy the remaining string to the output
        }
        
        return start + strlen(start); // Return a pointer to the end of the string
   }
   
   int fieldLength = sepPointer - start; //how many chars to copy
   strncpy(out, start, fieldLength); // copy the chars to the output
   out[fieldLength] = '\0'; // add terminator to the output string
   return sepPointer + 1; // Return a pointer to the character after the separator
}

int main() {
    char s[100];
    char buffer[1000];
    printf("Enter the file name: "); // Prompt the user for the file name
    fgets(buffer, 1000,stdin); // Read the file name from the user
    killNewline(buffer); // Remove the newline character from the end of the file name
    printf("%s\n", buffer); // Print the file name without the newline character

    FILE *inFile = fopen(buffer, "r"); // Open the file for reading
    if (inFile == NULL) {
        printf("Could not open the file.\n"); // Print an error message if the file could not be opened
        return 1;
    }
    else {
        int keepReading = 1;
        char myBuffer[1000]; // Buffer to hold each line read from the file

        while (keepReading) {
            char *whatWasRead = fgets(myBuffer, 1000, inFile); // Read a line from the file
            keepReading = (whatWasRead != NULL); // Check if the end of the file has been reached
            if (keepReading) {
                killNewline(myBuffer); // Remove the newline character from the end of the line
                printf(">%s<\n", myBuffer); // Print the whole line first

                char nextField[1000];
                char *p = myBuffer; // Start from the beginning of the line

                while (p != NULL) {
                    p = getNextField(p, ',', nextField); // Loop through the fields in the line
                    if (p != NULL) {
                        printf("  >%s<\n", nextField); // Print each field
                    }
                }
            }
        }

        fclose(inFile); // Close the file after use
    }
    fgets(s,100,stdin);
}