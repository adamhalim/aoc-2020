#include <stdio.h>
#include <stdlib.h>

int main() {


    // Open our file with input
    FILE *fp;
    fp = fopen("input.txt", "r");


    int last_char_pos = 31;
    char line[34];
    int current_x = 0;
    int counter = 0;

    // We read the file line by line, we increment our index,
    // current_x, by 3 per row, moving us 1 down and 3 right 
    // per loop. 
    while(fgets(line, sizeof(line), fp)) {
        if(line[current_x % last_char_pos] == '#') {
            counter++;
        }
        current_x += 3;
    }

    printf("%d\n", counter);

    return 0;
}