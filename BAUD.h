void BAUD_CAL(){
    float FRE, BPS, BAUD;

    printf("********************************************\n");
    printf("*    USART �ø��� ��� BAUD RATE ����    *\n");
    printf("* �ý��� Ŭ�� ���ļ�(MHz) / ��� �ӵ�(bps) *\n");
    printf("********************************************\n\n");

    printf("MCU�� �ý��� Ŭ�� ���ļ�(MHz)�� �Է��Ͻÿ�. : ");
    scanf("%f", &FRE);
    printf("��� �ӵ�(bps) ���� �Է��Ͻÿ�. : ");
    scanf("%f", &BPS);

    if(FRE <= 0 || BPS <= 0)
        printf("�ùٸ� ���� �Է��Ͻÿ�.\n");
    else{
        BAUD = (FRE * 1000000) / BPS;
        printf("\n");

        printf("BAUD RATE�� %.0f�Դϴ�.\n", BAUD);
    }
}
