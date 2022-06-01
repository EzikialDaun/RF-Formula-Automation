void ATT_CAL()
{
    int CHO;
    float ATT, SERI, PARA;

    printf("**********************************\n");
    printf("* ����(��)�� �е� ���谪 ����  *\n");
    printf("**********************************\n\n");

    printf("***************R1****************\n");
    printf("         *           *         \n");
    printf("         R2         R3         \n");
    printf("         *           *         \n\n");



    printf("R1�� ���װ�(��)�� �Է��Ͻÿ�. : ");
    scanf("%f", &SERI);

    printf("R2, R3�� ���װ�(��)�� �Է��Ͻÿ�. : ");
    scanf("%f", &PARA);



    if(SERI <= 0 || PARA <= 0)
    {
        printf("�ùٸ� ���� �Է��Ͻÿ�.");
    }
    else
    {
        printf("\n");

        printf("���谪�� %.2f [dB]�Դϴ�.", PAD_ATT(PARA, SERI));
    }
}



void PAD_CAL()
{
    float ATT, SERI, PARA;

    printf("**********************************\n");
    printf("* ����(��)�� �е� ���װ� ����  *\n");
    printf("*   0.5dB ~ 25dB���� ��� ����   *\n");
    printf("**********************************\n\n");

    printf("***************R1****************\n");
    printf("         *           *         \n");
    printf("         R2         R3         \n");
    printf("         *           *         \n\n");

    printf("���ϴ� ���跮(��)�� �Է��Ͻÿ�. : ");
    scanf("%f", &ATT);

    if(ATT < 0.5 || ATT > 25)
    {
        printf("�ùٸ� ���� �Է��Ͻÿ�.");
    }
    else
    {
        SERI = 25 * (pow(10, (ATT / 10.0)) - 1) * (pow(10, (-1 * ATT) / 20));
        PARA = 1 / (((pow(10, (ATT / 10.0)) + 1) / (50 * (pow(10, (ATT / 10.0)) - 1))) - (1 / SERI));

        printf("\n");

        printf("R1    (����) = %.1f [��]\n", SERI);
        printf("R2, R3(����) = %.1f [��]\n", PARA);

        RES_RECOMMEND(ATT, SERI, PARA);
    }
}
