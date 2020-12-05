#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    _Bool new_pass = 0;
    _Bool cid_found = 0;
    uint valid_passes = 0;
    u_short key_val_counter = 0;

    // Open our file with input
    FILE *fp = fopen("input.txt", "r");
    // We set a max limit of line_size to 128, 
    // just to be sure we fit the entire string
    size_t line_size = 128;
    char *line;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&line, &len, fp)) != -1) {
        // If we are at a new passport, we will first check if the 
        // last passport was valid: either all 8 fields have to be 
        // there, just 7 if cid is missing.
        if(new_pass){
            if(!cid_found && key_val_counter == 7) {
                valid_passes++;
            } else if(key_val_counter == 8) {
                valid_passes++;
            }
            key_val_counter = 0;
            new_pass = 0;
            cid_found = 0;
        }

        for(int i = 0; i < line_size;  i++) {
            // If we reach a new line, we check if it's an empty line.
            // if it's empty, we know we're at a new passport.
            if(line[i] == '\n'){
                if(!i) {
                    new_pass = 1;
                }
                break;
            }
            // End of file, break
            if(line[i] == NULL){

                break;
            }
            // We count the key:value pairs
            if(line[i] == ':'){
                key_val_counter++;
            }
        }
        // If we haven't found "cid" yet, we'll
        // search for it in the line.
        if(!cid_found) {
           cid_found = strstr(line, "cid");
        }
    }
    
    // We need to check the conditions once again
    // after the loop ends.
    if(!cid_found && key_val_counter == 7) {
        valid_passes++;
    } else if(key_val_counter == 8) {
        valid_passes++;
    }

    fclose(fp);
    free(line);
    printf("Valid passports: %d\n", valid_passes);
    return 0;
}

// This function will search for a substring within
// another string and return it if there is a match.
// If there is a not, this function returns NULL.
char *get_substring(char *line, char *substr) {

    // The matched_string will trim the first part of
    // the string, not matching the substr. E.g
    // strstr("Find me!!", "me") returns "me!!".
    char *matched_string = strstr(line, substr);

    // If no substring found, return null
    if(matched_string == NULL) {
        return NULL;
    }

    int start_index = matched_string - line;
    char *res_str = malloc(strlen(substr) - start_index + 1); 
    
    int str_index = 0;
    // We loop from our starting index, to the length of our 
    // substr + the starting index, filling our char* with 
    // chars from *line
    for(int i = start_index; i < strlen(substr) + start_index; i++) {
        res_str[str_index++] = line[i];
    }
    res_str[str_index] = '\0';
    return res_str;
}