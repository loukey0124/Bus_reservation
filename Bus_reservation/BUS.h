#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#define MAX_TIME 5

typedef struct Bus {
	char time[6];
	int seat[8][4];
}BUS;

typedef struct UserInformation {
	char id[16];
	char password[16];
} UI; // 유저 아이디랑 비밀번호 구조체

BUS rv_bus[MAX_TIME];
UI user;

void clear_buf();
void reservation();
void save_reservation();
void save_list(char time, int seat);
void read_reservation();
void select_seat(int time);
void main_menu();
char sel_menu();
void run_menu(char menu);
void show_seat_list(char time);

void GetPassword(char parm_password[], int len);
void UserRegister();
int login();
void show_login_menu();

void r_status();

void confirm_reservation();

void cancle();
void update_list(int num);