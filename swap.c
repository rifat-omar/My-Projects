#include <stdio.h>
void swap(int x, int y)
{
    int tmp;
    printf("x=%dy=%d\n",x,y);

    tmp = x;
    x = y;
    y = tmp;

    printf("x=%dy=%d\n",x,y);
}
int main(void)
{
    int a = 100, b = 200;
    printf("a=%db=%d\n",a,b);

    swap(a,b);

    printf("a=%db=%d\n",a,b);
}
