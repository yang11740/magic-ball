#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "cmd_console_tools.h"
#include "common-popstar_ball.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

int judge_all(struct RAND ball[10][10], int row, int col)
{
	int i, j, k, n1 = 1, n2 = 1, num = 0, m;

	//查找每一行中是否有可消除项
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
					ball[i][j + m].sign = 1;
				}
				num++;
			}
		}
	}
	//查找每一列中是否有可消除项
	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 2; i += n2) {
			n2 = 1;
			if (ball[i][j].number == ball[i + 1][j].number)
				for (k = i; ball[i][j].number == ball[k + 1][j].number; k++)
					n2++;
			if (n2 > 2) {
				for (m = 0; m < n2; m++) {
					ball[i + m][j].sign = 1;
				}
				num++;
			}
		}
	}
	if (num == 0)
		return 0;
	else
		return 1;
}

void mark(char ball[][COL_MAX], int row, int col, int x, int y)
{
	int i, j, k, n1 = 1, m, n2 = 1;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col - 2; j += n1) {
			n1 = 1;
			if (ball[i][j] == ball[i][j + 1]) {
				for (k = j; ball[i][j] == ball[i][k + 1]; k++) {
					n1++;
				}
			}
			if (n1 > 2) {
				for (m = 0; m < n1; m++) {
					cct_showch(x + 3 * (j + m + 1), y + i, ball[i][j + m], COLOR_HYELLOW, COLOR_HBLUE, 1);
					cct_setcolor();
				}
			}
		}
	}

	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 2; i += n2) {
			n2 = 1;
			if (ball[i][j] == ball[i + 1][j])
				for (k = i; ball[i][j] == ball[k + 1][j]; k++)
					n2++;
			if (n2 > 2) {
				for (m = 0; m < n2; m++) {
					cct_showch(x + 3 * (j + 1), y + i + m, ball[i + m][j], COLOR_HYELLOW, COLOR_HBLUE, 1);
					cct_setcolor();
				}
			}
		}
	}
}

void check(struct RAND ball[10][10], int row, int col, int sel, const char* row_sign, const char* col_sign)
{
	int x, y;
	wait("按回车键进行寻找初始可消除项的操作...", 1);

	if (judge_all(ball, row, col)) {
		cout << endl;
		cout << "初始可消除项（不同色标识）：" << endl;
		mark(row, col, row_sign, col_sign, ball);
		cct_getxy(x, y);
		cct_gotoxy(x, y);
	}
	else {
		if (sel == '1' || sel == '3')
			cout << "初始已无可消除项" << endl;

		else if (sel == '2')
			cout << "初始已无可消除项，本小题无法测试，请再次运行" << endl;
	}
}
/*
void zero(char* p_ball, int row, int col)
{
	int i, j, k, n1 = 1, n2 = 1, m;
	int temp[80];
	int* p = temp;
	char t;
	
	for (i = 0; i < row; i++) {
		for (j = 0; j < col-2; j += n1) {
			n1 = 1;
			if (*(p_ball + i * 9 + j) == *(p_ball + i * 9 + j + 1)) {
				if (*(p_ball + i * 9 + j)) {
					for (k = j; *(p_ball + i * 9 + j) == *(p_ball + i * 9 + k + 1); k++) {
						n1++;
					}
				}
				else
					continue;
			}
			if (n1 > 2) {
				for (m = 0; m < n1; m++) {
					*(p++) = i * 9 + j + m;
				}
			}
		}
	}

	for (j = 0; j < col; j++) {
		for (i = 0; i < row-2; i += n2) {
			n2 = 1;
			if (*(p_ball + i * 9 + j) == *(p_ball + (i + 1) * 9 + j)) {
				if (*(p_ball + i * 9 + j)) {
					for (k = i; *(p_ball + i * 9 + j) == *(p_ball + (k + 1) * 9 + j); k++)
						n2++;
				}
				else
					continue;
			}
			if (n2 > 2) {
				for (m = 0; m < n2; m++) {
					*(p++) = (i + m) * 9 + j;
				}
			}
		}
	}

	*p = -1;
	p = temp;
	for (; *p >= 0; p++) {
		*(p_ball + *p) = '0';
	}

	for (j = 0; j < col; j++) {
		for (i = 0; i < row; i++) {
			if (*(p_ball + i * 9 + j) == '0') {
				for (k = 0; k < i; k++) {
					t = *(p_ball + (i - k) * 9 + j);
					*(p_ball + (i - k) * 9 + j) = *(p_ball + (i - k - 1) * 9 + j);
					*(p_ball + (i - k - 1) * 9 + j) = t;
				}
			}
		}
	}
}

void mark_zero(char ball[][COL_MAX], int row, int col, int x, int y)
{
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (ball[i][j] == '0')
				cct_showch(x + 3 * (j + 1), y + i, ball[i][j], COLOR_HYELLOW, COLOR_HBLUE, 1);
		}
	}
}
*/
void down(struct RAND ball[10][10], int row, int col, const char* row_sign, const char* col_sign)
{
	int x, y;
	wait("按回车键进行数组下落除0操作...", 1);
	cout << endl;
	cout << "下落除0后的数组(不同色标识)：" << endl;
	make_zero(row, col, ball);
	move_zero(row, col, ball);
	mark_zero(row, col, row_sign, col_sign, ball);
	cct_getxy(x, y);
	cct_gotoxy(x, y);
}

void fill(int row, int col, struct RAND ball[10][10], const char* row_sign, const char* col_sign)
{
	int i, j, x, y;
	int temp[80];
	int* p;
	
	p = temp;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (ball[i][j].number == '0') {
				*(p++) = i * 9 + j;
				ball[i][j].number = 49 + rand() % 9;
				ball[i][j].sign = 0;
				ball[i][j].color = 0;
				ball[i][j].zero_up = 0;
			}
		}
	}
	*p = -1;
	p = temp;
	print_table(row, col, row_sign, col_sign, ball);
	cct_getxy(x, y);
	for (; *p >= 0; p++) {
		cct_showch(2 + 3 * (*p % 9 + 1), y - row - 1 + *p / 9, ball[*p / 9][*p % 9].number, COLOR_HYELLOW, COLOR_HBLUE, 1);
	}
	cct_gotoxy(x, y);
	cct_setcolor();
}

void renew(struct RAND ball[10][10], int row, int col, const char* row_sign, const char* col_sign)
{
	wait("按回车键进行新值填充...", 1);
	cout << endl;
	cout << "新值填充后的数组(不同色标识)：" << endl;
	fill(row, col, ball, row_sign, col_sign);
	
	if (judge_all(ball, row, col)) {
		check(ball, row, col, 1, row_sign, col_sign);
		down(ball, row, col, row_sign, col_sign);
		renew(ball, row, col, row_sign, col_sign);
	}
	else {
		cout << "初始已无可消除项" << endl;
		return;
	}
}

void exchange(struct RAND ball[10][10], int row, int col, const char* row_sign, const char* col_sign)
{
	int i, j, k, x, y;
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
	cout << "可选择的消除提示（不同色标识）：" << endl;
	print_table(row, col, row_sign, col_sign, ball);
	cct_getxy(x, y);
	for (; *p >= 0; p++) {
		cct_showch(2 + 3 * (*p % 9 + 1), y - row - 1 + *p / 9, ball[*p / 9][*p % 9].number, COLOR_HYELLOW, COLOR_HBLUE, 1);
	}
	cct_gotoxy(x, y);
	cct_setcolor();
}
