void ATT_CAL()
{
    int CHO;
    float ATT, SERI, PARA;

    printf("**********************************\n");
    printf("* 파이(π)형 패드 감쇠값 계산기  *\n");
    printf("**********************************\n\n");

    printf("***************R1****************\n");
    printf("         *           *         \n");
    printf("         R2         R3         \n");
    printf("         *           *         \n\n");



    printf("R1의 저항값(Ω)을 입력하시오. : ");
    scanf("%f", &SERI);

    printf("R2, R3의 저항값(Ω)을 입력하시오. : ");
    scanf("%f", &PARA);



    if(SERI <= 0 || PARA <= 0)
    {
        printf("올바른 값을 입력하시오.");
    }
    else
    {
        printf("\n");

        printf("감쇠값은 %.2f [dB]입니다.", PAD_ATT(PARA, SERI));
    }
}



void PAD_CAL()
{
    float ATT, SERI, PARA;

    printf("**********************************\n");
    printf("* 파이(π)형 패드 저항값 계산기  *\n");
    printf("*   0.5dB ~ 25dB까지 계산 가능   *\n");
    printf("**********************************\n\n");

    printf("***************R1****************\n");
    printf("         *           *         \n");
    printf("         R2         R3         \n");
    printf("         *           *         \n\n");

    printf("원하는 감쇠량(㏈)을 입력하시오. : ");
    scanf("%f", &ATT);

    if(ATT < 0.5 || ATT > 25)
    {
        printf("올바른 값을 입력하시오.");
    }
    else
    {
        SERI = 25 * (pow(10, (ATT / 10.0)) - 1) * (pow(10, (-1 * ATT) / 20));
        PARA = 1 / (((pow(10, (ATT / 10.0)) + 1) / (50 * (pow(10, (ATT / 10.0)) - 1))) - (1 / SERI));

        printf("\n");

        printf("R1    (직렬) = %.1f [Ω]\n", SERI);
        printf("R2, R3(병렬) = %.1f [Ω]\n", PARA);

        RES_RECOMMEND(ATT, SERI, PARA);
    }
}
