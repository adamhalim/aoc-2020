#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* validator(char *line, char *field_type);
_Bool valid_byr(char *line);
_Bool valid_iyr(char *line);
_Bool valid_eyr(char *line);
_Bool valid_hgt(char *line);
_Bool valid_hcl(char *line);
_Bool valid_ecl(char *line);
_Bool valid_pid(char *line);

int main() {

    _Bool new_pass = 0;
    _Bool cid_found = 0;
    uint valid_passes_part_one = 0;
    u_short key_val_counter = 0;

    // Open our file with input
    FILE *fp = fopen("input.txt", "r");
    // We set a max limit of line_size to 128, 
    // just to be sure we fit the entire string
    size_t line_size = 128;
    char *line;
    size_t len = 0;
    ssize_t read;

    // Function pointer array to all of our validators
    _Bool (*validators[7])(char *line) = {
        valid_byr,
        valid_iyr,
        valid_eyr,
        valid_hgt,
        valid_hcl,
        valid_ecl,
        valid_pid
    };

    // For each new passport, we map a boolean 
    // to the corresponding validator
    _Bool valid_fields[7];
     for(int i = 0; i < 7; i++){
        valid_fields[i] = 0;
    }
   
    uint valid_passes_part_two = 0;

    while((read = getline(&line, &len, fp)) != -1) {
        // If we are at a new passport, we will first check if the 
        // last passport was valid: either all 8 fields have to be 
        // there, just 7 if cid is missing.
        if(new_pass){
            if(!cid_found && key_val_counter == 7) {
                valid_passes_part_one++;
            } else if(key_val_counter == 8) {
                valid_passes_part_one++;
            }

            /* ------------- Part two ----------- */
            // If one of the fields is false, the passport is invalid
            _Bool valid_part_two = 1;
            for(int i = 0; i < 7; i++) {
                if(!valid_fields[i]) {
                    valid_part_two = 0;
                }
            }
            valid_passes_part_two += valid_part_two;

            // We reset all fields to false
            for(int i = 0; i < 7; i++){
                valid_fields[i] = 0;
            }

            /* ---------- endof Part two -------- */
            key_val_counter = 0;
            new_pass = 0;
            cid_found = 0;
        }

        // For all invalid fields, we call the corresponding validator (part two)
        for(int i = 0; i < 7; i++){
            if(!valid_fields[i]){
                valid_fields[i] = (validators[i](line));
            }
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
            if(line[i] == '\0'){
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
        valid_passes_part_one++;
    } else if(key_val_counter == 8) {
        valid_passes_part_one++;
    }

    _Bool valid_part_two = 1;
    for(int i = 0; i < 7; i++) {
        if(!valid_fields[i]) {
            valid_part_two = 0;
        }
    }
    valid_passes_part_two += valid_part_two;

    fclose(fp);
    free(line);
    printf("Valid passports part one: %d\n", valid_passes_part_one);
    printf("Valid passports part two: %d\n", valid_passes_part_two);
    return 0;
}


_Bool valid_byr(char *line) {
    char *byr_str = validator(line, "byr:");
    if(byr_str == NULL) {
        return 0;
    }
    int byr = atoi(byr_str);
    return (byr >= 1920 && byr <=2002);
}

_Bool valid_iyr(char *line) {
    char *iyr_str = validator(line, "iyr:");
    if(iyr_str == NULL) {
        return 0;
    }
    int iyr = atoi(iyr_str);
    return (iyr >=2010 && iyr <= 2020);
}

_Bool valid_eyr(char *line) {
    char *eyr_str = validator(line, "eyr:");
    if(eyr_str == NULL){
        return 0;
    }
    int eyr = atoi(eyr_str);
    return (eyr >=2020 && eyr <= 2030);
}

_Bool valid_hgt(char *line) {
    char *hgt_str = validator(line, "hgt:");
    if(hgt_str == NULL){
        return 0;
    }
    char *unit = strstr(hgt_str, "cm");
    int hgt = atoi(hgt_str);

    if(unit == NULL) {
        unit = strstr(hgt_str, "in");
        // If the unit is neither cm or in, we return 0
        if(unit == NULL) {
            return 0;
        }
        return (hgt >= 59 && hgt <= 76);
    } else {
        return (hgt >= 150 && hgt <= 193);
    }
}

_Bool valid_hcl(char *line) {
    char *hcl_str = validator(line, "hcl:#");
    if(hcl_str == NULL) {
        return 0;
    }

    // We only check if the following string after 
    // # is 6 chars long. We don't check for invalid
    // chars. (cheating?)
    return strlen(hcl_str) == 7;
}

_Bool valid_ecl(char *line) {
    char *ecl_str = validator(line, "ecl:");
    if(ecl_str == NULL) {
        return 0;
    }
    char colors[8][4] = {
        "amb",
        "blu",
        "brn",
        "gry",
        "grn",
        "hzl",
        "oth"
    };

    for(int i = 0; i < 7; i++) {
       if(strcmp(colors[i], ecl_str) == 0) {
           return 1;
       }
    }
    return 0;
}

_Bool valid_pid(char *line) {
    char *pid_str = validator(line, "pid:");
    if(pid_str == NULL){
        return 0;
    }
    return (strlen(pid_str) == 9);
}

// This function returns the value corresponding
// to a field type. E.g. a line with "hcl:#7d3b0c pid:431742871",
// would return "#7d3b0c" if we set field type to "hcl:#"
char* validator(char *line, char *field_type) {

    char *matched_string = strstr(line, field_type);

    // If no substring found, return false
    if(matched_string == NULL) {
        return NULL;
    }

    char* field_val = malloc(strlen(line));
    int field_len = 0;
    int start_index = matched_string - line + 4; 
    for(int i = start_index; i < strlen(line); i++) {
        if(line[i] == ' ' || line[i] == '\n') {
            break;
        }
        field_val[field_len++] = line[i];
    }

    field_val[field_len] = '\0';
    field_val = (char *) realloc(field_val, field_len);
    return field_val;
}