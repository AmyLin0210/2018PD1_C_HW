#include <stdio.h>                                                              
					
int main(int argc, char*argv[]){    
    int i[99][99] = {0};
    int s, n, x, y, a, b;
    FILE * ofp;
    ofp = fopen("output_a", "w");

    scanf("%d", &s);
    x = 0;
    y = (s-1)/2;
    i[x][y] = 1;

    for(n = 2; n <= s*s; ++n){

        a = x;
        b = y;
        --a;
        ++b;
        if(a < 0)  a = s-1;
        if(b >= s) b = 0;

        if(i[a][b] != 0){
            a = x;
            b = y;
            do{ 
                ++a;
                if(a >= s) a = 0;
            } while(i[a][b] != 0);
        }

        i[a][b] = n;

        x = a;
        y = b;
    }

    for(x = 0; x < s;x++){
        for(y = 0; y < s; y++)
            fprintf(ofp, "%d ", i[x][y]);
        fprintf(ofp, "\n");
    }

    fclose(ofp);

    return 0;
}   

