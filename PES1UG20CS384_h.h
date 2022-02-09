#include <stdio.h>
#include <stdlib.h>
// #include "PES1UG20CS384_C.c"
// #include "PES1UG20CS384_F.c"

struct node
{
    int xpos;
    int ypos;
    struct node *right;
    struct node *down;
};

struct node *ReadMap(int y_dimensions, int arr[][y_dimensions], int i, int j, int x_dimensions);
void navigate(struct node *head, int xend, int yend, struct node **path_stk, struct node **diversion_stack, FILE *fpout);
struct node *move_to_diversion(struct node *robo, struct node **diversion_stack, struct node **path_stk, int *top_diversion, int *top_path);
struct node *dequeue(struct node **);
void push(struct node **, int *top, struct node *);
struct node *pop(struct node **, int *top);
struct node *peek(struct node **, int top);