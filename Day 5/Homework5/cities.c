/*
* write a program that get data from uscities.csv,
* and print out the sum of the population of the 20 largest cities,
* and the name of the northernmost city in the file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    
    // strip quotes for normal fields
    if (fieldLength >= 2 && out[0] == '"' && out[fieldLength - 1] == '"') {
        strncpy(out, start + 1, fieldLength - 2);
        out[fieldLength - 2] = '\0';
}
    return sepPointer + 1; // Return a pointer to the character after the separator
}

int main() {
    char s[100];
    char *filename = "uscities.csv"; // Name of the file to read

    FILE *f = fopen(filename, "r"); // Open the file for reading
    if (f == NULL) {
        printf("Could not open the file.\n"); // Print an error message if the file could not be opened
        return 1;
    }
    else {
        char myBuffer[10000]; // Buffer to hold each line read from the file

        fgets(myBuffer, 10000, f); // skip the header line
        
        int keepReading = 1;
        int lineCount = 0; // Counter for the number of lines read

        long populationSum = 0; // Variable to hold the sum of the population of the 20 largest cities
        double maxLatitude = -90.0; // Variable to hold the maximum latitude found
        char northernmostCity[10000]; // Variable to hold the name of the northernmost city

        while (keepReading && lineCount < 20) {
            char *whatWasRead = fgets(myBuffer, 10000, f); // Read a line from the file
            keepReading = (whatWasRead != NULL); // Check if the end of the file has been reached
            
            if (keepReading) {
                killNewline(myBuffer); // Remove the newline character from the end of the line
                lineCount++; // Increment the line counter

                char nextField[10000];
                char cityName[10000];
                long population;
                double latitude;
                int fieldNum = 1; // Index to keep track of which field we are on

                char *p = myBuffer; // Start from the beginning of the line
                while (p != NULL && fieldNum <= 9) {
                    p = getNextField(p, ',', nextField); // Loop through the fields in the line
                    if (p != NULL) {
                        if (fieldNum == 2)
                            strcpy(cityName, nextField); // Store the city name
                        else if (fieldNum == 7)
                            latitude = atof(nextField); // Convert latitude to a double
                        else if (fieldNum == 9)
                            population = atol(nextField); // Convert population to a long integer

                        fieldNum++; // Increment the field index
                }
            }
                populationSum += population; // Add the population to the sum

                if (latitude > maxLatitude) { // Check if this city is more northern than the current northernmost city
                    maxLatitude = latitude; // Update the maximum latitude
                    strcpy(northernmostCity, cityName); // Update the name of the northernmost city
                }
            }
        }

        printf("Sum of the populations: %ld\n", populationSum);
        printf("Northernmost city is %s\n", northernmostCity);

        fclose(f); // Close the file after use
    }
    fgets(s,100,stdin);
}