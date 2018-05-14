#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[])
{
    int x = atoi(argv[1]);
    int sum;

    sum = 3*x*x*x*x*x + 2*x*x*x*x -5*x*x*x - x*x + 7*x - 6;
    printf("%d\n", sum);
    return 0;

}

