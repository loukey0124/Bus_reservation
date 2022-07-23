#include "BUS.h"

void r_status()
{
	int time;
	int index = 1;

	system("cls");
	printf("============================================================\n\n");
	for (int i = 0; i < MAX_TIME; i++)
		printf("\t\t\t[%d] %s\n\n", i + 1, rv_bus[i].time);

	printf("============================================================\n\n");
	printf("시간을 선택하세요:");
	scanf_s("%d", &time);
	clear_buf();
	if (1 > time || 5 < time)
		return;
	else
		time -= 1;

	system("cls");
	printf("====================%s 좌석 예약 현황====================\n\n", rv_bus[time].time);

	for (int i = 0; i < 8; i++) {
		printf("\t     ");
		for (int j = 0; j < 4; j++) {
			if (1 == rv_bus[time].seat[i][j])
				printf("%2d. ■   ", index);
			else
				printf("%2d. □   ", index);

			if (1 == j)
				printf("  ");
			index++;
		}
		printf("\n\n");
	}
	printf("============================================================\n\n");
	printf("엔터를 입력하세요.");
	getchar();
}