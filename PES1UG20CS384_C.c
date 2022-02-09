#include <stdio.h>
#include <stdlib.h>
#include "PES1UG20CS384_h.h"
// #include "PES1UG20CS384_F.c"

int main()
{

    //initialising file pointers
    FILE *fp, *fpout;
    fp = fopen("input.txt", "r");
    fpout = fopen("output.txt", "w");
    if (!fp || !fpout)
    {
        printf("Error in reading the files");
        return -1;
    }
    int xend, yend, xbeg, ybeg, i = 0, j = 0;
    struct node *diversion_stack[100];
    struct node *path_stack[100];
    struct node *head;

    int countx = 0;
    int county = 0;

    // This for loop and while loop will give us the dimensions of array
    for (int a = 0; a < 8; a++)
    {
        fgetc(fp);
    }

    int ch = fgetc(fp);
    while (ch != EOF)
    {
        if (ch == '0')
        {
            // printf("%c ", ch);
            county++;
            ch = fgetc(fp);
        }
        else if (ch == '1')
        {
            // printf("%c ", ch);
            county++;
            ch = fgetc(fp);
        }
        else if (ch == '\n')
        {
            countx++;
            county = 0;
            ch = fgetc(fp);
            // printf("\n");
        }
        else
        {
            ch = fgetc(fp);
        }
    }
    // printf("\ncountx : %d\ncounty : %d\n", countx, county);

    // This will reset the file pointer back to the start of the file
    fseek(fp, 0, SEEK_SET);

    //getting start and end points
    xbeg = (int)(fgetc(fp)) - 48;
    fgetc(fp);
    ybeg = (int)(fgetc(fp)) - 48;
    fgetc(fp);
    xend = (int)(fgetc(fp)) - 48;
    fgetc(fp);
    yend = (int)(fgetc(fp)) - 48;
    fgetc(fp);

    //initialising atrray for mapping
    //MAX 10x10 array, otherwise needs reconfiguration

    int arr[10][10];
    int c = fgetc(fp);
    while (c != EOF)
    {
        if (c == '0')
        {
            // printf("%c ", c);
            arr[i][j] = 0;
            j++;
            c = fgetc(fp);
        }
        else if (c == '1')
        {
            // printf("%c ", c);
            arr[i][j] = 1;
            j++;
            c = fgetc(fp);
        }
        else if (c == '\n')
        {
            i++;
            j = 0;
            c = fgetc(fp);
            // printf("\n");
        }
        else
        {
            c = fgetc(fp);
        }
    }
    printf("\n");
    //creating map
    head = ReadMap(county, arr, xbeg, ybeg, countx + 1); //y_dimensions, arr, xbeg, ybeg, x_dimensions
    //main function
    navigate(head, xend, yend, path_stack, diversion_stack, fpout);
    return 0;
}