void TABLE_READ()
{
    i = 0;

    fp = fopen("RES.txt", "r");

    if(fp == NULL)
    {
        printf("������ �� �� �����ϴ�.");
        exit(0);
    }

    while(i < MAX_ADDR)
    {
        fscanf(fp,"%d %f", &m[i].addr, &m[i].res);
        if(*m[i].res < 1000)
            printf("%2d\t%.1f[��]\n", *m[i].addr, *m[i].res);
        else
            printf("%2d\t%.1f[K��]\n", *m[i].addr, *m[i].res / 1000.0);
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
        printf("������ �� �� �����ϴ�.");
        exit(0);
    }

    printf("\n�����ϰ��� �ϴ� ���� ��ȣ�� �Է��Ͻÿ�. : ");
    scanf("%d", &a);

    printf("�����ϰ��� ���� ��(��)�� �Է��Ͻÿ�.(�Ҽ��� ù��° �ڸ�����) : ");
    scanf("%f", &b);

    if(a <= 0 || a > MAX_ADDR)
    {
        printf("�߸��� �ּҰ��Դϴ�.\n");
    }
    else
    {
        if((a == MAX_ADDR) && ((b >= *m[a - 2].res)))
        {
            *m[MAX_ADDR - 1].addr = MAX_ADDR;
            *m[MAX_ADDR - 1].res = b;
            printf("���� �Է� �Ϸ�.\n");
        }
        else if((b <= *m[a].res) && (b >= *m[a - 2].res))
        {
            *m[a - 1].addr = a;
            *m[a - 1].res = b;
            printf("���� �Է� �Ϸ�.\n");
        }
        else
            printf("�߸��� ���װ��Դϴ�.\n");
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
    printf("* ���� ���� ��� ��ȸ �� ���� *\n");
    printf("*******************************\n\n");

    printf("\n1. ���� ���� ��ȸ");
    printf("\n2. ���� �� ����\n");
    printf("\n���ϴ� �۾� �ڵ带 �Է��Ͻÿ�. : ");
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
        printf("�߸��� �ڵ带 �Է��ϼ̽��ϴ�.\n");
}



void RES_READ()
{
    printf("********************\n");
    printf("*  ���� ���� ��ȸ  *\n");
    printf("*                  *\n");
    printf("* ���� ��ȣ ���װ� *\n");
    printf("********************\n\n");

    TABLE_READ();
}



void RES_MODIFY()
{
    printf("********************\n");
    printf("*   ���� �� ����   *\n");
    printf("*                  *\n");
    printf("* ���� ��ȣ ���װ� *\n");
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
            printf("������ �� �� �����ϴ�.");
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



        printf("\n���� ���翡 ���� ����Ǵ� ���� ��\n");



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

        printf("R1    (����) = %.1f [��]\n", REC_SERI);
        printf("R2, R3(����) = %.1f [��]\n", REC_PARA);
        printf("���� ��      = %.2f [dB]\n", PAD_ATT(REC_PARA, REC_SERI));



        fclose(fp);
}
