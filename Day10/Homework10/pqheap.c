/*
 * Implement a priority queue using a min-heap.
 *
 * Performance results:
 *
 * 10-second enqueue N:
 * Approximately 500,000,000 values took 9.967 seconds.
 *
 * 10-second dequeue N:
 * Approximately 20,000,000 values took 11.330 seconds.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100
#define MAX_VALUE 100000000
#define INITIAL_CAPACITY 50

typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int initqueue(PriorityQueue *queue) {
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

void freequeue(PriorityQueue *queue) {
    free(queue->data);
    queue->data = NULL;
    queue->size = 0;
    queue->capacity = 0;
}

int resizequeue(PriorityQueue *queue, int needed) {
    if (needed <= queue->capacity) {
        return 1;
    }

    int newCapacity = queue->capacity;
    while (newCapacity < needed) {
        newCapacity *= 2;
    }

    int *newData = realloc(queue->data, newCapacity * sizeof(int));
    if (newData == NULL) {
        fprintf(stderr, "Unable to resize priority queue\n");
        return 0;
    }

    queue->data = newData;
    queue->capacity = newCapacity;
    return 1;
}

// Move one newly inserted value toward the root of the min-heap.
void heapifyUp(PriorityQueue *queue, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (queue->data[parent] <= queue->data[index]) {
            break;
        }

        swap(&queue->data[parent], &queue->data[index]);
        index = parent;
    }
}

// Move the root downward until the min-heap property is restored.
void heapifyDown(PriorityQueue *queue, int index) {
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < queue->size &&
            queue->data[leftChild] < queue->data[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < queue->size &&
            queue->data[rightChild] < queue->data[smallest]) {
            smallest = rightChild;
        }

        if (smallest == index) {
            break;
        }

        swap(&queue->data[index], &queue->data[smallest]);
        index = smallest;
    }
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

// Insert one value and restore the min-heap using heapifyUp.
int enqueuevalue(PriorityQueue *queue, int value) {
    if (!resizequeue(queue, queue->size + 1)) {
        return 0;
    }

    int insertedIndex = queue->size;
    queue->data[insertedIndex] = value;
    queue->size++;
    heapifyUp(queue, insertedIndex);
    return 1;
}

// Generate and insert a group of random values one at a time.
int enqueuecount(PriorityQueue *queue, int numberToAdd) {
    if (numberToAdd <= 0) {
        return 1;
    }

    if (!resizequeue(queue, queue->size + numberToAdd)) {
        return 0;
    }

    int* newValues = genarray(numberToAdd);

    if (newValues == NULL) {
        return 0;
    }

    // Insert each generated value into the heap one at a time.
    for (int i = 0; i < numberToAdd; i++) {
        int insertedIndex = queue->size;
        queue->data[insertedIndex] = newValues[i];
        queue->size++;
        heapifyUp(queue, insertedIndex);
    }

    free(newValues);

    return 1;
}

// Remove one minimum value. The root is exchanged with the last element,
// the heap size is reduced, and heapifyDown restores the min-heap.
int dequeuevalue(PriorityQueue *queue, int *removedValue) {
    if (queue->size == 0) {
        return 0;
    }

    *removedValue = queue->data[0];
    swap(&queue->data[0], &queue->data[queue->size - 1]);
    queue->size--;

    if (queue->size > 0) {
        heapifyDown(queue, 0);
    }

    return 1;
}

// Remove and print up to n values from lowest to highest.
int dequeuecount(PriorityQueue *queue, int numberToRemove) {
    if (numberToRemove <= 0) {
        return 0;
    }

    if (numberToRemove > queue->size) {
        numberToRemove = queue->size;
    }

    for (int i = 0; i < numberToRemove; i++) {
        int removedValue = 0;
        if (!dequeuevalue(queue, &removedValue)) {
            break;
        }
        printf("%d ", removedValue);
    }

    if (numberToRemove > 0) {
        printf("\n");
    }

    return numberToRemove;
}

int main(void) {
    char buffer[100];
    PriorityQueue queue;

    if (!initqueue(&queue)) {
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));

    while (1) {
        printf("How many numbers to add: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL ||
            buffer[0] == '\n') {
            break;
        }

        int numberToAdd = atoi(buffer);
        if (numberToAdd < 0) {
            printf("Must be zero or a positive number\n\n");
            continue;
        }

        if (!enqueuecount(&queue, numberToAdd)) {
            break;
        }

        printf("\nHow many numbers to remove: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL ||
            buffer[0] == '\n') {
            break;
        }

        int numberToRemove = atoi(buffer);
        if (numberToRemove < 0) {
            printf("Must be zero or a positive number\n\n");
            continue;
        }

        printf("\n");
        dequeuecount(&queue, numberToRemove);
        printf("\n");

        if (queue.size == 0) {
            break;
        }
    }

    freequeue(&queue);
    return 0;
}