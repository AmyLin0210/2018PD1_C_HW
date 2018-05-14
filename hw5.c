#include <stdio.h>    
#include <stdlib.h>
#include <time.h>
void Random   (int i1, int M1[][i1], int M2[][i1]);
void keyboard (int i1, int M1[][i1], int M2[][i1]);
void Mul      (int i1, int M1[][i1], int M2[][i1], int R[][i1]);
void Add      (int i1, int M1[][i1], int M2[][i1], int R[][i1]);
int main(int argc, char*argv[]){
	
    int N    = atoi(argv[1]); /*幾乘幾矩陣*/
    int AorM = atoi(argv[2]); /* 0 for Add ; 1 for Multiplication*/
    int Ran  = atoi(argv[3]); /* 0 for random ;1 for keyboard*/
    int R[N][N],M1[N][N],M2[N][N];    
    int random, x, y;

    FILE *ofp;
    ofp = fopen("output","w");

    srand(time(NULL));
    
    /*判斷矩陣隨機與否*/
    switch(Ran){
        case 0:
            Random (N, M1, M2);
            break;
        case 1:
            keyboard(N, M1, M2);    
    }   
    for(y = 0;y < N; y++){
        for(x = 0; x < N; x++)
            fprintf(ofp, "%d ", M1[y][x]);
        fprintf(ofp,"\n");
    }   
    fprintf(ofp,"\n");

    for(y = 0;y < N; y++){
        for(x = 0; x < N; x++)
            fprintf(ofp, "%d ", M2[y][x]);
        fprintf(ofp,"\n");                                                                                                                             
    }   
    fprintf(ofp,"\n");

    /*判斷矩陣相加相乘*/
    switch(AorM){
      case 0:
        Add(N, M1, M2, R); 
        break;
      case 1:
        Mul(N, M1, M2, R); 
      break;
   }

    /*將結果放入output*/
    for(y = 0; y < N; y++){
        for(x = 0; x < N; x++)
            fprintf(ofp,"%d ", R[y][x]);
        fputc('\n', ofp);
    }
    return 0;
}

/*隨機矩陣的產生*/
void Random (int i1, int M1[][i1], int M2[][i1]){
    int x, y, num;

    for(y = 0; y < i1; y ++)
        for(x = 0; x < i1; x++)
            M1[y][x] = (rand()%20)+1;

    for(y = 0; y < i1; y ++)
        for(x = 0; x < i1; x++)
            M2[y][x] = (rand()%20)+1;
};

/*由鍵盤輸入矩陣*/
void keyboard (int i1, int M1[][i1], int M2[][i1]){
    int x, y, num;
    for(y = 0; y < i1; y ++)
        for(x = 0; x < i1; x++)
            scanf("%d",&M1[y][x]);

    for(y = 0; y < i1; y ++)
        for(x = 0; x < i1; x++)
            scanf("%d",&M2[y][x]);
    
};

/*矩陣相乘*/
void Mul  (int i1, int M1[][i1], int M2[][i1], int R[][i1]){
    int x, y, n, m, sum = 0;
    for(y = 0; y < i1; y++){
        for(x = 0; x < i1; x++){
            for(n = 0; n < i1; n++)
                sum += M1[y][n] * M2[n][x];
            R[y][x] = sum;
            sum = 0;
        }
    }
};

/*矩陣相加*/
void Add  (int i1, int M1[][i1], int M2[][i1], int R[][i1]){
    int x, y, sum;
    for(y = 0; y < i1; y++)
        for(x = 0; x < i1; x++)
            R[y][x] = M1[y][x] + M2[y][x];
    
};  

