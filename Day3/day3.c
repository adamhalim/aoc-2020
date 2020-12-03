#include <stdio.h>
#include <stdlib.h>

int treeCounter(int rowJumpIncrementint, int columnJumpIncrement);

int main() {

    printf("Part one: %d\n", treeCounter(3,1));
    printf("Part two: %ld\n", (treeCounter(1,1) * treeCounter(3,1) * treeCounter(5,1)
     * treeCounter(7,1) * treeCounter(1,2)));

    return 0;
}

int treeCounter(int columnJumpIncrement, int rowJumpIncrement) {

    // Open our file with input
    FILE *fp;
    fp = fopen("input.txt", "r");

    int currentX = 0;
    int treeCounter = 0;
    int lastCharIndex = 31;
    char line[34];
    int currentIter = 0;

    // We read the file line by line, we increment our index,
    // current_x, by 3 per row, moving us 1 down and 3 right 
    // per loop. 
    while(fgets(line, sizeof(line), fp)) {
        if(currentIter++  % rowJumpIncrement == 0){
            if(line[currentX % lastCharIndex] == '#') {
                treeCounter++;
            }
            currentX += columnJumpIncrement;
        }
    }
    return treeCounter;
}