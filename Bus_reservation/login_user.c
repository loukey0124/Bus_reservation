#include "BUS.h"

void GetPassword(char parm_password[], int len)
{
    char input = 0;
    int i = 0;
    while (input != 13) {
        input = getch();
        if (input == 13 || len - 1 == i) {
            parm_password[i] = 0;
            break;
        }
        else {
            printf("*");
            parm_password[i] = input;
            i++;
        }
    }
}

void UserRegister() // 회원가입
{
    char id[16], pw[16], re[16];
    FILE* fp;

    while (1)
    {
        system("cls");
        printf("==========================회원가입==========================\n\n");
        printf("\t\t\tID:");
        scanf_s("%s", id, 16);
        clear_buf();
        printf("\t\t\tPW:");
        GetPassword(pw, 16);
        printf("\n");
        printf("\t\t\tre:");
        GetPassword(re, 16);
        printf("\n");

        fopen_s(&fp, "user.txt", "a");
        if (NULL == fp) {
            printf("FILE OPEN ERROR\n");
            exit(-1);
        }

        if (0 == strcmp(pw, re)) {
            fprintf(fp, "%s %s\n", id, pw);
            printf("회원가입이 완료되었습니다.\n");
            fclose(fp);
            getchar();
            return;
        }
        printf("비밀번호가 일치하지 않습니다.\n");
        getchar();
    }
}

int login() //로그인
{
    int i = 0, input = 0;
    int login_flag = 0;
    char id[16], pw[16], buf_id[16], buf_pw[16];
    FILE* fp;

    while (!login_flag) {
        system("cls");
        printf("===========================로그인===========================\n\n");
        printf("\t\t\tID:");
        scanf_s("%s", id, 16);
        clear_buf();
        printf("\t\t\tPW:");
        GetPassword(pw, 16);

        fopen_s(&fp, "user.txt", "r");
        if (NULL == fp) {
            printf("FILE OPEN ERROR\n");
            exit(-1);
        }

        while (1) {          
            if (EOF == fscanf_s(fp, "%s %s", buf_id, 16, buf_pw, 16)) {
                printf("\n아이디가 없습니다!");
                fclose(fp);
                clear_buf();
                return login_flag;
            }

            if (0 == strcmp(id, buf_id)) {
                if (0 == strcmp(pw, buf_pw)) {
                    printf("\n성공적으로 로그인 했습니다.");
                    strcpy_s(user.id, 16, id);
                    login_flag = 1;
                    fclose(fp);
                    clear_buf();
                    return login_flag;
                }
                else {
                    printf("\n비밀번호가 틀렸습니다!");
                    fclose(fp);
                    clear_buf();
                    return login_flag;
                }
            }
        }
    }
}

void show_login_menu()
{
    int flag = 0;
    char menu;
    while (1) {
        system("cls");
        printf("============환영합니다. 버스 예약 시스템 입니다.============\n\n");
        printf("\t\t\t[1] 로그인\n\n");
        printf("\t\t\t[2] 회원가입\n\n");
        printf("\t\t\t[3] 종료\n\n");
        printf("============================================================\n");
        printf("\n메뉴를 선택하세요:");
        scanf_s("%c", &menu, 1);
        clear_buf();

        switch (menu)
        {
        case '1':
            flag = login();
            break;
        case '2':
            UserRegister();
            break;
        case '3':
            exit(1);
            break;
        default:
            break;
        }

        if (1 == flag)
            break;
    }
}