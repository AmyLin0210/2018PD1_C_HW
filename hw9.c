#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
			
struct prefix{
    unsigned int ip;
    unsigned char len;
    struct prefix *next;
};
typedef struct prefix Prefix;

Prefix *input(void);                    //to read all the prefixs
void print_linked_list(Prefix *head);   //test the value of link_list
void length_distribution(Prefix *head);
void segment(Prefix *seg[], int d, Prefix *head);
void group_num(Prefix *seg[], int n);
void search(Prefix *head, FILE *input);
Prefix *prefix_insert(Prefix *head);
Prefix *prefix_delete(Prefix *head);

int main(int argc, char *argv[]){

    int n, d = atoi(argv[1]);
    int n1 = 1;
    for(n = 0; n < d; n++)
        n1 *= 2;
    n1 = n1+1;
    
    FILE *input1, *input2, *input3;
    input1 = fopen("input1", "w");
    input2 = fopen("input2", "w");
    input3 = fopen("input3", "w");

    Prefix *head;
    Prefix *seg[n1];

    head = input();             //link all the prefix in routing_table  
    search(head, input1);

    length_distribution(head);  //read how many prefix in routing_table

    //segment(seg, d, head);    //divide into  group

    //group_num(seg, n1);

    head = prefix_insert(head);
    search(head, input2);
    
    head = prefix_delete(head);
    search(head, input3);

    
    return 0;
}

Prefix *input(void){

    FILE *ifp;
    ifp = fopen("routing_table.txt","r"); //read routing_table file

    Prefix *newnode, *tempnode;
    Prefix *head;
    unsigned int  i, ans = 0, n = 0;
    int  count = 3;
    char a[50];
    char *temp = a;
    
    while((fgets(a, 50, ifp)) != NULL)  //read the prefix in the file 
    {
        newnode = (Prefix*)malloc(sizeof(Prefix));
        tempnode = head;
        temp = a;
        temp = strtok(temp, ".");   
        while(temp != NULL && count > 0){
            i = atoi(temp);
            ans = ans | (i << (count*8));  //use bitwise OR to store the ip
            --count;
            if(count > 0)
            temp = strtok(NULL, ".");
        }
        temp = strtok(NULL, "/");
        i = atoi(temp);
        ans = ans | i;
        newnode->ip = ans;

        temp = strtok(NULL, "/");
        if(temp == NULL)
            i = 32;
        else
            i = atoi(temp);
        newnode->len = i;

        if(tempnode == NULL)
            head = newnode;
        else{
            while(tempnode->next != NULL)
                tempnode = tempnode->next;
            tempnode->next = newnode;
        }
        count = 3;     //reset
        ans = 0;
        n++;
    }
    printf("%d\n", n);
    
    return(head);
}

void length_distribution(Prefix *head){

    int count, num[35] = {0};
    FILE *ofp;
    ofp = fopen("length_distribution", "w");

    while(head != NULL){
        num[head->len]++;
        head = head->next;
    }
    
    for(count = 0; count <= 32; count++)
        fprintf(ofp, "%d \n", num[count]);
    
    fclose(ofp);
}

void segment(Prefix *seg[], int d, Prefix *head){
    
    unsigned int a = 1, n, k, i;
    int test = 0;
    for(n = 0; n < d; n++)
        a *= 2;

    Prefix *newnode;   
    Prefix *tempnode;

    //initialize
    for(n = 0; n <= a; n++)
        seg[n] = NULL;
    
    while(head != NULL){
        if(head->len < d)
        {
            newnode = (Prefix*)malloc(sizeof(Prefix));
            tempnode = seg[a];
            newnode->ip = head->ip;
            newnode->len = head->len;
            if(tempnode == NULL)
                seg[a] = newnode;
            else{
                while(tempnode->next != NULL)
                    tempnode = tempnode->next;
                tempnode->next = newnode;
            }
            printf("%d success\n", a);
        }
        else
        {
            //前d碼對應到的數字
            k = head->ip;
            k = k >> (32-d);
            
            //linklist
            newnode = (Prefix *)malloc(sizeof(Prefix));
            tempnode = seg[k];
            newnode->ip = head->ip;
            newnode->len = head->len;
            if(tempnode == NULL)
                seg[k] = newnode;
            else{
                while(tempnode->next != NULL)
                    tempnode = tempnode->next;
                tempnode->next = newnode;
            }
            printf("%d success\n", k);
        }
        head = head->next;
    }
    
    
    return;
}

void group_num(Prefix *seg[], int n){
    int m, count;
    for(m = 0; m <= n; m++){
        count = 0;
        while(seg[m] != NULL){
            seg[m] = seg[m]->next;
            ++count;
        }
        printf("%d\n", count);
    }
}

Prefix *prefix_insert(Prefix *head){

    Prefix *originnode = head;
    Prefix *newnode;
    FILE *ifp;
    ifp = fopen("inserted_prefixes.txt", "r");
    char a[50], *temp;
    unsigned int count = 3, insert_ip = 0, insert_len, i;

    while((fgets(a, 50, ifp)) != NULL)
    {
        // read the ip in the file
        temp = a;
        temp = strtok(temp, ".");   
        while(temp != NULL && count > 0){
            i = atoi(temp);
            insert_ip = insert_ip | (i << (count*8));  //use bitwise OR to store the ip
            --count;
            if(count > 0)
                temp = strtok(NULL, ".");
        }
        temp = strtok(NULL, "/");
        i = atoi(temp);
        insert_ip = insert_ip | i;
        
        temp = strtok(NULL, "/");
        if(temp == NULL)
            i = 32;
        else
            i = atoi(temp);
        insert_len = i;
    
        newnode = (Prefix*)malloc(sizeof(Prefix));
        newnode->ip = insert_ip;
        newnode->len = insert_len;

        if(insert_ip > head->ip){
            newnode->next = head;
            head = newnode;
            originnode = head;
        }
        else{
            while(head->next != NULL && head->next->ip < insert_ip)
                head = head->next;
            if(head->ip != insert_ip){
                newnode->next = head->next;
                head->next = newnode;
            }
        }
        
        head = originnode;
        count = 3;            //reset
        insert_ip = 0;
    }

    return head;
}

Prefix *prefix_delete(Prefix *head){

    Prefix *originnode = head;
    Prefix *newnode;
    FILE *ifp;
    ifp = fopen("deleted_prefixes.txt", "r");
    char a[50], *temp;
    unsigned int count = 3, insert_ip = 0, insert_len, i;
    
    while((fgets(a, 50, ifp)) != NULL)
    {
        // read the ip in the file
        temp = a;
        temp = strtok(temp, ".");   
        while(temp != NULL && count > 0){
            i = atoi(temp);
            insert_ip = insert_ip | (i << (count*8));  //use bitwise OR to store the ip
            --count;
            if(count > 0)
                temp = strtok(NULL, ".");
        }
        temp = strtok(NULL, "/");
        i = atoi(temp);
        insert_ip = insert_ip | i;
        
        temp = strtok(NULL, "/");
        if(temp == NULL)
            i = 32;
        else
            i = atoi(temp);
        insert_len = i;

        if((head->ip == insert_ip) && (head->len == insert_len))
            originnode = head->next;
        else{
            while(head->next != NULL){
                if((head->next->ip == insert_ip) && (head->next->len == insert_len)){
                    newnode = head->next->next;
                    head->next = newnode;
                    break;
                }
                head = head->next;
            }
        }
        count = 3;          //reset
        insert_ip = 0;
        head = originnode;
    }

    return head;
}

void search(Prefix *head, FILE *input){
    
    Prefix *originhead = head;
    FILE *ifp;
    ifp = fopen("trace_file.txt", "r");
    char a[50], *temp;
    unsigned int count = 3, i_ip = 0, i_len, i;
    unsigned int h_ip = 0, h_len;

    while((fgets(a, 50, ifp)) != NULL)
    {
        // read the ip in the file
        temp = a;
        temp = strtok(temp, ".");   
        while(temp != NULL && count > 0){
            i = atoi(temp);
            i_ip = i_ip | (i << (count*8));  //use bitwise OR to store the ip
            --count;
            if(count > 0)
                temp = strtok(NULL, ".");
        }
        temp = strtok(NULL, "/");
        i = atoi(temp);
        i_ip = i_ip | i;

        temp = strtok(NULL, "/");
        if(temp == NULL)
            i = 0;
        else
            i = atoi(temp);
        i_len = i;
    
        while(1){
            h_ip = head->ip;
            h_len = head->len;
            if((h_len >= i_len) && (h_ip>>(32-i_len)) == (i_ip>>(32-i_len))){
                    fprintf(input, "success\n");
                    break;
            }
            if((h_len < i_len) && (h_ip>>(32-h_len) == (i_ip>>(32-h_len)))){
                    fprintf(input, "success\n");
                    break;
            }
            if(head->next == NULL){
                fprintf(input,"fault\n");
                break;
            }

            head = head->next;
        }

        count = 3;               //reset
        i_ip = 0;
        head = originhead;
    }

}

void print_linked_list(Prefix *head){
    int n = 0;
    for(; head != NULL; head = head->next){
        ++n;
        //printf("len = %d\n", head->len);
    }
    printf("lenth = %d\n", n);
    return;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

