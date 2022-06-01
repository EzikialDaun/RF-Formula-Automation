void POWER_CAL(){
    float DC, CURRENT, POWER, EFF, WATT;

    printf("**************************\n");
    printf("*  AMP 전력 효율 계산기  *\n");
    printf("*  RF 전력 / 직류 전력   *\n");
    printf("**************************\n\n");

    printf("드레인 인가 전압(V)을 입력하시오. : ");
    scanf("%f", &DC);
    printf("전류(A) 값을 입력하시오. : ");
    scanf("%f", &CURRENT);
    printf("출력(dBm)을 입력하시오. : ");
    scanf("%f", &POWER);

    if(DC <= 0 || CURRENT <= 0 || POWER <= 0)
        printf("올바른 값을 입력하시오.\n");
    else{
        WATT = pow(10, ((POWER - 30) / 10));
        EFF = WATT / (DC * CURRENT) * 100;
        printf("\n");

        printf("전력 효율은 %.2f％입니다.\n", EFF);
    }
}



void PAE_CAL(){
    float DC, CURRENT, INPUT, POWER, EFF, IWATT, OWATT;

    printf("**********************************\n");
    printf("*   AMP 전력 부가 효율 계산기    *\n");
    printf("*  RF 입력 성분을 뺀 순수한 전력 *\n");
    printf("**********************************\n\n");

    printf("드레인 인가 전압(V)을 입력하시오. : ");
    scanf("%f", &DC);
    printf("전류(A) 값을 입력하시오. : ");
    scanf("%f", &CURRENT);
    printf("입력 전력(dBm)을 입력하시오. : ");
    scanf("%f", &INPUT);
    printf("출력 전력(dBm)을 입력하시오. : ");
    scanf("%f", &POWER);

    if(DC <= 0 || CURRENT <= 0 || INPUT < 0 || POWER <= 0)
        printf("올바른 값을 입력하시오.\n");
    else{
        IWATT = pow(10, ((INPUT - 30) / 10));
        OWATT = pow(10, ((POWER - 30) / 10));
        EFF = (OWATT - IWATT) / (DC * CURRENT) * 100;
        printf("\n");

        printf("전력 부가 효율은 %.2f％입니다.\n", EFF);
    }
}
