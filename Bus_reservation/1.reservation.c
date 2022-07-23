#include "BUS.h"

void clear_buf()
{
	while ('\n' != getchar());
}

void main_menu()
{
	system("mode con cols=60 lines=30");
	printf("============환영합니다. 버스 예약 시스템 입니다.============\n\n");
	printf("\t\t\t[1] 예매하기\n\n");
	printf("\t\t\t[2] 예매확인\n\n");
	printf("\t\t\t[3] 예매취소\n\n");
	printf("\t\t\t[4] 예매현황\n\n");
	printf("\t\t\t[5] 종료.\n\n");
	printf("============================================================\n");
}

char sel_menu()
{
	char menu;

	printf("\n메뉴를 선택하세요:");
	scanf_s("%c", &menu, 1);
	clear_buf();
	return menu;
}

void run_menu(char menu)
{
	switch (menu)
	{
	case '1':
		printf("1. 예매하기\n");
		reservation();
		break;
	case '2':
		printf("2. 예매확인\n");
		confirm_reservation();
		break;
	case '3':
		printf("3. 예매취소\n");
		cancle();
		break;
	case '4':
		printf("4. 예매현황\n");
		r_status();
		break;
	case '5':
		exit(1);
		break;
	default:
		break;
	}
	system("cls");
}

void reservation()
{
	int sel_time = 0;
	system("cls");
	printf("==================천안 -> 서울행 버스 예약==================\n\n");
	for (int i = 0; i < MAX_TIME; i++)
		printf("\t\t\t[%d] %s\n\n", i + 1, rv_bus[i].time);
	printf("============================================================\n\n");
	printf("시간을 선택하세요:");
	scanf_s("%d", &sel_time);
	clear_buf();
	if (1 > sel_time || 5 < sel_time)
		return;
	else
		sel_time -= 1;
	
	select_seat(sel_time);
}

void read_reservation()
{
	int temp;
	FILE* fp;

	fopen_s(&fp, "seat.txt", "r");
	if (NULL == fp) {
		printf("FILE OPEN ERROR\n");
		exit(-1);
	}

	for (int i = 0; i < MAX_TIME; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 4; k++) {
				temp = fgetc(fp);
				if (temp == 49)
					rv_bus[i].seat[j][k] = 1;
				else if (temp == 48)
					continue;
				else
					k--;
			}
		}
	}
	fclose(fp);
}

void save_reservation()
{
	FILE* fp;
	fopen_s(&fp, "seat.txt", "w");
	if (NULL == fp) {
		printf("FILE OPEN ERROR\n");
		exit(-1);
	}
		

	for (int i = 0; i < MAX_TIME; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 4; k++)
				fprintf(fp, "%d", rv_bus[i].seat[j][k]);
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void save_list(char time, int seat) {
	FILE* fp;
	int i = seat / 4, j = seat % 4;
	
	fopen_s(&fp, "list.txt", "a");
	if (NULL == fp) {
		printf("FILE OPEN ERROR\n");
		exit(-1);
	}

	fprintf(fp, "%s %s %d\n", user.id, rv_bus[time].time, seat);
	fclose(fp);
}

void select_seat(int time)
{
	int seat;
	int people;
	int seat_arr[32];

	show_seat_list(time);
	
	printf("인원수를 입력하세요:");
	scanf_s("%d", &people);
	for (int i = 0; i < people; i++) {//입력한 인원수 만큼 반복
		show_seat_list(time);//좌석 리스트 출력
		printf("%d번째 좌석을 선택하세요:", i + 1);
		scanf_s("%d", &seat);
		seat--;

		for (int i = 0; i < 32; i++)//2차원 배열을 1차원 배열에 대입
			seat_arr[i] = rv_bus[time].seat[i / 4][i % 4];

		if (1 == seat_arr[seat]) {//선택한 좌석이 매진이면 다시 입력받음
			printf("이미 예약된 좌석입니다.\n좌석을 다시 선택하세요.\n");
			i--;
		}
		else//아니라면 해당 위치의 배열값을 1로 변경
			rv_bus[time].seat[(seat) / 4][(seat) % 4] = 1;

		show_seat_list(time);//좌석 리스트 출력
		save_reservation();//좌석 리스트 저장
		save_list(time, seat);
	}
	clear_buf();//버퍼 비우기
	printf("예약이 완료되었습니다.");
	getchar();//엔터 대기
}

void show_seat_list(char time)
{
	int index = 1;
	system("cls");
	printf("======================좌석을 선택하세요=====================\n\n");

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
}