#include <stdio.h>

int main() {

    char s[100];
    char t[100];

    printf ("What is your name? ");
    scanf("%s", s);
    // fgets(s,100,stdin); removed this line because it would read the leftover '\n' and overwrite s with "\n"
    printf("%s? That's a funny name!",s);
    fgets(s,100,stdin);   // remove the "\n" left in the input buffer by scanf
    fgets(t,100,stdin);   // pause the program to wait for the user to press Enter before exiting
    return 0;  // return 0 to indicate that the program finished successfully
}
