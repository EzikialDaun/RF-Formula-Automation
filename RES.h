void TABLE_READ()
{
    i = 0;

    fp = fopen("RES.txt", "r");

    if(fp == NULL)
    {
        printf("파일을 열 수 없습니다.");
        exit(0);
    }

    while(i < MAX_ADDR)
    {
        fscanf(fp,"%d %f", &m[i].addr, &m[i].res);
        if(*m[i].res < 1000)
            printf("%2d\t%.1f[Ω]\n", *m[i].addr, *m[i].res);
        else
            printf("%2d\t%.1f[KΩ]\n", *m[i].addr, *m[i].res / 1000.0);
        i++;
    }

    fclose(fp);
}



void TABLE_WRITE()
{
    int a = 0;
    float b = 0;
    j = 0;

    fp = fopen("RES.txt", "w");

    if(fp == NULL)
    {
        printf("파일을 열 수 없습니다.");
        exit(0);
    }

    printf("\n수정하고자 하는 행의 번호를 입력하시오. : ");
    scanf("%d", &a);

    printf("수정하고자 자재 값(Ω)을 입력하시오.(소수점 첫번째 자리까지) : ");
    scanf("%f", &b);

    if(a <= 0 || a > MAX_ADDR)
    {
        printf("잘못된 주소값입니다.\n");
    }
    else
    {
        if((a == MAX_ADDR) && ((b >= *m[a - 2].res)))
        {
            *m[MAX_ADDR - 1].addr = MAX_ADDR;
            *m[MAX_ADDR - 1].res = b;
            printf("파일 입력 완료.\n");
        }
        else if((b <= *m[a].res) && (b >= *m[a - 2].res))
        {
            *m[a - 1].addr = a;
            *m[a - 1].res = b;
            printf("파일 입력 완료.\n");
        }
        else
            printf("잘못된 저항값입니다.\n");
    }

    while(j < MAX_ADDR)
    {
        if(j == MAX_ADDR - 1)
            fprintf(fp, "%d %.1f", *m[j].addr, *m[j].res);
        else
            fprintf(fp, "%d %.1f\n", *m[j].addr, *m[j].res);
        j++;
    }

    fclose(fp);
}



void RES_FUNC()
{
    int select;

    printf("*******************************\n");
    printf("* 보유 자재 목록 조회 및 수정 *\n");
    printf("*******************************\n\n");

    printf("\n1. 보유 자재 조회");
    printf("\n2. 자재 값 수정\n");
    printf("\n원하는 작업 코드를 입력하시오. : ");
    scanf("%d", &select);

    if(select == 1)
    {
        system("cls");
        RES_READ();
    }
    else if(select == 2)
    {
        system("cls");
        RES_MODIFY();
    }
    else
        printf("잘못된 코드를 입력하셨습니다.\n");
}



void RES_READ()
{
    printf("********************\n");
    printf("*  보유 자재 조회  *\n");
    printf("*                  *\n");
    printf("* 자재 번호 저항값 *\n");
    printf("********************\n\n");

    TABLE_READ();
}



void RES_MODIFY()
{
    printf("********************\n");
    printf("*   자재 값 수정   *\n");
    printf("*                  *\n");
    printf("* 자재 번호 저항값 *\n");
    printf("********************\n\n");

    TABLE_READ();

    TABLE_WRITE();
}



float PAD_ATT(float PARA, float SERI)
{
    float ATT, R2P, ZL, VSOURCE, LIN, VIN, VOU, POU;

    R2P = (PARA * 50) / (PARA + 50);
    ZL = (PARA * (R2P + SERI)) / (PARA + (R2P + SERI));
    VSOURCE = 2 * (sqrt(50));
    LIN = VSOURCE / (50 + ZL);
    VIN = VSOURCE - (LIN * 50);
    VOU = VIN * (R2P / (R2P + SERI));
    POU = (VOU * VOU) / 50;
    ATT = -10 * log10(POU);

    return ATT;
}



void RES_RECOMMEND(float ATT, float SERI, float PARA)
{
    float REC_SERI, REC_PARA, minimum;
    float rec[16];
    int k;
    i = 0, j = 0;

    fp = fopen("RES.txt", "r");

        if(fp == NULL)
        {
            printf("파일을 열 수 없습니다.");
            exit(0);
        }

        while(!feof(fp))
        {
            fscanf(fp,"%d %f", &m[i].addr, &m[i].res);
            i++;
        }

        i = 0;

        while(!((*m[i].res <= SERI) && (*m[i + 1].res >= SERI))){
            i++;
        }

        j = 0;

        while(!((*m[j].res <= PARA) && (*m[j + 1].res >= PARA))){
            j++;
        }



        if(PAD_ATT(*m[j + 2].res, *m[i + 2].res) > ATT)
            rec[0] = PAD_ATT(*m[j + 2].res, *m[i + 2].res) - ATT;
        else
            rec[0] = ATT - PAD_ATT(*m[j + 2].res, *m[i + 2].res);

        if(PAD_ATT(*m[j + 1].res, *m[i + 2].res) > ATT)
            rec[1] = PAD_ATT(*m[j + 1].res, *m[i + 2].res) - ATT;
        else
            rec[1] = ATT - PAD_ATT(*m[j + 1].res, *m[i + 2].res);

        if(PAD_ATT(*m[j].res, *m[i + 2].res) > ATT)
            rec[2] = PAD_ATT(*m[j].res, *m[i + 2].res) - ATT;
        else
            rec[2] = ATT - PAD_ATT(*m[j].res, *m[i + 2].res);

        if(PAD_ATT(*m[j - 1].res, *m[i + 2].res) > ATT)
            rec[3] = PAD_ATT(*m[j - 1].res, *m[i + 2].res) - ATT;
        else
            rec[3] = ATT - PAD_ATT(*m[j - 1].res, *m[i + 2].res);



        if(PAD_ATT(*m[j + 2].res, *m[i + 1].res) > ATT)
            rec[4] = PAD_ATT(*m[j + 2].res, *m[i + 1].res) - ATT;
        else
            rec[4] = ATT - PAD_ATT(*m[j + 2].res, *m[i + 1].res);

        if(PAD_ATT(*m[j + 1].res, *m[i + 1].res) > ATT)
            rec[5] = PAD_ATT(*m[j + 1].res, *m[i + 1].res) - ATT;
        else
            rec[5] = ATT - PAD_ATT(*m[j + 1].res, *m[i + 1].res);

        if(PAD_ATT(*m[j].res, *m[i + 1].res) > ATT)
            rec[6] = PAD_ATT(*m[j].res, *m[i + 1].res) - ATT;
        else
            rec[6] = ATT - PAD_ATT(*m[j].res, *m[i + 1].res);

        if(PAD_ATT(*m[j - 1].res, *m[i + 1].res) > ATT)
            rec[7] = PAD_ATT(*m[j - 1].res, *m[i + 1].res) - ATT;
        else
            rec[7] = ATT - PAD_ATT(*m[j - 1].res, *m[i + 1].res);



        if(PAD_ATT(*m[j + 2].res, *m[i].res) > ATT)
            rec[8] = PAD_ATT(*m[j + 2].res, *m[i].res) - ATT;
        else
            rec[8] = ATT - PAD_ATT(*m[j + 2].res, *m[i].res);

        if(PAD_ATT(*m[j + 1].res, *m[i].res) > ATT)
            rec[9] = PAD_ATT(*m[j + 1].res, *m[i].res) - ATT;
        else
            rec[9] = ATT - PAD_ATT(*m[j + 1].res, *m[i].res);

        if(PAD_ATT(*m[j].res, *m[i].res) > ATT)
            rec[10] = PAD_ATT(*m[j].res, *m[i].res) - ATT;
        else
            rec[10] = ATT - PAD_ATT(*m[j].res, *m[i].res);

        if(PAD_ATT(*m[j - 1].res, *m[i].res) > ATT)
            rec[11] = PAD_ATT(*m[j - 1].res, *m[i].res) - ATT;
        else
            rec[11] = ATT - PAD_ATT(*m[j - 1].res, *m[i].res);



        if(PAD_ATT(*m[j + 2].res, *m[i - 1].res) > ATT)
            rec[12] = PAD_ATT(*m[j + 2].res, *m[i - 1].res) - ATT;
        else
            rec[12] = ATT - PAD_ATT(*m[j + 2].res, *m[i - 1].res);

        if(PAD_ATT(*m[j + 1].res, *m[i - 1].res) > ATT)
            rec[13] = PAD_ATT(*m[j + 1].res, *m[i - 1].res) - ATT;
        else
            rec[13] = ATT - PAD_ATT(*m[j + 1].res, *m[i - 1].res);

        if(PAD_ATT(*m[j].res, *m[i - 1].res) > ATT)
            rec[14] = PAD_ATT(*m[j].res, *m[i - 1].res) - ATT;
        else
            rec[14] = ATT - PAD_ATT(*m[j].res, *m[i - 1].res);

        if(PAD_ATT(*m[j - 1].res, *m[i - 1].res) > ATT)
            rec[15] = PAD_ATT(*m[j - 1].res, *m[i - 1].res) - ATT;
        else
            rec[15] = ATT - PAD_ATT(*m[j - 1].res, *m[i - 1].res);


        minimum = rec[0];
        for(k = 0;k < 16;k++){
            if(rec[k] < minimum)
                minimum = rec[k];
        }



        printf("\n보유 자재에 따라 권장되는 저항 값\n");



        if(minimum == rec[0])
        {
            REC_SERI = *m[i + 2].res;
            REC_PARA = *m[j + 2].res;
        }
        else if(minimum == rec[1])
        {
            REC_SERI = *m[i + 2].res;
            REC_PARA = *m[j + 1].res;
        }
        else if(minimum == rec[2])
        {
            REC_SERI = *m[i + 2].res;
            REC_PARA = *m[j].res;
        }
        else if(minimum == rec[3])
        {
            REC_SERI = *m[i + 2].res;
            REC_PARA = *m[j - 1].res;
        }
        else if(minimum == rec[4])
        {
            REC_SERI = *m[i + 1].res;
            REC_PARA = *m[j + 2].res;
        }
        else if(minimum == rec[5])
        {
            REC_SERI = *m[i + 1].res;
            REC_PARA = *m[j + 1].res;
        }
        else if(minimum == rec[6])
        {
            REC_SERI = *m[i + 1].res;
            REC_PARA = *m[j].res;
        }
        else if(minimum == rec[7])
        {
            REC_SERI = *m[i + 1].res;
            REC_PARA = *m[j - 1].res;
        }
        else if(minimum == rec[8])
        {
            REC_SERI = *m[i].res;
            REC_PARA = *m[j + 2].res;
        }
        else if(minimum == rec[9])
        {
            REC_SERI = *m[i].res;
            REC_PARA = *m[j + 1].res;
        }
        else if(minimum == rec[10])
        {
            REC_SERI = *m[i].res;
            REC_PARA = *m[j].res;
        }
        else if(minimum == rec[11])
        {
            REC_SERI = *m[i].res;
            REC_PARA = *m[j - 1].res;
        }
        else if(minimum == rec[12])
        {
            REC_SERI = *m[i - 1].res;
            REC_PARA = *m[j + 2].res;
        }
        else if(minimum == rec[13])
        {
            REC_SERI = *m[i - 1].res;
            REC_PARA = *m[j + 1].res;
        }
        else if(minimum == rec[14])
        {
            REC_SERI = *m[i - 1].res;
            REC_PARA = *m[j].res;
        }
        else if(minimum == rec[15])
        {
            REC_SERI = *m[i - 1].res;
            REC_PARA = *m[j - 1].res;
        }

        printf("R1    (직렬) = %.1f [Ω]\n", REC_SERI);
        printf("R2, R3(병렬) = %.1f [Ω]\n", REC_PARA);
        printf("감쇠 값      = %.2f [dB]\n", PAD_ATT(REC_PARA, REC_SERI));



        fclose(fp);
}
