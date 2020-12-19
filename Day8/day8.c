#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 int get_val(char* line);
 int find_loop(char* lines[], int line_counter);
 int find_loop_changed_instruction(int index, char c, char* lines[], int line_counter);

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

     /* Part one */
     int acc = find_loop(lines, line_counter);

     if(acc) {
         printf("Loop found! Accumulator = %d\n", accumulator); 
     }


 /* ----------------------- PART TWO ------------------*/
    // For part two, I want to count and find all occurances of 
    // nop and jmp:
    int nop_counter = 0;
    int jmp_counter = 0;
    for(int i = 0; i < line_counter; i++) {
        if(*lines[i] == 'n') {
            nop_counter++;
        } else if(*lines[i] == 'j') {
            jmp_counter++;
        }
    }

    int nop_indexes[nop_counter];
    int jmp_indexes[jmp_counter];
    nop_counter = 0;
    jmp_counter = 0;
    for(int i = 0; i < line_counter; i++) {
        if(*lines[i] == 'n') {
            nop_indexes[nop_counter++] = i;
        } else if(*lines[i] == 'j') {
            jmp_indexes[jmp_counter++] = i;
        }
    }

    // Now we pretty much want to do part 1 of the program again,
    // switching out one occurance of jmp/nop one at a time
    // and checking if the program terminates.
    /* ----------------------- PART TWO ------------------*/

    _Bool found_loop = 1;

    for(int i = 0; i < nop_counter; i++) {
       if(found_loop) {
            found_loop = find_loop_changed_instruction(nop_indexes[i], 'j', lines, line_counter);
        } else {
            printf("Program ran successfully!\nAccumulator = %d\n", accumulator);
            break;
        }
    }

    for(int i = 0; i < jmp_counter; i++) {
        if(found_loop) {
            found_loop = find_loop_changed_instruction(jmp_indexes[i], 'n', lines, line_counter);
        } else {
            printf("Program ran successfully!\nAccumulator = %d\n", accumulator);
            break;
        }
    }
   
}

// This function will change an (nop<->jmp) entry in our lines[] and 
// call find_loop. 
int find_loop_changed_instruction(int index, char c, char* lines[], int line_counter) {
    // Since our find_loop only looks at the first char of a line,
    // we only need to change the first char and call find_loop
    lines[index][0] = c;
    int loop_found = find_loop(lines, line_counter);

    // When we're done with find_loop, we want to change back the char 
    // to what it was initially
    if(c == 'n') {
        lines[index][0] = 'j';
    } else {
        lines[index][0] = 'n';
    }

    return loop_found;
}

int find_loop(char* lines[], int line_counter){
    accumulator = 0;
    
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
            return 1;
        }
        if(*lines[i] == 'a') {
            accumulator += get_val(lines[i]);
        } else if (*lines[i] == 'j') {
            i += get_val(lines[i]) -1;
            if( i > line_counter) {
                // If we jump to somewhere outside of our scope,
                // I guess we terminate?
                return 0;
            }
        } else if (*lines[i] == 'n') {
            // For now, don't do anything. Might delete later
        }
        alreadyVisited[i] = 1;
    }
    // If we can loop through all of our instructions,
    // the program will terminate successfully.
    return 0;
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