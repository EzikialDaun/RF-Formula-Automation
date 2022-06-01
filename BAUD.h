void BAUD_CAL(){
    float FRE, BPS, BAUD;

    printf("********************************************\n");
    printf("*    USART 시리얼 통신 BAUD RATE 계산기    *\n");
    printf("* 시스템 클럭 주파수(MHz) / 통신 속도(bps) *\n");
    printf("********************************************\n\n");

    printf("MCU의 시스템 클럭 주파수(MHz)를 입력하시오. : ");
    scanf("%f", &FRE);
    printf("통신 속도(bps) 값을 입력하시오. : ");
    scanf("%f", &BPS);

    if(FRE <= 0 || BPS <= 0)
        printf("올바른 값을 입력하시오.\n");
    else{
        BAUD = (FRE * 1000000) / BPS;
        printf("\n");

        printf("BAUD RATE는 %.0f입니다.\n", BAUD);
    }
}
