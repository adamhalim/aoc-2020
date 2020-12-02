#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int num;
    struct node *next;   /* Next list element */
    struct node *prev;  /* Previous list element */
};

struct list {
    struct node head;  /* List head */
    struct node tail;  /* List tail */
};

// Initializes our linkedlist as an empty list
void init_list(struct list* list)  {
    list->head.prev = NULL;
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
}

// Pushes an element to the back of the list
void list_append(struct list *list, struct node *elem) {
    elem->prev = list->tail.prev;
    elem->next = &list->tail;
    list->tail.prev->next = elem;
    list->tail.prev = elem;
}

int main() {

    struct list *list = (struct list*)malloc(sizeof(struct list));
    init_list(list);
    
    // Open our file with input
    FILE *fp;
    fp = fopen("input.txt", "r");


    // This will append all entires in the data file 
    // to our list
    char line[6];
    while(fgets(line, sizeof(line), fp)) {
        struct node *elem = malloc(sizeof(struct node));
        // Converts our string to an integer and saves it in element
        // and appends it to our linkedlist
        elem->num = atoi(line);
        list_append(list, elem);
    }
    
    struct node *first_loop = list->head.next;
    int first_ans;
    int second_ans;

    // Iterate through entire linkedlist, with three nested loops.
    // At each sub-loop, we need to reset the pointer that is "below"
    // our current nested level
    while(first_loop != &list->tail) {
        struct node *second_loop = list->head.next;
        struct node *third_loop = list->head.next;
        while(second_loop != &list->tail) {
            struct node *third_loop = list->head.next;
            if(first_loop->num + second_loop->num == 2020) {                
                first_ans = first_loop->num * second_loop->num;
            }
            while(third_loop != &list->tail) {
                if(first_loop->num + second_loop->num + third_loop->num == 2020) {
                    second_ans = first_loop->num * second_loop->num * third_loop->num;
                    break;
                }
                third_loop = third_loop->next;
            }
            second_loop = second_loop->next;
        }
        first_loop = first_loop->next;
    }

    printf("Answer 1: %d\nAnswer 2: %d\n", first_ans, second_ans);
    return 0;
}