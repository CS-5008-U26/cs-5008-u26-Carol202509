#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure to hold city information
typedef struct city_struct {
    char* nameAscii;
    char* stateId;
    int countyFIPS;
    double latitude;
    double longitude;
    int population;
} city;

// Remove the newline character from the end of the string
void killNewline (char* str) {
    if (strlen(str) > 1 && (str[strlen(str) - 1]) == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}

char *getNextField (char* start, char separator, char* out) {
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

city *stringToCity(char* textLine) {
    char fieldBuffer[1000];
    int fieldNum = 1;
    char *p = textLine;

    city *c = malloc(sizeof(city));
    if (c == NULL) {
        return NULL;
    }

    while (p != NULL && fieldNum <= 9) {
        p = getNextField(p, ',', fieldBuffer);

        if (p == NULL) {
            break;
        }

        switch (fieldNum) {
            case 2:
                c->nameAscii = strdup(fieldBuffer); // Store the ASCII city name
                break;
            case 3:
                c->stateId = strdup(fieldBuffer); // Store the state ID
                break;
            case 5:
                c->countyFIPS = atoi(fieldBuffer); // Store the county FIPS code
                break;
            case 7:
                c->latitude = atof(fieldBuffer); // Convert latitude to a double and store it
                break;
            case 8:
                c->longitude = atof(fieldBuffer); // Convert longitude to a double and store it
                break;
            case 9:
                c->population = atoi(fieldBuffer); // Convert population to an integer and store it
                break;
        }
            
        fieldNum++; // Increment the field index
    }
    
    return c; // Return the pointer to the city structure
}

/*
 * Generic vector, doubling dynamic array.
*/

typedef struct vector_struct {
    void** data; // Pointer to an array of city pointers
    int used; // Current number of cities in the vector
    int size; // Maximum number of cities the vector can hold
} vector;


vector* createVector(int initialSize) {
    vector* v = (vector*)malloc(sizeof(vector));
    if (v == NULL) {
        return NULL; // Memory allocation failed
    }
    v->data = (void**)malloc(initialSize * sizeof(void*));
    if (v->data == NULL) {
        free(v); // Free the vector structure if memory allocation for data fails
        return NULL;
    }
    v->used = 0; // Initialize the used count to zero
    v->size = initialSize; // Set the initial size of the vector
    return v;
}

void insertLast (vector* v, void* element) {
    if (v == NULL) {
        return;
    }
    if (v->used >= v->size) {
        v->size = v->size * 2; // Double the size of the vector
        void** newData = (void**)malloc(sizeof(void*) * v->size); // Allocate new memory for the resized vector
        if (newData == NULL) {
            return; // Memory allocation failed
        }
        // Copy old elements to the new memory
        for (int i = 0; i < v->used; i++) {
            newData[i] = v->data[i];
        }
        free(v->data);
        v->data = newData;
    }

    v->data[v->used] = element; // Insert the new element at the end
    v->used++; // Increment the used count
}

// Free the memory allocated for a city structure
void freeCity(city* c) {
    if (c == NULL) {
        return;
    }
    free(c->nameAscii);
    free(c->stateId);
    free(c); // Free the city structure itself
    }

int main() {
    char inputBuffer[100];
    printf("How many cities: ");
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    int n = atoi(inputBuffer);

    FILE* f = fopen("../../Resources/uscities.csv", "r");
    if (f == NULL) {
        printf("Error: Could not open file.\n");

        return 1;
    }

    char lineBuffer[3000];
    fgets(lineBuffer, sizeof(lineBuffer), f);

    vector* cityVector = createVector(4); // Create a vector with an initial size of 4
    if (cityVector == NULL) {
        printf("Error: Could not create vector.\n");
        fclose(f);
        return 1;
    }

    int count = 0;
    while (count < n && fgets(lineBuffer, sizeof(lineBuffer), f) != NULL) {
        killNewline(lineBuffer);
        city* c = stringToCity(lineBuffer);
        if (c != NULL) {
            insertLast(cityVector, c);
            count++;
        }
    }
    fclose(f);

    for (int i = 0; i < cityVector->used; i++) {
        city* c = (city*)cityVector->data[i];
        printf("%s %s, population %d, at (%.4f, %.4f)\n",
               c->nameAscii, c->stateId, c->population, c->latitude, c->longitude);
    }

    for (int i = 0; i < cityVector->used; i++) {
        freeCity((city*)cityVector->data[i]);
    }
    free(cityVector->data);
    free(cityVector);

    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    return 0;
}