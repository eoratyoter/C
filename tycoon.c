#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 2
#define COL 3
#define MAX_CUPSIZE 5
int ice_num = 0;


typedef struct icecream{
    int number;
    char name[15];
    int stock;
}Icecream;

Icecream*** icecream_tb;
int reverse;

typedef struct customer{
    int cstmrnum;
    int cup_size;
    int order[5];
}Customer;

typedef struct owner{
    int total_income;
    //price per cupsize
    int priceOfCupsize[5];
} Owner;

Icecream* create_icecream(){
    Icecream* ice = NULL;
    ice = (Icecream*)malloc(sizeof(Icecream));
    memset(ice, 0, sizeof(Icecream));
    return ice;
}
Icecream*** create_icecream_table(int row, int col){
    int i;
    Icecream*** table;
    table = (Icecream***) malloc (sizeof(Icecream**) * row);
    for (i=0; i<row; i++){
        table[i] = (Icecream**) malloc (sizeof(Icecream*) * col);
    }
    return table;
}

void table_init(){
    int i, j;
    int ice_num = 0;
    icecream_tb = create_icecream_table(ROW, COL);
    reverse = 0;
    char name[15];
    srand(time(NULL));
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            Icecream* ice = create_icecream();
            ice->number = ++ice_num;
            ice->stock = rand() % 5;
            printf("진열할 아이스크림명을 입력하세요 : ");
            scanf(" %s", name);
            strcpy(ice->name, name);
            icecream_tb[i][j] = ice;
        }
    }
}

void transposed_icecream(){
    int row = ROW;
    int col = COL;
    int i, j;
    if (reverse == 1){
        row = COL;
        col = ROW;
    }
    Icecream*** table = create_icecream_table(col, row);
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            table[j][i] = icecream_tb[i][j];
        }
    }
    free(icecream_tb);
    icecream_tb = table;

    for(i = 0; i < col; i++){
        for(j  = 0; j < row; j++){
            printf("[(%d)%15s]", icecream_tb[i][j]->number, icecream_tb[i][j]->name);
        }
        printf("\n");
    }
    reverse = (reverse+1)%2;
}

void owner_init(Owner *ice_owner){
    int i;
    for(i = 0; i < 5; i++){
        ice_owner->priceOfCupsize[i] = (i+1)*100;
    }
    ice_owner->total_income = 0;
}

Customer* create_customer(){
    Customer* cus = (Customer *)malloc(sizeof(Customer));
    memset(cus, 0, sizeof(Customer));
    return cus;
}

void cal_sales(Owner *ice_owner, int cupsize){
    int income = ice_owner->priceOfCupsize[cupsize-1];
    ice_owner->total_income = ice_owner->total_income + income;
}
/*void table_print() {
    int i,j;
    char print_temp[512];
    FILE *fp= fopen("./icecream_ASC.txt","r");
    if(fp== NULL){   
        printf("file load failed");
    }   
    while(fgets(print_temp, sizeof(print_temp),fp) ){   
    printf("%s",print_temp);
    }   
    puts("");
    fclose(fp);
    for (i= 0; i< 2; i++) {   
        for (j = 0; j < 2; j++){   
            printf("[%15s]",icecream_tb[i][j]);
        }   
        printf("\n");
    }
}*/

void get_order(Owner* ice_owner){
    int row;
    int col;
    Customer* cus = create_customer();
    int i;
    Sleep(1000);
    srand(time(NULL));
    printf("사장 : 고객님 주문받겠습니다.\n");
    cus->cup_size = (rand() % MAX_CUPSIZE)+1;
    printf("고객 : 저 컵사이즈는 %d번으로 해주시고, 맛은 ",cus->cup_size);
    for(i = 0; i < cus->cup_size; i++){
        int ice_num = rand() % (ROW*COL);
        if(reverse == 0){
            row = ice_num / COL;
            col = ice_num % COL;
        }
        else{
            row = ice_num % COL;
            col = ice_num / COL;
        }
        cus->order[i] = ice_num;
        printf("%d번 %s, ", icecream_tb[row][col]->number, icecream_tb[row][col]->name);
    }
    printf("주세요\n");
    cal_sales(ice_owner, cus->cup_size);
}

/*void orderprint(Customer x){
    int i = 0;
    printf("%d번손님 %d번 컵사이즈로 다음과 같이 주문하셨습니다. ", x.cstmrnum, x.cup_size);
    for (i = 0; i < x.cup_size; i++){
        printf(" %d번", x.order[i]);
    }
    printf(". 잠시만 기다려 주세요.\n");
}*/

int main(){
    int k,l;
    table_init();
    for(k = 0; k < 2; k++){
        for(l = 0; l < 3; l++){
            printf("[%d: %15s]", icecream_tb[k][l]->number, icecream_tb[k][l]->name);
        }
        printf("\n");
    }
    Owner ice_owner;
    owner_init(&ice_owner);
    int i = 0;

    get_order(&ice_owner);
    printf("단속원 떴다!\n");
    transposed_icecream();
    get_order(&ice_owner);
    printf("단속원 갔다!\n");
    transposed_icecream();
    get_order(&ice_owner);

    printf("최종 수익: %d\n", ice_owner.total_income);

    return 0;
}