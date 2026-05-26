/* Print all prime numbers from 1 to 100.
 */

#include <stdio.h>
#include <time.h>
#include <math.h>

int main () {
    
    clock_t startTime = clock();

    printf("2\n"); // 2 is the only even prime number 

    for (int i = 3; i <= 100000; i += 2) {

        int isPrime = 1; // Assume the number is prime until proven otherwise
        int sqrtI = (int)sqrt((double)i); // Calculate the square root of i once

        for (int j = 3; j <= sqrtI; j += 2) {
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