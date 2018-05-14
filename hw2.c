#include <stdio.h>

int main(int argc, char * argv[])
{
    FILE * ifp;
    FILE * ofp;

    /*開啟檔案*/
    ifp = fopen( argv[1], "r");
    ofp = fopen( argv[2], "w");

    int c;
    int s[128] = {0};                           
    int n;

    /*讀檔案並計數*/
    while((c = fgetc(ifp)) != EOF){
        s[c]++;
    }

    /*寫入共有多少word*/
    /*依定義，word為被space隔開的字串，
      但每一行中的最後一個word後面會換行而沒有space，
      故判斷word的數目會等於spacd + new_line的數目*/

    fprintf(ofp, "%d\n",s[32] + s[10]);

    /*寫入其他字元共幾個*/
    for(n = 0; n <128; n++){
        fprintf( ofp, "%d\n",s[n]);
    }
    
    /*關閉檔案*/
    fclose(ifp);
    fclose(ofp);

    return 0;
}     

