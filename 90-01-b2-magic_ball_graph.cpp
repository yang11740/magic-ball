#include <iostream>
#include <windows.h>
#include "cmd_console_tools.h"
#include "common-popstar_ball.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

/*
void frame(int row, int col, int select)
{
	int i, j, x;
	if (select == '4')
		x = 0;
	else
		x = 1;

	cct_showstr(0, 1, "╔", COLOR_HWHITE, COLOR_BLACK, 1);
	if (select == '4' || select == '5') {
		Sleep(50);
	}
	for (i = 0; i < col; i++) {
		cct_showstr(2 + (2 + 2 * x) * i, 1, "═", COLOR_HWHITE, COLOR_BLACK, 1);
		if (select == '4' || select == '5') {
			Sleep(50);
		}
		if (x && (i < col - 1)) {
			cct_showstr(4 + 4 * i, 1, "╦", COLOR_HWHITE, COLOR_BLACK, 1);
			if (select == '4' || select == '5') {
				Sleep(50);
			}
		}
	}
	cct_showstr(2 + (2 + 2 * x) * col - 2 * x, 1, "╗", COLOR_HWHITE, COLOR_BLACK, 1);
	if (select == '4' || select == '5') {
		Sleep(50);
	}
	for (j = 0; j < row; j++) {
		cct_showstr(0, j * (x + 1) + 2, "║", COLOR_HWHITE, COLOR_BLACK, 1);
		if (x) {
			for (i = 0; i < col; i++) {
				cct_showstr(2 + 4 * i, j * (x + 1) + 2, "  ", COLOR_HWHITE, COLOR_HWHITE, 1);
				if (select == '4' || select == '5') {
					Sleep(50);
				}
				if (i < col - 1) {
					cct_showstr(4 + 4 * i, j * (x + 1) + 2, "║", COLOR_HWHITE, COLOR_BLACK, 1);
					if (select == '4' || select == '5') {
						Sleep(50);
					}
				}
			}
		}
		cct_showstr(2 + (2 + 2 * x) * col - 2 * x, j * (x + 1) + 2, "║", COLOR_HWHITE, COLOR_BLACK, 1);
		if (select == '4' || select == '5') {
			Sleep(50);
		}
		if (x && (j < row - 1)) {
			cct_showstr(0, j * (x + 1) + 3, "╠═", COLOR_HWHITE, COLOR_BLACK, 1);
			if (select == '4' || select == '5') {
				Sleep(50);
			}
			cct_showstr(4, j * (x + 1) + 3, "╬═", COLOR_HWHITE, COLOR_BLACK, col - 1);
			if (select == '4' || select == '5') {
				Sleep(50);
			}
			cct_showstr(4 * col, j * (x + 1) + 3, "╣", COLOR_HWHITE, COLOR_BLACK, 1);
			if (select == '4' || select == '5') {
				Sleep(50);
			}
		}
	}

	cct_showstr(0, (row - 1) * (x + 1) + 3, "╚", COLOR_HWHITE, COLOR_BLACK, 1);
	if (select == '4' || select == '5') {
		Sleep(50);
	}
	for (i = 0; i < col; i++) {
		cct_showstr(2 + (2 + 2 * x) * i, (row - 1) * (x + 1) + 3, "═", COLOR_HWHITE, COLOR_BLACK, 1);
		if (select == '4' || select == '5') {
			Sleep(50);
		}
		if (x && (i < col - 1)) {
			cct_showstr(4 + 4 * i, (row - 1) * (x + 1) + 3, "╩", COLOR_HWHITE, COLOR_BLACK, 1);
			if (select == '4' || select == '5') {
				Sleep(50);
			}
		}
	}
	cct_showstr(2 + (2 + 2 * x) * col - 2 * x, (row - 1) * (x + 1) + 3, "╝", COLOR_HWHITE, COLOR_BLACK, 1);
	if (select == '4' || select == '5') {
		Sleep(50);
	}
}

void print_ball(char ball[][9], int row, int col, int select)
{
	int i, j, x;
	if (select == '4')
		x = 0;
	else
		x = 1;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			cct_showstr(2 + (2 + 2 * x) * j, 2 + (1 + x) * i, "○", ball[i][j], COLOR_BLACK, 1);
			if (select == '4' || select == '5') {
				Sleep(50);
			}
		}
	}
}
*/

void print_check(struct RAND ball[10][10], int row, int col,int* p_bomb)
{
	int i, j, k, n1 = 1, m, n2 = 1, num = 0;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col - 2; j += n1) {
			n1 = 1;
			if (ball[i][j].number == ball[i][j + 1].number) {
				for (k = j; ball[i][j].number == ball[i][k + 1].number; k++) {
					n1++;
				}
			}
			if (n1 > 2) {
				for (m = 0; m < n1; m++) {
					*(p_bomb++) = i * 9 + j + m;
					cct_showstr(2 + 4 * (j + m), 2 + 2 * i, "●", ball[i][j].number, COLOR_BLACK, 1);
					cct_setcolor();
				}
				num++;
			}
		}
	}

	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 2; i+=n2) {
			n2 = 1;
			if (ball[i][j].number == ball[i + 1][j].number)
				for (k = i; ball[i][j].number == ball[k + 1][j].number; k++)
					n2++;
			if (n2 > 2) {
				for (m = 0; m < n2; m++) {
					*(p_bomb++) = (i + m) * 9 + j;
					cct_showstr(2 + 4 * j, 2 + 2 * (i + m), "●", ball[i][j].number, COLOR_BLACK, 1);
					cct_setcolor();
				}
				num++;
			}
		}
	}
	*p_bomb = -1;
	if (num == 0) {
		cct_gotoxy(0, 0);
		cct_setcolor();
		cout << "初始已无可消除项" << endl;
	}
}

int print_disappear(struct RAND ball[10][10], int row, int col, int bomb[])
{
	int i;
	int num = 0;
	for (i = 0; bomb[i] >= 0; i++) {
		if (ball[bomb[i] / 9][bomb[i] % 9].number != '0') {
			cct_showstr(2 + 4 * (bomb[i] % 9), 2 + 2 * (bomb[i] / 9), "¤", ball[bomb[i] / 9][bomb[i] % 9].number, COLOR_BLACK, 1);
			Sleep(100);
			cct_showstr(2 + 4 * (bomb[i] % 9), 2 + 2 * (bomb[i] / 9), "  ", ball[bomb[i] / 9][bomb[i] % 9].number, COLOR_BLACK, 1);
			Sleep(100);
			cct_showstr(2 + 4 * (bomb[i] % 9), 2 + 2 * (bomb[i] / 9), "¤", ball[bomb[i] / 9][bomb[i] % 9].number, COLOR_BLACK, 1);
			Sleep(100);
			cct_showstr(2 + 4 * (bomb[i] % 9), 2 + 2 * (bomb[i] / 9), "  ", COLOR_HWHITE, COLOR_HWHITE, 1);
			Sleep(100);
			cct_setcolor();
			ball[bomb[i] / 9][bomb[i] % 9].number = '0';
			num++;
		}
	}
	return num;
}
/*
void print_down(struct RAND ball[10][10], int row, int col)
{
	int i, j, k, n1 = 1, n2 = 1;
	char t;

	for (j = 0; j < col; j++) {
		for (i = 0; i < row; i++) {
			if (ball[i][j].number == '0') {
				for (k = 0; k < i; k++) {
					t = ball[i - k][j].number;
					ball[i - k][j].number = ball[i - k - 1][j].number;
					ball[i - k - 1][j].number = t;
					if (ball[i - k][j].number != '0') {
						cct_showstr(2 + 4 * j, 2 + 2 * (i - k), "○", ball[i - k][j].number, COLOR_BLACK, 1);
					}
					if (ball[i - k][j].number == '0') {
						cct_showstr(2 + 4 * j, 2 + 2 * (i - k), "  ", COLOR_HWHITE, COLOR_HWHITE, 1);
					}
					cct_showstr(2 + 4 * j, 2 + 2 * (i - k - 1), "  ", COLOR_HWHITE, COLOR_HWHITE, 1);
					Sleep(200);
				}
			}
		}
	}
	cct_setcolor();
}
*/
void print_fill(struct RAND ball[10][10], int row, int col)
{
	int i, j;
	
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (ball[i][j].number == '0') {
				ball[i][j].number = 49 + rand() % 9;
				ball[i][j].sign = 0;
				ball[i][j].color = 0;
				ball[i][j].zero_up = 0;
				cct_showstr(2 + 4 * j, 2 + 2 * i, "○", ball[i][j].number, COLOR_BLACK, 1);
				Sleep(100);
			}
		}
	}
}

int print_exchange(struct RAND ball[10][10], int row, int col, int* p_note)
{
	int i, j, k;
	int non[6] = { 0,0,0,0,0,0 };
	int temp[80];
	int* p;
	p = temp;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (i - 1 >= 0) {
				if (i - 3 >= 0) {
					non[0] = (ball[i][j].number == ball[i - 2][j].number);
					non[1] = (ball[i][j].number == ball[i - 3][j].number);
				}
				if (j - 1 >= 0)
					non[2] = (ball[i][j].number == ball[i - 1][j - 1].number);
				if (j - 2 >= 0)
					non[3] = (ball[i][j].number == ball[i - 1][j - 2].number);
				if (j + 1 < col)
					non[4] = (ball[i][j].number == ball[i - 1][j + 1].number);
				if (j + 2 < col)
					non[5] = (ball[i][j].number == ball[i - 1][j + 2].number);

				if ((non[0] && non[1]) || (non[2] && non[3]) || (non[4] && non[5]) || (non[2] && non[4])) {
					*(p++) = i * 9 + j;
					*(p++) = (i - 1) * 9 + j;
				}
			}

			for (k = 0; k < 6; k++)
				non[k] = 0;

			if (j - 1 >= 0) {
				if (j - 3 >= 0) {
					non[0] = (ball[i][j].number == ball[i][j - 2].number);
					non[1] = (ball[i][j].number == ball[i][j - 3].number);
				}
				if (i - 1 >= 0)
					non[2] = (ball[i][j].number == ball[i - 1][j - 1].number);
				if (i - 2 >= 0)
					non[3] = (ball[i][j].number == ball[i - 2][j - 1].number);
				if (i + 1 < row)
					non[4] = (ball[i][j].number == ball[i + 1][j - 1].number);
				if (i + 2 < row)
					non[5] = (ball[i][j].number == ball[i + 2][j - 1].number);

				if ((non[0] && non[1]) || (non[2] && non[3]) || (non[4] && non[5]) || (non[2] && non[4])) {
					*(p++) = i * 9 + j;
					*(p++) = i * 9 + j - 1;
				}
			}

			for (k = 0; k < 6; k++)
				non[k] = 0;

			if (i + 1 < row) {
				if (i + 3 < row) {
					non[0] = (ball[i][j].number == ball[i + 2][j].number);
					non[1] = (ball[i][j].number == ball[i + 3][j].number);
				}
				if (j - 1 >= 0)
					non[2] = (ball[i][j].number == ball[i + 1][j - 1].number);
				if (j - 2 >= 0)
					non[3] = (ball[i][j].number == ball[i + 1][j - 2].number);
				if (j + 1 < col)
					non[4] = (ball[i][j].number == ball[i + 1][j + 1].number);
				if (j + 2 < col)
					non[5] = (ball[i][j].number == ball[i + 1][j + 2].number);

				if ((non[0] && non[1]) || (non[2] && non[3]) || (non[4] && non[5]) || (non[2] && non[4])) {
					*(p++) = i * 9 + j;
					*(p++) = (i + 1) * 9 + j;
				}
			}

			for (k = 0; k < 6; k++)
				non[k] = 0;

			if (j + 1 < col) {
				if (j + 3 < col) {
					non[0] = (ball[i][j].number == ball[i][j + 2].number);
					non[1] = (ball[i][j].number == ball[i][j + 3].number);
				}
				if (i + 1 < row)
					non[2] = (ball[i][j].number == ball[i + 1][j + 1].number);
				if (i + 2 < row)
					non[3] = (ball[i][j].number == ball[i + 2][j + 1].number);
				if (i - 1 >= 0)
					non[4] = (ball[i][j].number == ball[i - 1][j + 1].number);
				if (i - 2 >= 0)
					non[5] = (ball[i][j].number == ball[i - 2][j + 1].number);

				if ((non[0] && non[1]) || (non[2] && non[3]) || (non[4] && non[5]) || (non[2] && non[4])) {
					*(p++) = i * 9 + j;
					*(p++) = i * 9 + j + 1;
				}
			}

			for (k = 0; k < 6; k++)
				non[k] = 0;
		}
	}
	*p = -1;
	p = temp;
	if (*p >= 0) {
		for (; *p >= 0; p++) {
			cct_showstr(2 + 4 * (*p % 9), 2 + 2 * (*p / 9), "◎", ball[*p / 9][*p % 9].number, COLOR_BLACK, 1);
			*(p_note++) = *p;
		}
		*p_note = -1;
		return 1;
	}
	else
		return 0;
}
