#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    //포인터
    //&f = f의 주소
    int num = 10;
    int *pnum = &num;//int* = 주소를 저장(끝에는 정수가 있음)

    printf("%d %d\n", num, *pnum);//%d는 정수값 반환
    printf("%p, %p\n", &num, pnum);//%p는 주소값 반환

    *pnum = 20;
    printf("%d\n", *pnum);
    printf("\n");

    //이중 포인터
    int i = 10;//i 값 할당
    int *p = &i;//p에 i주소 할당
    int **pp = &p;//pp에 p주소 할당

    printf("%d %d %d\n", i, *p, **pp);
    printf("%p %p %p\n", &i, p, *pp);
    printf("%p %p %p\n", i, p, pp);
    printf("\n");

    //배열 포인터
    int a[5], *ap=NULL;
    ap = a;//배열은 건들면 주소가 튀어나오므로 &를 붙이지 않음
    ap[3] = 20;
    printf("%d %d\n", ap[3], a[3]);//포인터 ap와 배열 a가 같은 역할을 하게 됨

    char array_name[8] = {0};
    char *point_name = array_name;

    sprintf(point_name, "%s", "Game");

    printf("%c %c %c\n", *point_name, *(point_name+1), *(point_name+2));
    printf("%c %c %c\n", array_name[0], array_name[1], array_name[2]);
    printf("%p %p", array_name, point_name);
    printf("\n");
    //구조체 포인터
    typedef struct{ //다항식 구조체 선언
        int degree;
        float coef[5];
    } Polynomial;

    Polynomial st; //다항식 구조체 변수 st 선언
    Polynomial* sp=NULL;//다항식 포인터 sp선언
    sp = &st;//포인터 sp가 구조체 st를 가리킴
    st.degree = 5;//구조체 st를 통한 멤버 접근: .연산자 사용
    sp->coef[0] = 1;//포인터 sp를 통한 멤버 접근: ->연산자 사용
    printf("%d %d\n", st.degree, st.coef[0]);
    printf("%d %d\n", sp->degree, sp->coef[0]);
    printf("\n");

    //동적 메모리
    int* data = NULL;//할당할 메모리 주소 저장할 포인터
    data = (int*)malloc(sizeof(int)*100);//동적 메모리 할당
    //(int*) = 정수형 포인터로 자료형 강제
    //sizeof(int) = int 크기만큼의 바이트
    *data = 10;//data[0] = 10이랑 같음
    data[3] = 30;//배열과 동일하게 data[0] ~ data[99] 사용가능
    data[99] = 20;
    data = (int*)realloc(data, sizeof(int)*200);
    //기존 data를 200사이즈로 재할당
    data[199] = 200;
    printf("%d %d %d %d %d\n", data[0], *data, data[3], data[99], data[199]);
    free(data);//동적 메모리 반납
    printf("\n");
}