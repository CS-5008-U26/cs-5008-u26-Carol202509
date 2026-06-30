/*
* Implement a doubly-linked list of city structures.
* The list is built from a CSV file containing city information.
* The program provides a menu for the user to perform various operations on the list.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure to hold city information
typedef struct city_struct {
    char *name;
    char *nameAscii;
    char *stateId;
    char *stateName;
    char *countyFIPS;
    char *countyName;
    double latitude;
    double longitude;
    int population;
} city;

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
            case 1:
                c->name = strdup(fieldBuffer); // Store the city name
                break;
            case 2:
                c->nameAscii = strdup(fieldBuffer); // Store the ASCII city name
                break;
            case 3:
                c->stateId = strdup(fieldBuffer); // Store the state ID
                break;
            case 4:
                c->stateName = strdup(fieldBuffer); // Store the state name
                break;
            case 5:
                c->countyFIPS = strdup(fieldBuffer); // Store the county FIPS code
                break;
            case 6:
                c->countyName = strdup(fieldBuffer); // Store the county name
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
    free(c->name);
    free(c->nameAscii);
    free(c->stateId);
    free(c->stateName);
    free(c->countyFIPS);
    free(c->countyName);
    free(c); // Free the city structure itself
    }

// Print the information of a city structure
void printCity(city* c) {
    if (c == NULL) {
        return;
    }
    printf("%s %s, population %d\n", c->nameAscii, c->stateId, c->population);
}

// define a doubly-linked list node structure
typedef struct doubleNode {
    void* data;
    struct doubleNode* next;
    struct doubleNode* prev;
} dNode;

// create a new node with the given data
dNode* createNode(void* data) {
    dNode* newNode = (dNode*)malloc(sizeof(dNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode -> data = data;
    newNode -> next = NULL;
    newNode -> prev = NULL;
    return newNode;
}

// insert a new node at the front of the list
dNode* insertFront(dNode* head, void* data) {
    dNode* newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    newNode -> next = head;
    if (head != NULL) {
        head -> prev = newNode;
    }
    return newNode;
}

// insert a new node at the end of the list
dNode* insertLast(dNode* head, void* data) {
    dNode* newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    if (head == NULL) {
        return newNode;
    }
    dNode* current = head;
    while (current -> next != NULL) {
        current = current -> next;
    }
    current -> next = newNode;
    newNode -> prev = current;
    return head;
}

// get the nth node in the list (1-based index)
dNode* getNth(dNode* head, int position) {
    if (head == NULL || position < 1) {
        return NULL;
    }
    dNode* current = head;
    int index = 1; // 1 stands for the first city in the list
    while (current != NULL && index < position) {
        current = current -> next;
        index++;
    }
    return current;
}

// unlink a node from the list without freeing it
dNode* removeNode(dNode* head, dNode* nodeToRemove) {
    if (head == NULL || nodeToRemove == NULL) {
        return head;
    }
    //case1: remove the head node
    if (head == nodeToRemove) {
        dNode* newHead = head -> next;
        if (newHead != NULL) {
            newHead -> prev = NULL;
        }
        nodeToRemove -> next = NULL;
        nodeToRemove -> prev = NULL;

        return newHead;
    }
    // case2: remove a node in the middle or at the end
    dNode* current = head;

    while (current != NULL && current -> next != nodeToRemove) {
        current = current -> next;
    }
    if (current != NULL) {
        current -> next = nodeToRemove -> next;
        if (nodeToRemove -> next != NULL) {
            nodeToRemove -> next -> prev = current;
        }
        nodeToRemove -> next = NULL; // Unlink the node
        nodeToRemove -> prev = NULL; // Unlink the node
    }
    return head;
}

// delete a node from the list and free its memory
dNode* deleteNode(dNode* head, dNode* nodeToDelete) {
    if (head == NULL || nodeToDelete == NULL) {
        return head;
    }
    // case1: delete the head node
    if (head == nodeToDelete) {
        dNode* newHead = head -> next;
        if (newHead != NULL) {
            newHead -> prev = NULL;
        }
        freeCity((city*)head -> data); // Free the city structure
        free(head);
        return newHead;
    }
    // case2: delete a node in the middle or at the end
    dNode* current = head;

    while (current != NULL && current -> next != nodeToDelete) {
        current = current -> next;
    }
    if (current != NULL) {
        current -> next = nodeToDelete -> next;
        if (nodeToDelete -> next != NULL) {
            nodeToDelete -> next -> prev = current;
        }
        freeCity((city*)nodeToDelete -> data); // Free the city structure
        free(nodeToDelete);
    }
    return head;
}

// get the length of the list
int getLength(dNode* head) {
    int length = 0;
    dNode* current = head;
    while (current != NULL) {
        length++;
        current = current -> next;
    }
    return length;
}

// reverse the linked list
dNode* reverseList(dNode* head) {
    dNode* prev = NULL;
    dNode* current = head;
    dNode* next = NULL;
    while (current != NULL) {
        next = current -> next;
        current -> next = prev;
        current -> prev = next;
        prev = current;
        current = next;
    }
    return prev; // New head of the reversed list
}

// free the entire list and its data
void freeList(dNode* head) {
    dNode* current = head;

    while (current != NULL) {
        dNode* nextNode = current -> next;
        freeCity((city*)current -> data); // Free the city structure
        free(current);
        current = nextNode;
    }
}

int main() {
    char inputBuffer[3000];

    FILE *f = fopen("../../Resources/uscities.csv", "r");
    if (f == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }
    fgets(inputBuffer, 3000, f); // skip the header line

    // build a linked list of city structures
    dNode* cityList = NULL;
    for (int i = 0; i < 20; i++) {
        if (fgets(inputBuffer, 3000, f) == NULL) {
            break;
        }
        killNewline(inputBuffer);
        city *c = stringToCity(inputBuffer);
        cityList = insertLast(cityList, c);
    }
    fclose(f);

    char buffer[100];
    int n;

    while (1) {
        printf("size, delete, reverse, get, or print: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        if (strcmp(buffer, "size\n") == 0) {
            printf("Size is %d\n", getLength(cityList));
        }
        else if (strcmp(buffer, "delete\n") == 0) {
            printf("Enter a number: ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                break;
            }
            n = atoi(buffer);
            dNode* nodeToDelete = getNth(cityList, n);
            if (nodeToDelete != NULL) {
                cityList = deleteNode(cityList, nodeToDelete);
            }
        }
        else if (strcmp(buffer, "reverse\n") == 0) {
            cityList = reverseList(cityList);
        }
        else if (strcmp(buffer, "get\n") == 0) {
            printf("Enter a number: ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                break;
            }
            n = atoi(buffer);
            dNode* target = getNth(cityList, n);
            if (target != NULL) {
                cityList = removeNode(cityList, target);
                target -> next = cityList;
                if (cityList != NULL) {
                    cityList -> prev = target;
                }
                cityList = target;
            }
        }
        else if (strcmp(buffer, "print\n") == 0) {
            printf("Enter a number: ");

            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                break; 
            }

            n = atoi(buffer);

            dNode* current = cityList;
            for (int i = 0; i < n && current != NULL; i++) {
                printCity((city*)current -> data);
                current = current -> next;
            }
        }
        else {
            break;
        }
    }

    freeList(cityList); // Free the linked list
    return 0;
}