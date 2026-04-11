#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 2
#define COL 3
#define MAX_CUPSIZE 5
#define MAX_CUSTOMER_SIZE 5

typedef struct stack{
    int *icecream_number;//아이스크림을 담는 1차원 배열
    int capacity;//최대 용량 저장
    int top;//스택에 얼마나 들어있는지 검증
}Stack;

typedef struct icecream{
    int number;//아이스크림 번호
    char name[15];//아이스크림 이름
    int stock;//재고
}Icecream;

typedef struct customer{
    //int cstmrnum;//손님 번호
    int cup_size;//주문한 컵사이즈
    int order[MAX_CUPSIZE];
    Stack *icecream_cup;//아이스크림 컵 내용물
}Customer;

typedef struct queue{
    int front, rear;//큐 검증요소
    //주문 받을 원형 큐 배열(+1은 원형큐의 특징으로 공백과 포화를 구분하기 위해 빈 칸 하나를 만들어야 해서)
    Customer* cus[MAX_CUSTOMER_SIZE+1];
}Queue;

typedef struct owner{
    int total_income;//총 수입 계산을 위한 변수
    //price per cupsize
    int priceOfCupsize[MAX_CUPSIZE];//일종의 가격표
    Queue* q;//주문 받은 손님 저장
} Owner;

Icecream*** icecream_tb;//아이스크림 테이블을 위한 3차원 배열
int reverse;//테이블 돌렸는지 검증

Icecream* create_icecream(){
    Icecream* ice = NULL;//값 초기화
    ice = (Icecream*)malloc(sizeof(Icecream));//아이스크림 구조체 사이즈 할당
    memset(ice, 0, sizeof(Icecream));//초기값 0 입력
    return ice;//아이스크림 반환
}

Icecream*** create_icecream_table(int row, int col){
    int i;//for문용 변수
    Icecream*** table;//아이스크림 테이블을 위한 3차원 배열
    //아이스크림 2차원 포인터 * row에 대한 자리 설정
    table = (Icecream***) malloc (sizeof(Icecream**) * row);
    for (i=0; i<row; i++){
        //아이스크림 1차원 포인터 * col에 대한 자리 설정
        table[i] = (Icecream**) malloc (sizeof(Icecream*) * col);
    }
    return table;//테이블 값 반환
}

void init_queue(Queue* q){
    q->front = q->rear = 0;//공백상태로 큐 초기화
}

int is_empty_queue(Queue* q){
    return(q->front == q->rear);//둘이 같은지 검증
}

int is_full_queue(Queue* q){
    return((q->rear+1)%(MAX_CUSTOMER_SIZE+1) == q->front);//rear 다음칸에 front가 있는지 검증
}

int enqueue(Queue* q, Customer* cus){
    if(is_full_queue(q)) return -1;//꽉 찼으면 -1 반환
    q->rear = (q->rear+1) % (MAX_CUSTOMER_SIZE+1);//rear 한칸 뒤로 빼주기
    q->cus[q->rear] = cus;//현 rear에 입력받은 값 넣기
    return 0;
}

Customer* dequeue(Queue* q){
    if(is_empty_queue(q)) return NULL;//없으면 -1 반환
    q->front = (q->front+1)%(MAX_CUSTOMER_SIZE+1);//front 전진
    return q->cus[q->front];//현 front값 빼주기
}

void table_init(){
    int i, j;//for문용
    int ice_num = 0;//인덱스 검증
    icecream_tb = create_icecream_table(ROW, COL);//테이블 메모리 할당
    reverse = 0;//전치 확인
    char name[15];//이름
    srand(time(NULL));//랜덤을 위한 현재시간 저장
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            Icecream* ice = create_icecream();//아이스크림 0으로 초기화
            ice->number = ++ice_num;//아이스크림 번호 지정
            ice->stock = rand() % 5;//재고 설정
            printf("진열할 아이스크림명을 입력하세요 : ");
            //입력 받기
            scanf(" %s", name);
            strcpy(ice->name, name);//아이스크림 이름 베껴오기
            icecream_tb[i][j] = ice;//현재 입력받은 내용 구조체 배열에 집어넣기
        }
    }
}

void transposed_icecream(){
    int row = ROW;//행 저장
    int col = COL;//열 저장
    int i, j;//for문
    if (reverse == 1){//뒤집을 때
        row = COL;
        //행 열 바꾸기
        col = ROW;
    }
    Icecream*** table = create_icecream_table(col, row);//기존과 같은 아이스크림 테이블 만들기
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            table[j][i] = icecream_tb[i][j];//여기서 바꿔주기
        }
    }
    free(icecream_tb);//기존 테이블 할당 해제
    icecream_tb = table;//새 테이블 불러오기

    for(i = 0; i < col; i++){//새로 출력
        for(j  = 0; j < row; j++){
            printf("[(%d)%15s]", icecream_tb[i][j]->number, icecream_tb[i][j]->name);
        }
        printf("\n");
    }
    reverse = (reverse+1)%2;//변수 전환
}

void owner_init(Owner *ice_owner){
    int i;//for문용
    for(i = 0; i < MAX_CUPSIZE; i++){
        ice_owner->priceOfCupsize[i] = (i+1)*100;//가격 설정
    }
    ice_owner->total_income = 0;//최종수익 초기화
    Queue* q = (Queue*)malloc(sizeof(Queue));//큐 동적할당
    memset(q, 0, sizeof(Queue));//값 초기화
    init_queue(q);//front, rear 초기화
    ice_owner->q = q;//ice_owner 내부로 연결
}

int is_empty(Stack* icecream_cup){
    return (icecream_cup->top == -1);
}

int is_full(Stack* icecream_cup){
    return (icecream_cup->top == (icecream_cup->capacity-1));
}

Customer* create_customer(){
    Customer* cus = (Customer *)malloc(sizeof(Customer));//손님 구조체 메모리 할당
    memset(cus, 0, sizeof(Customer));//값 초기화
    cus->icecream_cup = (Stack*)malloc(sizeof(Stack));//아이스크림 컵 스택 할당
    return cus;//손님 반환
}

void cal_sales(Owner *ice_owner, int cupsize, int penalty){
    int income = ice_owner->priceOfCupsize[cupsize-1];//수익설정
    income -= (penalty*100);//수익에서 페널티만큼 제거
    ice_owner->total_income = ice_owner->total_income + income;//이번 수익 추가
    //수익 출력
    printf("사장 : 이 번 주문으로 %d원, 총 %d원 벌었다!\n", income, ice_owner->total_income);
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

void stock_refill(Icecream* ice, Owner* ice_owner){
    ice->stock += 5;
    ice_owner->total_income -= 250;
}

void init_cup(Stack* icecream_cup){
    icecream_cup->capacity = MAX_CUPSIZE;//용량 초기세팅
    icecream_cup->top = -1;//아이스크림 탑 초기화
    //아이스크림 번호*정수 사이즈로 메모리 할당
    icecream_cup->icecream_number = (int*)malloc(icecream_cup->capacity*sizeof(int));
}

void push(int choice, Stack *icecream_cup){
    if(is_full(icecream_cup)){//꽉찼다면
        icecream_cup->capacity *= 2;//용량 두배
        icecream_cup->icecream_number = (int*)realloc(//메모리 재할당
            icecream_cup->icecream_number,
            icecream_cup->capacity*sizeof(int)
        );
    }
    icecream_cup->icecream_number[++icecream_cup->top] = choice;//top에 +1 후에 입력된 값 담기
}

int pop(Stack* icecream_cup){
    if(is_empty(icecream_cup)) return -1;//비어있다면 -1 반환
    //top안의 값 반환후 top 한칸 내림
    else return icecream_cup->icecream_number[icecream_cup->top--];
}

int delivery_order(Customer* cus){
    int i, ice_num;//for문 / 아이스크림 갯수 확인
    int penalty = 0;//실수 양

    for(i = cus->cup_size; i--; i>0){//아이스크림 하나씩 까보기
        ice_num = pop(cus->icecream_cup);//위의 아이스크림 까보기
        if(ice_num == -1){//아이스크림이 없으면
            printf("고객 : 왜 주문한 아이스크림을 안주는거야!\n");
            penalty++;//실수 하나
        }
        else{
            if((ice_num-1)==cus->order[i]){//실수 없음
                printf("고객 : 음, 맛있다!\n");//성공
            }
            else{//틀렸으면
                printf("고객 : 내가 말한건 이 맛이 아닌데...\n");
                penalty++;//실수 하나
            }
        }
    }
    if((cus->icecream_cup->top) > -1){//아이스크림을 다 깠는데도 남으면
        penalty += ((cus->icecream_cup->top)+1);//넘치는 만큼 페널티
        printf("아... 다이어트 중인데...\n");
    }
    return penalty;//페널티 반환
}

int prepare_order(Owner* ice_owner){
    Customer* cus = dequeue(ice_owner->q);//주문내역서 반환
    if(cus == NULL) return -1;//손님이 없으면 -1 반환
    Stack* icecream_cup = cus->icecream_cup;//또다른 이름 붙이기(간결한 코드)
    printf("주문 수행 시작\n");
    init_cup(icecream_cup);//컵 초기화

    int cupsize = -1;//컵 사이즈 초기화
    printf("사장 : 고객님이 요청하신 컵사이즈가 뭐였지?\n");
    scanf("%d", &cupsize);//컵 사이즈 받기

    int i, choice;//for문 / 선택한 아이스크림 저장 변수

    for(i=0; i<cupsize; i++){
        printf("사장 : 몇 번 아이스크림을 쌓아야 하지?\n");
        scanf("%d", &choice);//아이스크림 받기
        push(choice, icecream_cup);//받은 값 아이스크림에 저장
    }
    int penalty = delivery_order(cus);//아이스크림 잘 담았는지 검사
    cal_sales(ice_owner, cus->cup_size, penalty);//수익이랑 패널티 확인
    return 0;
}


int get_order(Owner* ice_owner){
    int row;//행
    int col;//열
    Customer* cus = create_customer();//손님 구조체 만들어주기
    int i;//for문용
    Sleep(1000);
    srand(time(NULL));//랜덤을 위한 시간 저장
    printf("사장 : 고객님 주문받겠습니다.\n");
    cus->cup_size = (rand() % MAX_CUPSIZE)+1;//컵사이즈 랜덤한 결정
    printf("고객 : 저 컵사이즈는 %d번으로 해주시고, 맛은 ",cus->cup_size);
    for(i = 0; i < cus->cup_size; i++){
        int ice_num = rand() % (ROW*COL);//총 개수로 나눠서 나머지
        if(reverse == 0){//뒤집혀있는지
            row = ice_num / COL;//행
            col = ice_num % COL;//열
        }
        else{
            row = ice_num % COL;//열
            col = ice_num / COL;//행
        }
        cus->order[i] = ice_num;//i번째 아이스크림 저장
        //printf("%d번 %s, ", icecream_tb[row][col]->number, icecream_tb[row][col]->name);
        printf("%s, ", icecream_tb[row][col]->name);
    }
    printf("이 순서로 주세요\n");
    int ret = enqueue(ice_owner->q, cus);//큐 진행
    if(ret == -1){//꽉 차면
        free(cus);//방금 저장된 메모리 해제
        return -1;//되돌리기
    }
    return 0;
    //int penalty = delivery_order(cus);
    //cal_sales(ice_owner, cus->cup_size, penalty);
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
    int k,l;//for문
    table_init();//테이블 생성
    for(k = 0; k < 2; k++){//테이블 출력
        for(l = 0; l < 3; l++){
            printf("[%d: %15s]", icecream_tb[k][l]->number, icecream_tb[k][l]->name);
        }
        printf("\n");
    }
    Owner ice_owner;//주인 생성
    owner_init(&ice_owner);//주인 초기화
    int i = 0;//for문용
    for(i=0; i<MAX_CUSTOMER_SIZE+1; i++){//주문 받는 반복(+1은 포화상태 확인용)
        Sleep(1000);
        //주문 받고 만약 포화라면 오류메세지 출력
        if(get_order(&ice_owner)==-1) printf("사장 : 오늘 장사는 마감했습니다. 죄송합니다.\n");
    }
    for(i=0; i<MAX_CUSTOMER_SIZE+1; i++){//주문 받는 반복(+1은 공백상태 확인용)
        Sleep(1000);
        //주문 치고 만약 공백이라면 오류메세지 출력
        if(prepare_order(&ice_owner)==-1) printf("사장 : 주문이 끝났다!\n");
    }
    //get_order(&ice_owner);
    printf("단속원 떴다!\n");
    transposed_icecream();//전치
    //get_order(&ice_owner);
    printf("단속원 갔다!\n");
    transposed_icecream();//전치
    //get_order(&ice_owner);

    printf("최종 수익: %d\n", ice_owner.total_income);//최종수익 출력

    return 0;
}