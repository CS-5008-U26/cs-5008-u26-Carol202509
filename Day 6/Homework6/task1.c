/*
* print the names of all candies from the file "candy-data.csv".
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure to hold candy information
typedef struct candy_struct {
    char *name;
    int containsChocolate;
    int isFruity;
    int containsCaramel;
    int containsNuts;
    int containsNougat;
    int containsRiceWafersCookies;
    int isHard;
    int isBar;
    int isPluribus;
    double sugarPercent;
    double pricePercent;
    double winPercent;
} candy;

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

candy *stringToCandy(char* textLine) {

    char fieldBuffer[1000];
    int fieldNum = 1;
    char *p = textLine;
    candy *c = malloc(sizeof(candy));
    if (c == NULL) {
        return NULL;
    }

    while (p != NULL && fieldNum <= 13) {
        p = getNextField(p, ',', fieldBuffer);
        if (p != NULL) {
            switch (fieldNum) {
                case 1:
                    c->name = strdup(fieldBuffer); // Store the candy name
                    break;
                case 2:
                    c->containsChocolate = atoi(fieldBuffer); // Store the chocolate flag
                    break;
                case 3:
                    c->isFruity = atoi(fieldBuffer); // Store the fruity flag
                    break;
                case 4:
                    c->containsCaramel = atoi(fieldBuffer); // Store the caramel flag
                    break;
                case 5:
                    c->containsNuts = atoi(fieldBuffer); // Store the nuts flag
                    break;
                case 6:
                    c->containsNougat = atoi(fieldBuffer); // Store the nougat flag
                    break;
                case 7:
                    c->containsRiceWafersCookies = atoi(fieldBuffer); // Store the rice wafers cookies flag
                    break;
                case 8:
                    c->isHard = atoi(fieldBuffer); // Store the hard flag
                    break;
                case 9:
                    c->isBar = atoi(fieldBuffer); // Store the bar flag
                    break;
                case 10:
                    c->isPluribus = atoi(fieldBuffer); // Store the pluribus flag
                    break;
                case 11:
                    c->sugarPercent = atof(fieldBuffer); // Store the sugar percentage
                    break;
                case 12:
                    c->pricePercent = atof(fieldBuffer); // Store the price percentage
                    break;
                case 13:
                    c->winPercent = atof(fieldBuffer); // Store the win percentage
                    break;
            }
            fieldNum++; // Increment the field index
            }
            }
            return c; // Return the pointer to the candy structure
}

candy** readCandyList(char *filename, int *outCount) {
    char lineBuffer[3000];
    int countLines = 0;


    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Could not open the file.\n");
        return NULL;
    }

    fgets(lineBuffer, 3000, f); // Read the header line and ignore it
    countLines = 0;
    while (fgets(lineBuffer, 3000, f) != NULL) {
        countLines++;
    }
    rewind(f); // Reset the file pointer to the beginning of the file
    
    fgets(lineBuffer, 3000, f); // skip the header line
    candy **cArray = malloc(countLines * sizeof(candy*)); // Allocate memory for an array of pointers to candy structures

    for (int i = 0; i < countLines; i++) {
        char *whatWasRead = fgets(lineBuffer, 3000, f); // Read a line from the file
        if (whatWasRead == NULL) {
            break; // If the end of the file has been reached, break out of the loop;
        }
        killNewline(lineBuffer); // Remove the newline character from the end of the line
        cArray[i] = stringToCandy(lineBuffer); // Convert the line to a candy structure and store the pointer in the array
    }
    fclose(f);
    *outCount = countLines; // Store the number of lines read in the output parameter
    return cArray; // Return the pointer to the array of city structures
}

int main() {
    char s[100];

    int countLines;
    candy** myCandyList = readCandyList("../../Resources/candy-data.csv", &countLines);
    if (myCandyList == NULL) {
        printf("Could not open file "); // Exit with an error code if the candy list could not be read
        return 1;
    }
    for (int i = 0; i < countLines; i++) {
        printf("%s\n", myCandyList[i]->name); // Print the name of each candy in the list
    }
    fgets(s, 100, stdin);
    return 0;
}