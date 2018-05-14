#include <stdio.h>
#include <stdlib.h>
	
typedef double(*Fcn)(double x, int n); 
double power(double x, int n); 
double multiply(double x, int n); 
double divide(double x, int n); 
double powerpower(Fcn f, double x, int n, int m); 

int main(int argc, char *argv[]){
    double x = atof(argv[2]);
    int    n = atoi(argv[3]);
    int    m = atoi(argv[4]);
    Fcn f;

    switch(atoi(argv[1])){
        case 0:
            f = power;
            printf("%f\n", powerpower(f, x, n, m));
            break;
        case 1:
            f = multiply;
            printf("%f\n", powerpower(f, x, n, m));
            break;
        case 2:
            f = divide;
            printf("%.6f\n", powerpower(f, x, n, m));
            break;
    }
    return 0;
}

double power(double x, int n){ 
    int count; 
    double ans = 1;
    for(count = 0; count < n; count ++) 
        ans *= x;
    return ans;
};

double multiply(double x, int n){ 
    return x * n;
};

double divide(double x, int n){ 
    return x / n;  
}

double powerpower(Fcn f, double x, int n, int m){ 
    int    count;
    double ans = 1, a = f(x, n); 
    for(count = 0; count < m; count++)
        ans *= a;
    return ans;
}

