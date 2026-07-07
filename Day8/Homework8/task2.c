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

// Free the memory allocated for a city structure
void freeCity(city* c) {
    if (c == NULL) {
        return;
    }
    free(c->nameAscii);
    free(c->stateId);
    free(c); // Free the city structure itself
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

/*
 * Binary search Tree (BST) implementation on latitude.
 */

typedef struct bstnode_struct {
    city* cityPtr; // Pointer to a city structure
    struct bstnode_struct* left; // Pointer to the left child node
    struct bstnode_struct* right; // Pointer to the right child node
}bstnode;

// Insert a city into the BST, ordered by latitude
// Returns the root of the BST after insertion
bstnode* bstInsert(bstnode* root, city* c) {
    if (root == NULL) {
        bstnode* newNode = (bstnode*)malloc(sizeof(bstnode));
        if (newNode == NULL) {
            return NULL; // Memory allocation failed
        }
        newNode->cityPtr = c;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode; // Return the new node as the root
    }

    if (c->latitude < root->cityPtr->latitude) {
        root->left = bstInsert(root->left, c); // Insert into the left subtree
    } else {
        root->right = bstInsert(root->right, c); // Insert into the right subtree
    }

    return root; // Return the unchanged root pointer
}

// Inorder traversal of the BST to fill an array with city pointers
void inorderTraverse(bstnode* root, city** cityArray, int* index) {
    if (root == NULL) {
        return;
    }
    inorderTraverse(root->left, cityArray, index); // Traverse the left subtree
    cityArray[*index] = root->cityPtr;
    (*index)++;
    inorderTraverse(root->right, cityArray, index); // Traverse the right subtree
}

// Perform a linear search on an array of city pointers to find a city by name
int linearSearch(city** cityArray, int size, char* name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(cityArray[i]->nameAscii, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Free the memory allocated for the BST nodes
void freeBST(bstnode* root) {
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
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

    vector* cityVector = createVector(4);
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

    // build the BST based on latitude
    bstnode* root = NULL;
    for (int i = 0; i < cityVector->used; i++) {
        root = bstInsert(root, (city*)cityVector->data[i]);
    }

    // inorder traversal to get cities sorted by latitude
    city** sortedByLatitude = (city**)malloc(cityVector->used * sizeof(city*));
    int index = 0;
    inorderTraverse(root, sortedByLatitude, &index);

    int nyIndex = linearSearch(sortedByLatitude, cityVector->used, "New York");
    printf("By latitude, New York is index %d\n", nyIndex);

    freeBST(root);
    free(sortedByLatitude);
    
    for (int i = 0; i < cityVector->used; i++) {
        freeCity((city*)cityVector->data[i]);
    }
    free(cityVector->data);
    free(cityVector);

    return 0;
}