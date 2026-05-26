/* Print all multiples of 63 from 0 to 1500 in a right-justified column.
*/

#include <stdio.h>

int main () {
    int i;

    for (i = 0; i < 1500; i += 63) {
        printf("%5d\n", i);
    }
   
}