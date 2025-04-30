#include <stdio.h>

int get_integer ()
{

    int value;

    printf("Enter an integer:");
    scanf("%d" , &value);

    return value;
}

int add(int x, int y)
{
    return x + y;
}
int main (void)
{
    int x = get_integer();
    int y= get_integer();

    int sum = add(x,y);
    printf("The sum of the two numbers is %d . \n" , sum);
    return 0;
}
