#include <stdio.h>
#define STUDENTS 10

int main (void)
{
    int scores[STUDENTS];
    int sum = 0;
    int i , average;

    for (i = 0; i<STUDENTS;i++)
    {
        printf("Enter student's grades:");
        scanf("%d",&scores[i]);

    }
    for(i=0; i<STUDENTS;i++)
        sum += scores[i];

    average = sum / STUDENTS;
    printf ("Grade average = %d\n", average);

    return 0;
}
