#include <stdio.h>
int max(int x , int y)
{
    if (x > y)
        return x;
    else
        return y;
}
int main (void)
{
    int x, y, larger;

    printf ("Enter two integers :");
    scanf("%d%d",&x,&y);

    larger = max(x,y);
    printf("The larger value is %d . \n" , larger);
    return 0;
}
