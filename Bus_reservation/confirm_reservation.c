#include "BUS.h"

void confirm_reservation()
{
	char name[16]; // list.txt 정보를 배열로 저장하는 변수
	char time[6];
	int seat = 0;
	int flag = 0;
	FILE* fp;
	
	system("cls");
	printf("======================나의 예약 내역========================\n\n");

	fopen_s(&fp, "list.txt", "r");
	if (NULL == fp) {
		printf("FILE OPEN ERROR\n");
		exit(-1);
	}

	int i = 1;
	while (1) {
		if (EOF == fscanf_s(fp, "%s %s %d", name, 16, time, 6, &seat)) {
			if (0 == flag)
				printf("\t\t    예약 내역이 없습니다.\n");
			printf("\n============================================================\n\n");
			break;
		}

		if (0 == strcmp(user.id, name)) {
			printf("\t    %2d. %-8s  시간:%6s  좌석번호:%2d\n", flag + 1, name, time, seat + 1);
			flag++;
		}
		i++;
	}
	fclose(fp);
	printf("엔터를 입력하세요.");
	getchar();
}
	