#include <stdio.h>
#include <stdlib.h>
#include "PES1UG20CS384_h.h"
// #include "PES1UG20CS384_C.c"

void navigate(struct node *robo, int xend, int yend, struct node **path_stack, struct node **diversion_stack, FILE *fpout)
{
    int top_diversion = -1;
    int top_path = -1;
    //till robo reaches end
    while (robo->xpos != xend || robo->ypos != yend)
    {
        //x and y coords set to -1 if at deadend and no prev junction found
        if (robo->xpos == -1)
        {
            printf("No possible path\n");
            fprintf(fpout, "%d\n", -1);
            break;
        }
        else
        {
            //mapping position of robo before moving
            push(path_stack, &top_path, robo);
            //Check for walls on the right(NULL)
            if (robo->right != NULL)
            {
                if (robo->down != NULL)
                {
                    //mapping position of junction if move_to_diversion needed
                    push(diversion_stack, &top_diversion, robo);
                }
                //move robo right
                robo = robo->right;
            }
            //check for walls below(NULL)
            else if (robo->down != NULL)
            {
                //move robo down
                robo = robo->down;
            }
            //deadend condition
            else
            {
                //move_to_diversion to last stored junction node if exists
                robo = move_to_diversion(robo, diversion_stack, path_stack, &top_diversion, &top_path);
            }
        }
    }

    //printing output to screen and output file
    if (robo->xpos != -1)
    {
        printf("\nPath the robo follows : \n");
        for (int i = 0; i <= top_path; i++)
        {
            printf("(%d , %d) \n", (path_stack[i])->xpos, (path_stack[i])->ypos);
            fprintf(fpout, "%d %d\n", (path_stack[i])->xpos, (path_stack[i])->ypos);
        }
        printf("(%d , %d) \n", xend, yend);
        fprintf(fpout, "%d %d\n", xend, yend);
    }
}

struct node *ReadMap(int n, int arr[][n], int i, int j, int m)
{
    // Return if i or j is out of bounds
    if (i > n - 1 || j > m - 1)
        return NULL;
    // Create a new node for current i and j if it is 0
    // Recursively allocate its down and right pointers
    if (arr[i][j] == 0)
    {
        struct node *temp;
        temp = (struct node *)malloc(sizeof(struct node));
        temp->xpos = i;
        temp->ypos = j;
        temp->right = ReadMap(n, arr, i, j + 1, m);
        temp->down = ReadMap(n, arr, i + 1, j, m);
        return temp;
    }
    // On seeing a 1 or wall
    else
        return NULL;
}

void push(struct node **stk, int *top, struct node *element)
{
    (*top)++;
    stk[*top] = element;
}

struct node *pop(struct node **stk, int *top)
{
    struct node *temp = stk[*top];
    *top = *top - 1;
    return temp;
}

struct node *peek(struct node **stk, int top)
{
    struct node *temp = stk[top];
    return temp;
}

struct node *move_to_diversion(struct node *robo, struct node **diversion_stack, struct node **path_stk, int *top_diversion, int *top_path)
{
    // junction stack empty, no way to destination
    if (*top_diversion == -1)
    {
        robo->xpos = -1;
        robo->ypos = -1;
        return robo;
    }
    else
    {
        // get last junction node
        struct node *prev_diversion = pop(diversion_stack, top_diversion);
        // replace deadend path entrance with wall
        prev_diversion->right = NULL;
        // remove unwanted coordinates from path uptil junction
        while ((peek(path_stk, *top_path))->xpos != prev_diversion->xpos || (peek(path_stk, *top_path))->ypos != prev_diversion->ypos)
        {
            pop(path_stk, top_path);
        }
        pop(path_stk, top_path);

        return prev_diversion;
    }
}