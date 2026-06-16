/*
* write a program that prompts the user for a filename,
* then prints the size of the file in bytes.
* If the file does not exist, print an error message.
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

	

int main (int argc, char *argv[]) {
    char s[100];
    char filename[1000];

    if (argc >= 2) {
        strcpy(filename, argv[1]); // Copy the filename from the command line argument
    } 
    else {
        printf("Enter the name of a file: ");
        fgets(filename, 1000, stdin);
        filename[strcspn(filename, "\n")] = '\0'; // Remove the newline character
    }

    struct stat fileStat;
	if (stat(filename, &fileStat) < 0) {
		printf ("Whoops!  %s does not exist\n", filename);
        // we could examine errno at this point
	} 
    else {
		printf ("%s has %lld bytes\n", filename, fileStat.st_size);
	}
    fgets(s,100,stdin);
}