#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 char* get_str(char* line);
 int get_val(char* line);

 int accumulator = 0;

void main() {

    // Open our file with input
    FILE *fp = fopen("input.txt", "r");

    // We set a max limit of line_size to 9, 
    // just to be sure we fit the entire string
    size_t line_size = 9;
    char *line;
    size_t len = 0;
    ssize_t read;
    

    // We first loop through the file to get how many lines
    // there are. We do this to create a char*[] of 
    // fixed length.
    int line_counter = 0;
    while((read = getline(&line, &len, fp)) != -1) {
        line_counter++;
    }

    fp = fopen("input.txt", "r");
    char *lines[line_counter];
    int index = 0;

    // we then open the file again and assign each index of 
    // the char*[] to a char*.
    while((read = getline(&line, &len, fp)) != -1) {
        lines[index] = malloc(strlen(line) +1);
        strcpy(lines[index++], line);
    }

    // We create a boolean array that keeps track of 
    // if we've already executed an instruction on a given line.
    // All values are initialized to 0 
    // (is there a nicer way to do this? arr[] = {0} wouldn't work)
    _Bool alreadyVisited[line_counter];
    for(int i = 0; i < line_counter; i++) {
        alreadyVisited[i] = 0;
    }
    
    // We loop through each of our saved strings. We match the first 
    // char of each string to check what to do
    for(int i = 0; i < line_counter; i++) {
        if(alreadyVisited[i]) {
            printf("Loop found! Accumulator = %d.\n", accumulator);
            break;
        }
        if(*lines[i] == 'a') {
            accumulator += get_val(lines[i]);
        } else if (*lines[i] == 'j') {
            i += get_val(lines[i]) -1;
        } else if (*lines[i] == 'n') {
            // For now, don't do anything. Might delete later
        }
        alreadyVisited[i] = 1;
    }
}

// Returns the integer value of an instruction
int get_val(char* line) {
    char * str_val = strstr(line, "+");
    int val;
    if(str_val == NULL) {
        val = atoi(strstr(line, "-"));
    } else {
        val = atoi(str_val +1);
    }
    return val;
}
