#define MAX_ADDR 80
// ������ ����



int i = 0, j = 0;
// �Լ����� ����ϴ� ADDRESS ����



FILE *fp;
// ���� ����� �Լ��� ���Ǵ� ������ �Լ�



struct member
{
    int addr[100];
    float res[100];
};
// �� ��ȣ�� �� �࿡ �ش��ϴ� ���װ� ����ü

struct member m[100];



typedef void (*FSM) ();
// �Լ� ������
void FUNCTIONS(FSM func){
    return func();
}

FSM boo = NULL;
