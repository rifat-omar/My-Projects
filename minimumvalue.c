#include <stdio.h>
#define SIZE 10
int main (void)
{
    int prices[SIZE] = {28, 81, 60, 83, 67, 10, 66, 97, 37,94};
    int i, minimum;
    printf("----------------\n");
    for (i = 0;i<SIZE; i++){
        printf("%-3d",i+1);
        printf("%-3d",prices[i]);
    }
    printf("---------------\n\n");
    minimum = prices[0];
    for(i = 1; i<SIZE;i++){
    if (prices[i]<minimum){
    minimum = prices[i];
        }
    }
    printf("The minimum value is %d.\n", minimum);
    return 0;
}
