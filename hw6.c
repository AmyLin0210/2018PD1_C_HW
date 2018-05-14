#include <stdio.h>
#include <stdlib.h>

void number(int n, int k, int A[n], int a, int b, FILE *ofp);
int main(int argc, char *argv[]){
    int n = atoi(argv[1]);   
    int k = atoi(argv[2]); 
    int A[n];
    int count;
			
    FILE *ofp;
    ofp = fopen("output","w");
    fprintf(ofp,"%d %d\n",n ,k);

    for(count = 0; count < n; count++){
        scanf("%d",&A[count]);
        fprintf(ofp,"%d ", A[count]); 
    }   
    fprintf(ofp,"\n\n");

    number(n, k, A, 0, 0, ofp);

    return 0;
}
void number(int n, int k, int A[n], int a, int b, FILE *ofp){
    int S[n], i;
    if(a >= k){ 
        for(i = 0; i < k; i++)
            fprintf(ofp, "%d ", A[i]);
        fprintf(ofp,"\n");
        return;
    }   

    for(i = 0; i < n; i++)
        S[i] = A[i];

    for(i = b; i <= (n - (k - a)); i++){
        S[a] = A[i];
        number(n, k, S, a + 1, i + 1, ofp);
    }   
        
};

