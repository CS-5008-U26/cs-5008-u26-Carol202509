/*
* write a program that reads in the largest cities from uscities.csv,
* and finds out the set of cities with the largest populations, whose names add up to 200 characters or less.
* Print the total population and the names of the cities in that set.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CITIES 200
#define MAX_NAME_LENGTH 200

// Define a structure to hold city information
typedef struct city_struct {
    char* name;
    long long population;
    int nameLength;
} city;

void killNewline (char* str) {
    if (strlen(str) > 1 && (str[strlen(str) - 1]) == '\n') {
        str[strlen(str) - 1] = '\0'; // Remove the newline character from the end of the string
    }
}

char* getNextField (char* start, char separator, char* out) {
    // special case: no more fields to read
    if (*start == '\0') {
        return NULL;
    }
    // find the next separator
    char* sepPointer = strchr(start, separator);
    
    int fieldLength;
    char* nextStart;
    
    if (sepPointer == NULL) { // No more separators found, field goes to the end of the string
        fieldLength = strlen(start);
        nextStart = start + fieldLength;
    }
    else { // Separator found, field goes up to the separator
        fieldLength = sepPointer - start;
        nextStart = sepPointer + 1;
    }

    // If the field is enclosed in double quotes, copy only the inside.
    if (fieldLength >= 2 && start[0] == '"' && start[fieldLength - 1] == '"') {
        strncpy(out, start + 1, fieldLength - 2);
        out[fieldLength - 2] = '\0';
    } else {
        strncpy(out, start, fieldLength);
        out[fieldLength] = '\0';
    }
        
        return nextStart; // Return a pointer to the character after the separator
   }

city *stringToCity(char* textLine) {
    char fieldBuffer[1000];
    int fieldNum = 1;
    char* p = textLine;

    city* c = malloc(sizeof(city));
    if (c == NULL) {
        return NULL;
    }

    while (p != NULL && fieldNum <= 9) {
        p = getNextField(p, ',', fieldBuffer);

        if (p == NULL) {
            break;
        }

        switch (fieldNum) {
            case 1:
                c->name = strdup(fieldBuffer); // Store the city name

                if (c->name == NULL) {
                    free(c); // Free the city structure if memory allocation fails
                    return NULL;
                }

                c->nameLength = strlen(c->name); // Store the length of the city name
                break;
            case 9:
                c->population = atoll(fieldBuffer); // Convert population to an integer and store it
                break;
        }
            
        fieldNum++; // Increment the field index
    }
    
    return c; // Return the pointer to the city structure
}

// Free the memory allocated for a city structure
void freeCity(city* c) {
    if (c == NULL) {
        return;
    }
    free(c->name);
    free(c); // Free the city structure itself
    }

int main() {
    char s[100];

    //open the file for reading
    FILE *File = fopen("../../Resources/uscities.csv", "r");
    if (File == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    city* cities[MAX_CITIES];
    int cityCount = 0;

    char myBuffer[1000];
    // skip the header line
    fgets(myBuffer, sizeof(myBuffer), File);

    while (cityCount < MAX_CITIES && fgets(myBuffer, sizeof(myBuffer), File) != NULL) {
        killNewline(myBuffer); // Remove the newline character from the end of the line 
        city* c = stringToCity(myBuffer);
        if (c != NULL && c->name != NULL && c->nameLength >0) {
            cities[cityCount] = c;
            cityCount++;
        }
        else if (c != NULL) {
            freeCity(c); // Free the city structure if it was allocated but not added to the array
        }
    }
        fclose(File); // Close the file after use

    // Find the set of cities with the largest populations, whose names add up to 200 characters or less
    // length of city i = cities[i]->nameLength (characters)
    // population of city i = cities[i]->population (integer)
    // dp[i][l] = maximum population using first i cities and total name length l
    long long dp[MAX_CITIES + 1][MAX_NAME_LENGTH + 1];

    // base case: no cities, no population
    for (int l = 0; l <= MAX_NAME_LENGTH; l++) {
        dp[0][l] = 0;
    }

    for (int i = 1; i <= cityCount; i++) {
        int nameLength = cities[i - 1]->nameLength;
        long long population = cities[i - 1]->population;

        for (int l = 0; l <= MAX_NAME_LENGTH; l++) {
            // current nameLength > max length, can't include this city
            if (nameLength > l) {
                dp[i][l] = dp[i - 1][l];
            }
            // current nameLength <= max length,fits in the remaining budget
            else {
                dp[i][l] = dp[i - 1][l]; // Don't include this city
                long long includePopulation = population + dp[i - 1][l - nameLength];
                if (includePopulation > dp[i][l]) {
                    dp[i][l] = includePopulation;
                }
            }
        }
    }

    long long maxPopulation = dp[cityCount][MAX_NAME_LENGTH];

    // Backtrack to find the cities that make up the maximum population
    int chosenCities[MAX_CITIES];
    int numChosen = 0;
    int l = MAX_NAME_LENGTH;

    for (int i = cityCount; i > 0; i--) {
        if (dp[i][l] != dp[i - 1][l]) {
            chosenCities[numChosen] = i - 1; // Store the index of the chosen city
            numChosen++;
            l -= cities[i - 1]->nameLength; // Reduce the remaining length
        }
    }

    // print the results
   printf("Total population: %lld\n", maxPopulation);
   printf("Cities:\n");
   
   for (int i = numChosen - 1; i >= 0; i--) {
    city* c = cities[chosenCities[i]];
    printf(" %s\n", c->name);
   }

   // free every city and its name
   for (int i = 0; i < cityCount; i++) {
    freeCity(cities[i]);
   }
    
    printf("\n");
    fgets(s, sizeof(s), stdin);

   return 0;
}