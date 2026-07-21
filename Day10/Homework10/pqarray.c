/*
 * Implement a priority queue using a sorted list.
 *
 * Performance results:
 *
 * 10-second enqueue N:
 * Approximately 200,000 values took 9.967 seconds.
 *
 * 10-second dequeue N:
 * Removing all 100,000 elements took 0.010160 seconds.
 *
 */

/*
 * Implement a priority queue using a sorted list.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100
#define MAX_VALUE 100000000
#define INITIAL_CAPACITY 50

/* P R I O R I T Y   Q U E U E   D A T A */

typedef struct {
    int* data;
    int size;
    int capacity;
} PriorityQueue;

/* Y O U R   S O R T   F U N C T I O N */

void sortarray(int a[], int n) {
    /*
     * Insertion sort.
     *
     * The array is sorted from lowest to highest so that the lowest
     * priority value is stored at the front of the array.
     */
    for (int i = 1; i < n; i++) {
        int value = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > value) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = value;
    }
}

/* U T I L I T Y   F U N C T I O N S */

// printarray - print an array of ints
// a is the array, n is the number of elements

void printarray(int a[], int n) {
    int numberToPrint = ((n < MAX_TO_PRINT) ? n : MAX_TO_PRINT);
    for (int i=0; i < numberToPrint; i++) {
        printf ("%d ", a[i]);
    }
    printf ("\n");
}

// genarray - return an array of random ints
// numberofelements is how many elements are in the array

int* genarray(int numberofelements) {
    int* result = malloc(numberofelements * sizeof(int));

    if (result == NULL) {
        printf("malloc failed\n");
    } else {
        for (int i = 0; i < numberofelements; i++) {
            /*
             * Generate a larger random number because rand() may
             * return only a 15-bit value on some systems.
             */
            long long int r1 = rand();
            long long int r2 = rand();

            long long int randomValue =
                (r1 << 14) + (r2 & 0x3fff);

            result[i] = (int)(randomValue % MAX_VALUE);
        }
    }

    return result;
}

/* P R I O R I T Y   Q U E U E   F U N C T I O N S */

// initialize an empty priority queue

int initqueue(PriorityQueue* queue) {
    queue->data = malloc(INITIAL_CAPACITY * sizeof(int));
    queue->size = 0;
    queue->capacity = 0;

    if (queue->data == NULL) {
        fprintf(stderr, "Failed to initialize priority queue\n");
        return 0;
    }

    queue->capacity = INITIAL_CAPACITY;
    return 1;
}

// release all memory used by the priority queue

void freequeue(PriorityQueue* queue) {
    free(queue->data);
    queue->data = NULL;
    queue->size = 0;
    queue->capacity = 0;
}

// make the backing array large enough to hold required elements

int resizequeue(PriorityQueue* queue, int needed) {
    if (needed <= queue->capacity) {
        return 1;
    }

    int newCapacity = queue->capacity;

    // Double the capacity until it is large enough.
    while (newCapacity < needed) {
        newCapacity *= 2;
    }

    int* newData = realloc(queue->data, newCapacity * sizeof(int));

    if (newData == NULL) {
        fprintf(stderr, "Unable to resize priority queue\n");
        return 0;
    }

    queue->data = newData;
    queue->capacity = newCapacity;

    return 1;
}

// enqueuecount - add random values to the priority queue

int enqueuecount(PriorityQueue* queue, int numberToAdd) {
    if (numberToAdd <= 0) {
        return 1;
    }

    int requiredSize = queue->size + numberToAdd;

    if (!resizequeue(queue, requiredSize)) {
        return 0;
    }

    int* newValues = genarray(numberToAdd);

    if (newValues == NULL) {
        return 0;
    }

    // Copy the newly generated numbers to the end of the queue.
    for (int i = 0; i < numberToAdd; i++) {
        queue->data[queue->size + i] = newValues[i];
    }

    queue->size += numberToAdd;

    free(newValues);

    // Sort the priority queue
    sortarray(queue->data, queue->size);

    return 1;
}

// dequeuecount - remove up to n lowest values

int dequeuecount(PriorityQueue *queue, int n) {
    if (n <= 0) {
        return 0;
    }

    // Do not remove more elements than the queue contains.
    int numberToRemove = n;

    if (numberToRemove > queue->size) {
        numberToRemove = queue->size;
    }

    // Remove the lowest values from the front.

    for (int i = 0; i < numberToRemove; i++) {
        printf("%d ", queue->data[i]);
    }

    if (numberToRemove > 0) {
        printf("\n");
    }

    int remaining = queue->size - numberToRemove;

    // Shift the remaining elements toward the front.
    memmove(
        queue->data, // destination: start of the array
        queue->data + numberToRemove, // source: start of the remaining elements
        remaining * sizeof(int) // number of bytes to move
    );

    queue->size = remaining;

    return numberToRemove;
}

/* T I M I N G   F U N C T I O N S */

void timedenqueue(PriorityQueue* queue, int count) {
    clock_t startTime = clock();

    int success = enqueuecount(queue, count);

    clock_t endTime = clock();

    double elapsedTime =
        (double)(endTime - startTime) / CLOCKS_PER_SEC;

    if (success) {
        printf(
            "Added %d values. Queue size: %d\n",
            count,
            queue->size
        );

        printf(
            "Enqueue elapsed time: %f seconds\n\n",
            elapsedTime
        );
    }
}

void timeddequeue(PriorityQueue* queue, int count) {
    clock_t startTime = clock();

    int numberRemoved = dequeuecount(queue, count);

    clock_t endTime = clock();

    double elapsedTime =
        (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf(
        "Removed %d values. Queue size: %d\n",
        numberRemoved,
        queue->size
    );

    printf(
        "Dequeue elapsed time: %f seconds\n\n",
        elapsedTime
    );
}

/* M A I N   F U N C T I O N */

int main(void) {
    char buffer[100];
    PriorityQueue queue;

    if (!initqueue(&queue)) {
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));

    while (1) {
        // Ask how many values to enqueue.
        printf("How many numbers to add: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        // A blank line ends the program.
        if (buffer[0] == '\n') {
            break;
        }

        int numberToAdd = atoi(buffer);

        if (numberToAdd < 0) {
            printf("Must be zero or a positive number\n\n");
            continue;
        }

        enqueuecount(&queue, numberToAdd);

        // Ask how many values to dequeue.
        printf("How many numbers to remove: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        if (buffer[0] == '\n') {
            break;
        }

        int numberToRemove = atoi(buffer);

        if (numberToRemove < 0) {
            printf("Must be zero or a positive number\n\n");
            continue;
        }

        dequeuecount(&queue, numberToRemove);

        // Stop when the queue becomes empty.
    
        if (queue.size == 0) {
            printf("Priority queue is empty.\n");
            break;
        }
    }

    freequeue(&queue);

    return 0;
}