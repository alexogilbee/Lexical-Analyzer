#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * dynamic_strcat(char * base, char * added) {
	// resize the base String
	char * conjoined = (char *)malloc(strlen(base) + strlen(added) + 1);

	if (conjoined == NULL) {
		printf("Error: failed to create char array.\n");
		return NULL;
	}

	// strcat and go
	strcpy(conjoined, base);

	return strcat(conjoined, added);
}

int main(void) {
	// so we want to have an input reader
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("Error: Could not locate file.\n");
		exit(-1);
	}

	char str [12];
	char ** mega_str = (char **)calloc(1, sizeof(char*));
	int cnt = 0;
	// we read the input file (in PL/0)
	while (fscanf(fp, "%s", str) != EOF) {
		cnt++;
		mega_str = (char **)realloc(mega_str, sizeof(char*)*cnt);
		mega_str[cnt-1] = (char*)calloc(1, sizeof(char));
		mega_str[cnt-1] = dynamic_strcat(mega_str[cnt-1], str);
	}
	// while we read it (fscanf for EVERY string)
		// we run some methods that determine what the word is
			// check if a comment, if so then set comment var to 1? until newline OR */

			// filter out the commas, whitespace, etc. (i guess not commas)
			// check if the string is a reserved word

			// 4 things to check: (return if any fail)
			// if let[0] is a number, check all for nonletters and return accordingly
			// if let[0] is a number, token is a number, so check if strlen <= 5 (6 for null?)
			// if let[0] is a LETTER, check if length <= 11 (12 null)
			// if let[0] is a letter, check if subsequent chars are letters or numbers ONLY

		// we also want an output writer, or maybe just import the megastringconcat
		// thing again, then swap input fp to output
			
	fclose(fp);
	fp = fopen("output.txt", "w");

	int i;
	for (i = 0; i < cnt; i++)
		fprintf(fp, "%s ", mega_str[i]);
}
