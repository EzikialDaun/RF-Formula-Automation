#define MAX_ADDR 80
// 저항의 갯수



int i = 0, j = 0;
// 함수에서 사용하는 ADDRESS 변수



FILE *fp;
// 파일 입출력 함수에 사용되는 포인터 함수



struct member
{
    int addr[100];
    float res[100];
};
// 행 번호와 각 행에 해당하는 저항값 구조체

struct member m[100];



typedef void (*FSM) ();
// 함수 포인터
void FUNCTIONS(FSM func){
    return func();
}

FSM boo = NULL;
