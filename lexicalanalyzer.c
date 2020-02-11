#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nulsym = 1;
int identsym = 2;
int numbersym = 3;
int plussym = 4;
int minussym = 5;
int multsym = 6;
int slashsym = 7;
int oddsym = 8;
int eqlsym = 9;
int neqsym = 10;
int lessym = 11;
int leqsym = 12;
int gtrsym = 13;
int geqsym = 14;
int lparentsym = 15;
int rparentsym = 16;
int commasym = 17;
int semicolonsym = 18;
int periodsym = 19;
int becomessym = 20;
int beginsym = 21;
int endsym = 22;
int ifsym = 23;
int thensym = 24;
int whilesym = 25;
int dosym = 26;
int callsym = 27;
int constsym = 28;
int varsym = 29;
int procsym = 30;
int writesym = 31;
int readsym = 32;
int elsesym = 33;

// globals
char * reserved_words[] = {
    "const", "var", "procedure", "cal", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"
};
int RESERVED_WORDS_LEN = 14;

char special_symbols[] = {
    '+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':'
};
int SPECIAL_SYMBOLS_LEN = 14;

char invisible_chars[] = {
    '\t', ' ', '\n', '\r', '\v', '\f'
};
int INVISIBLE_CHARS_LEN = 6;


// dynamic strcat
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

// Checks if word is a reserved word
int is_reserved_word(char * word) {
    for (int i = 0; i < RESERVED_WORDS_LEN; i++) {
        if (strcmp(reserved_words[i], word) == 0) {
            return 1;
        }
    }
    
    return 0;
}

// Checks if symbol is special symbol
int is_special_symbol(char symbol) {
    for (int i = 0; i < SPECIAL_SYMBOLS_LEN; i++) {
        if (special_symbols[i] == symbol) {
            return 1;
        }
    }
    
    return 0;
}

// Checks if symbol is whitespace
int is_invisible_char(char symbol) {
    for (int i = 0; i < INVISIBLE_CHARS_LEN; i++) {
        if (invisible_chars[i] == symbol) {
            return 1;
        }
    }
    
    return 0;
}



int main(void) {
	// so we want to have an input reader
	FILE *fp = fopen("input.txt", "r");
	FILE *out = fopen("output.txt", "w");
	
	if (fp == NULL) {
		printf("Error: Could not locate file.\n");
		exit(-1);
	}

	char str [12];
	char ** mega_str = (char **)calloc(1, sizeof(char*));
	int cnt = 0;
	
	// read the input file (in PL/0)
	/*
	while (fscanf(fp, "%s", str) != EOF) {
		mega_str = (char **) realloc(mega_str, sizeof(char*) * (cnt + 1));
		mega_str[cnt] = (char*) calloc(1, sizeof(char));
		mega_str[cnt] = dynamic_strcat(mega_str[cnt], str);
		cnt += 1;
	}
	*/
	// and copy to output file
	char temp_char = fgetc(fp);
	while (temp_char != EOF) {
	    fputc(temp_char, out);
	    temp_char = fgetc(fp);
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

	
	/*
	fclose(fp);
	fp = fopen("output.txt", "w");

	int i;
	for (i = 0; i < cnt; i++)
		fprintf(fp, "%s ", mega_str[i]);
    fclose(fp);
    */
    
	fclose(fp);
	fclose(out);
}
