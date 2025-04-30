#include <stdio.h>

int factorial(int n)
{
    int i , result = 1;

    for (i = 1; i <= n ; i++)
        result *= i;
    return result;
}
int combination( int n, int r)
{
    return (factorial(n)/(factorial(r) * factorial(n-r)));
}
int get_integer (void)
{
    int n;

    printf ("Enter an integer : ");
    scanf("%d" , &n);
    return n;
}

int main(void)
{
    int a, b;
    a = get_integer ();
    b = get_integer ();

    printf("C(%d, %d) = %d \n" ,a, b, combination(a, b));
    return 0;
}
