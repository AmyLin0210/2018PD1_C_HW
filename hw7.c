#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
				
void compute(int x, ...);
int main(int argc ,char *argv[]){
    int  x = atoi(argv[1]);
    compute(x, 1 , 3); 
    compute(x, 3, 2, 4, 6); 
    compute(x, 5, 1, 2, 0, 7, 5); 
    return 0;
}
void compute(int x, ...){
    va_list ap; 
    va_start(ap, x); 
    int count, num = va_arg(ap, int);
    int a = 1, b;
    int total = 0;
    b = va_arg(ap, int);
    for(count = 0; count < num; count++){
        total += b * a;                                                                                                                                
        b = va_arg(ap, int);
        a *= x;
    }   
    printf("%d\n", total);
    va_end(ap);
};

