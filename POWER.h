void POWER_CAL(){
    float DC, CURRENT, POWER, EFF, WATT;

    printf("**************************\n");
    printf("*  AMP ���� ȿ�� ����  *\n");
    printf("*  RF ���� / ���� ����   *\n");
    printf("**************************\n\n");

    printf("�巹�� �ΰ� ����(V)�� �Է��Ͻÿ�. : ");
    scanf("%f", &DC);
    printf("����(A) ���� �Է��Ͻÿ�. : ");
    scanf("%f", &CURRENT);
    printf("���(dBm)�� �Է��Ͻÿ�. : ");
    scanf("%f", &POWER);

    if(DC <= 0 || CURRENT <= 0 || POWER <= 0)
        printf("�ùٸ� ���� �Է��Ͻÿ�.\n");
    else{
        WATT = pow(10, ((POWER - 30) / 10));
        EFF = WATT / (DC * CURRENT) * 100;
        printf("\n");

        printf("���� ȿ���� %.2f���Դϴ�.\n", EFF);
    }
}



void PAE_CAL(){
    float DC, CURRENT, INPUT, POWER, EFF, IWATT, OWATT;

    printf("**********************************\n");
    printf("*   AMP ���� �ΰ� ȿ�� ����    *\n");
    printf("*  RF �Է� ������ �� ������ ���� *\n");
    printf("**********************************\n\n");

    printf("�巹�� �ΰ� ����(V)�� �Է��Ͻÿ�. : ");
    scanf("%f", &DC);
    printf("����(A) ���� �Է��Ͻÿ�. : ");
    scanf("%f", &CURRENT);
    printf("�Է� ����(dBm)�� �Է��Ͻÿ�. : ");
    scanf("%f", &INPUT);
    printf("��� ����(dBm)�� �Է��Ͻÿ�. : ");
    scanf("%f", &POWER);

    if(DC <= 0 || CURRENT <= 0 || INPUT < 0 || POWER <= 0)
        printf("�ùٸ� ���� �Է��Ͻÿ�.\n");
    else{
        IWATT = pow(10, ((INPUT - 30) / 10));
        OWATT = pow(10, ((POWER - 30) / 10));
        EFF = (OWATT - IWATT) / (DC * CURRENT) * 100;
        printf("\n");

        printf("���� �ΰ� ȿ���� %.2f���Դϴ�.\n", EFF);
    }
}
