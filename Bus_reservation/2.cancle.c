#include "BUS.h"

void cancle()
{
	char name[16]; // list.txt 정보를 배열로 저장하는 변수
	char time[6];
	int seat = 0;
	int flag = 0;
	int del_num;
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
			if (0 == flag) {
				printf("\t\t    예약 내역이 없습니다.\n");
				printf("\n============================================================\n\n");
				printf("엔터를 입력하세요.");
				getchar();
				return;
			}
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
	printf("취소할 번호를 입력하세요:");
	scanf_s("%d", &del_num);
	clear_buf();

	update_list(del_num);
}

void update_list(int num)
{
	char name[16], time[6];
	int seat;
	int flag = 1;
	int index_time;
	FILE* fp1, * fp2;

	fopen_s(&fp1, "list.txt", "r");
	if (NULL == fp1) {
		printf("FILE1 OPEN ERROR!\n");
		exit(-1);
	}
	fopen_s(&fp2, "list_temp.txt", "a+");
	if (NULL == fp2) {
		printf("FILE2 OPEN ERROR!\n");
		exit(-1);
	}

	while (1) {
		if (EOF == fscanf_s(fp1, "%s %s %d", name, 16, time, 6, &seat)) {
			break;;
		}

		if (flag == num) {
			for (int i = 0; i < MAX_TIME; i++) {
				if (0 == strcmp(rv_bus[i].time, time))
					index_time = i;
			}
			rv_bus[index_time].seat[seat / 4][seat % 4] = 0;
			flag++;
			continue;
		}
		fprintf(fp2, "%s %s %d\n", name, time, seat);

		flag++;
	}
	fclose(fp1);
	fclose(fp2);

	if (0 == remove("list.txt")) {
		rename("list_temp.txt", "list.txt");
		printf("취소되었습니다.\n");
	}
	else
		printf("취소 실패");

	save_reservation();
	getchar();
}