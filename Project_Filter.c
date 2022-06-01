// C 기본 입출력 함수 라이브러리
// printf(), scanf() 등
#include <stdio.h>

// dos 제어 함수 라이브러리
// system() 등
#include <windows.h>

// 수학 함수 라이브러리
// log(), power() 등
#include <math.h>

// 사용자 정의 라이브러리
// 시스템 초기화
#include "INIT.h"

// 자재 조회 기능 및 추천 기능
#include "RES.h"

// 파이형 패드 값 계산기 기능
#include "PAD.h"

// 전력 계산 기능
#include "POWER.h"

// 시리얼 통신 BAUD 계산기 기능
#include "BAUD.h"



/*
개정 내역

ver 1.0 : 신규 제정
ver 1.1 : 파일 및 함수 분리
ver 1.2 : 저항값 계산기 기능 개선; 추천의 정밀도를 높임.
ver 1.3 : 저항값 계산기 기능 개선; 추천의 정밀도를 높임. 인터페이스 수정
ver 1.4 : 주석 추가. 인터페이스 수정
*/



void main()
{
    int op = 0, mod = 0;

    while(1)
    {
        printf("**************************************\n");
        printf("*    업무 자동화 프로그램 Ver 1.4    *\n");
        printf("*      MADE BY 2017531002 김민석     *\n");
        printf("*      LATELY UPDATED 2017/06/06     *\n");
        printf("**************************************\n\n");



        // 목록 표시
        printf("1. AMP 전력 효율 계산기\n");
        printf("2. AMP 전력 부가 효율 계산기\n");
        printf("3. 파이(π)형 패드 저항값 계산기\n");
        printf("4. 파이(π)형 패드 감쇠값 계산기\n");
        printf("5. USART 시리얼 통신 BAUD RATE 계산기\n");
        printf("6. 보유 자재 목록 조회 및 수정\n");
        printf("7. 프로그램 종료\n\n");



        // 작업 선택
        printf("원하는 작업 코드를 입력하시오. : ");
        scanf("%d", &op);



        // 선택한 작업을 함수 포인터에 값 할당
        switch(op)
        {
            case 1 :
            {
                // 전력효율 계산기
                // 드레인 인가 전압(V)과 전류(A), RF 출력 값(dBm)을 통해 AMP의 효율(%)을 구하는 기능
                boo = POWER_CAL;
                break;
            }
            case 2 :
            {
                // 전력부가효율 계산기
                // 드레인 인가 전압(V)과 전류(A)와 RF 입력 값(dBm), 그리고 RF 출력 값(dBm)을 통해 AMP의 전력부가효율(%)을 구하는 기능
                boo = PAE_CAL;
                break;
            }
            case 3 :
            {
                // PI PAD 저항값 계산기
                // 감쇠값(dB)을 입력받아 직렬 저항 값(Ω)과 병렬 저항 값(Ω)을 구하는 기능
                boo = PAD_CAL;
                break;
            }
            case 4 :
            {
                // PI PAD 감쇠값 계산기
                // 직렬 저항 값(Ω)과 병렬 저항 값(Ω)을 입력받아 감쇠값(dB)을 계산하는 기능
                boo = ATT_CAL;
                break;
            }
            case 5 :
            {
                // BADU RATE 계산기
                // MCU의 시스템 클럭 주파수 값(MHz)과 시리얼 통신 속도(bps)을 입력받아 BAUD RATE 값(baud)을 구하는 기능
                boo = BAUD_CAL;
                break;
            }
            case 6 :
            {
                // 보유 자재 목록 조회 및 수정
                // 텍스트 파일로 만들어진 보유 자재 목록을 파일 입출력을 통해 조회하거나 수정하는 기능
                // 저항값 계산기와 감쇠값 계산기가 이 자재 목록을 참조
                boo = RES_FUNC;
                break;
            }
            case 7 : break;
            default : break;
        }



        // 프로그램 종료
        if(op >= 7 || op <= 0)
            break;



        // 화면 지우기
        system("cls");



        // 기능 실행, 사후 처리
        while(1){
            // 포인터 값을 바탕으로 기능(함수) 실행
            FUNCTIONS(boo);



            // 기능이 끝난 후 작업 선택
            // 자재 조회/수정 기능에서의 사후처리
            if(op == 6)
            {
                printf("\n1. 자재 조회/수정 선택하기");
                printf("\n2. 처음으로 돌아가기");
                printf("\n3. 프로그램 종료\n");
                printf("원하는 작업 코드를 입력하시오. : ");
            }
            // 나머지 기능에서의 사후처리
            else
            {
                printf("\n1. 값 다시 입력하기");
                printf("\n2. 처음으로 돌아가기");
                printf("\n3. 프로그램 종료\n");
                printf("원하는 작업 코드를 입력하시오. : ");
            }



            // mod 값에 따라 아래와 같이 실행 방향 선택
            scanf("%d", &mod);



            // 화면 지우기
            system("cls");



            // 1일 경우에는 같은 기능을 다시 시작함.
            // 2나 3일 때에는 while 문에서 빠져나감
            if(mod == 1)
                continue;
            else if(mod == 2 || mod == 3)
                break;
            else
                break;
        }



        // 3일 경우에는 최종적으로 프로그램 종료
        if(mod >= 3 || mod <= 0)
            break;
    }
}
