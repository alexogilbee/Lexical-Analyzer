// Harry Sauers
// Alex Ogilbee


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// globals

typedef enum { 
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym 
} token_type;

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

char * program_string = "";


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

// Checks if character is a number
int is_number(char c) {
    int n = c - '0';
    int[] nums = {0,1,2,3,4,5,6,7,8,9};
    
    for (int i = 0; i < 10; i++) {
        if (n == nums[i]) {
            return 1;
        }
    }
    return 0;
}

// Checks if character is a letter
int is_letter(char c) {
    int letter_min_1 = 'A';
    int letter_max_1 = 'Z';
    int letter_min_2 = 'a';
    int letter_max_2 = 'z';
    
    // check if within valid letter ranges
    if ( (c >= letter_min_1 && c <= letter_max_1) || (c >= letter_min_2 && c <= letter_max_2) ) {
        return 1;
    } else {
        return 0;
    }
}

// checks if all chars are numbers
int is_only_numbers(char * word) {
    for (int i = 0; i < strlen(word); i++) {
        if (! is_number(word[i])) {
            return 0;
        }
    }
    return true;
}

// checks if word is made up of ONLY numbers and/or letters
int is_letters_and_numbers(char * word) {
    for (int i = 0; i < strlen(word); i++) {
        if (! is_letter(word[i]) && ! is_number(word[i])) {
            return 0;
        }
    }
    return 1;
}

// checks if word is too long
int is_word_too_big(char * word, int max) {
    if (strlen(word) <= max) {
        return 0;
    } else {
        return 1;
    }
}

void MalormedNumberError(void) {
    printf("Error: Malformed number.");
}

void SyntaxError(void) {
    printf("Error: Syntax error.");
}

void NumberTooBigError(void) {
    printf("Error: number too big");
}

void StringTooLongError(void) {
    printf("Error: string too long");
}

void EOF_COMMENT_ERROR(void) {
    printf("Error: EOF reached while in comment.");
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
    
    // begin output formatting:
    fprintf(out, "Source Program: \n");
    
    // and copy to output file
    char temp_char = fgetc(fp);
    while (temp_char != EOF) {
        program_string = dynamic_strcat(program_string, &temp_char);
        
        fputc(temp_char, out);
        temp_char = fgetc(fp);
    }
    
    // while we read it
    int i = 0;
    int in_comment = 0;
    int program_length = strlen(program_string);
    while (i < program_length) {
        char c = program_string[i];
        int token;
        
        // we run some methods that determine what the word is
        // check if a comment, if so then set comment var to 1? until newline OR */
        if (c == '/') {
            if (i + 1 < program_length) {
                if (program_string[i+1] == '*') {
                    in_comment = 1;
                    i += 2;
                }
            }
        }
        // if outside program
        if (i >= program_length && in_comment) {
            // ERROR
            EOF_COMMENT_ERROR();
        }
        
        // while in comment, 
        while (i < program_length && in_comment) {
            c = program_string[i];
            if (c == '*') {
                i += 1;
                
                if (i >= program_length) {
                    EOF_COMMENT_ERROR();
                }
                
                c = program_string[i];
                if (c == '/') {
                    // no longer in comment
                    in_comment = 0;
                    i += 1;
                    continue;
                }
            }
        }
        
        // check for special characters
        if (is_special_symbol(c)) {
            // do stuff
        }
        
        // filter out the commas, whitespace, etc. (i guess not commas)
        if (is_invisible_char(c)) {
            i += 1;
            continue;
        }
        
        // build word
        char * word = {&c};
        int j = i + 1;
        
        while (! (is_invisible_char(program_string[j])) && ! (is_special_symbol(program_string[j])) && j < program_length) {
            word = dynamic_strcat(word, &program_string[j]);
            j += 1;
        }
        
        // check if the string is a reserved word
        if (is_reserved_word(word)) {
            // do stuff
            printf("Reserved word found\n");
        } else {
            // remember: let = word

            // 4 things to check: (return if any fail)
            
            // if let[0] is a number, check all for nonletters and return accordingly
                // loop through all chars in word, see if they are numbers. if true: nothing, else: MalformedNumberError(), return/exit
                // if true: treat as token #3 (literal), else: SyntaxError(), return/exit
                
            // if let[0] is a number, token is a number, so check if strlen <= 5
                // check len: if true, we're good. else: NumberTooBigError(), return/exit
                
                
            // if let[0] is a LETTER, check if length <= 11
                // if true: nothing (see below) else: StringTooLongError(), return/exit
            // if let[0] is a letter, check if subsequent chars are letters or numbers ONLY (not exclusive)
                // if true: token #2, else: MalformedStringError(), return/exit
        
        }
        
        // append {word/lexeme, token} to word_list[array]

        // we also want an output writer, or maybe just import the megastringconcat
        // ^ see below
        i += 1;
    }
    
    fclose(fp);
    fclose(out);
}
