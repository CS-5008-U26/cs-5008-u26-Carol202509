/* Print all prime numbers from 1 to 100.
*/

#include <stdio.h>
#include <time.h>

int main () {
    
    clock_t startTime = clock();

    for (int i = 2; i <= 100000; i++) {
        int isPrime = 1; // Assume the number is prime until proven otherwise

        for (int j = 2; j < i; j++) {
            if (i % j == 0) { // If i is divisible by any number less than itself, it's not prime
                isPrime = 0;
                break;
            }
        }

        if (isPrime) {
            printf("%d\n", i);
        }
    }

    clock_t endTime = clock();

    double timeTaken = (double)((endTime - startTime) / CLOCKS_PER_SEC);

    printf("Time taken: %f seconds\n", timeTaken);
    return 0;
}