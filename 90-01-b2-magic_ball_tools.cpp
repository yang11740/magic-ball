/* 2352475 计科 易阳 */
#include <iostream>
#include <time.h>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/common-popstar_ball.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

int choice(int X, int Y, int note[])
{
	int i, j, k;
	i = (Y - 2) / 2;
	j = (X - 2) / 4;
	for (k = 0; note[k] >= 0; k++) {
		if ((i * 9 + j) == note[k])
			return 1;
	}
	return 0;
}

int test(int* p1, int* p2, struct RAND ball[10][10],int row,int col)
{
	int i, j, k, n1 = 1,n2 = 1;
	char t;
	t = ball[*p1 / 9][*p1 % 9].number;
	ball[*p1 / 9][*p1 % 9].number = ball[*p2 / 9][*p2 % 9].number;
	ball[*p2 / 9][*p2 % 9].number = t;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col - 2; j += n1) {
			n1 = 1;
			if (ball[i][j].number == ball[i][j + 1].number) {
				for (k = j; ball[i][j].number == ball[i][k + 1].number; k++) {
					n1++;
				}
			}
			if (n1 > 2) {
				return 1;
			}
		}
	}

	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 2; i += n2) {
			n2 = 1;
			if (ball[i][j].number == ball[i + 1][j].number)
				for (k = i; ball[i][j].number == ball[k + 1][j].number; k++)
					n2++;
			if (n2 > 2) {
				return 1;
			}
		}
	}
	t = ball[*p1 / 9][*p1 % 9].number;
	ball[*p1 / 9][*p1 % 9].number = ball[*p2 / 9][*p2 % 9].number;
	ball[*p2 / 9][*p2 % 9].number = t;
	return 0;
}
int location(struct RAND ball[10][10], int row, int col,int y,int sel,int note[])
{
	int X = 0, Y = 0;
	int maction, n, ret;
	int keycode1, keycode2;
	int num[ROW_MAX][COL_MAX] = { 0 };
	int temp[3];
	int* p = temp;
	
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);
	while (1) {
		cct_gotoxy(0, y + 1);
		cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if ((X - 2) / 4 >= 0 && (X - 2) / 4 < col && (Y - 2) / 2 >= 0 && (Y - 2) / 2 < row && ((X - 2) % 4 == 0 || (X - 2) % 4 == 1) && (Y - 2) % 2 == 0) {
			cct_setcolor();
			cout << "[当前光标]  " << (char)('A' + (Y - 2) / 2) << "行" << (X - 2) / 4 + 1 << "列       ";
			n = 1;
			if ((X - 2) % 4 == 1)
				X--;
		}
		else {
			cct_setcolor();
			cout << "[当前光标]  位置非法                    ";
			n = 0;
		}
		if (n) {
			switch (maction) {
				case MOUSE_LEFT_BUTTON_CLICK:
					if (choice(X, Y, note)) {
						cct_gotoxy(0, y + 1);
						cct_setcolor();
						cout << "选择" << (char)('A' + (Y - 2) / 2) << "行" << (X - 2) / 4 + 1 << "列          ";
						if (sel == '8') {
							Sleep(300);
							cct_disable_mouse();
							cct_setcursor(CURSOR_VISIBLE_NORMAL);
							return 0;
						}
						if (sel == '9') {
							Sleep(200);
							num[(Y - 2) / 2][(X - 2) / 4]++;
							if (num[(Y - 2) / 2][(X - 2) / 4] % 2 == 1) {
								cct_showstr(X, Y, "◎", ball[(Y - 2) / 2][(X - 2) / 4].number, COLOR_HWHITE, 1);
								if (1) {
									if (p == temp) {
										*(p++) = ((Y - 2) / 2) * 9 + (X - 2) / 4;
										break;
									}
									if (p - temp == 1) {
										*p = ((Y - 2) / 2) * 9 + (X - 2) / 4;
										if (temp[0] / 9 - temp[1] / 9 == 1 || temp[0] / 9 - temp[1] / 9 == -1 || temp[0] % 9 - temp[1] % 9 == 1 || temp[0] % 9 - temp[1] % 9 == -1) {
											ret = test(&temp[0], &temp[1], ball, row, col);
											if (ret) {
												cct_showstr(X, Y, "○", ball[(Y - 2) / 2][(X - 2) / 4].number, COLOR_BLACK, 1);
												cct_showstr(temp[0] % 9 * 4 + 2, temp[0] / 9 * 2 + 2, "○", ball[temp[0] / 9][temp[0] % 9].number, COLOR_BLACK, 1);
												p = temp;
												return 1;
											}
											else {
												cct_setcolor();
												cct_gotoxy(0, y + 1);
												cout << "不能交换" << (char)('A' + temp[0] / 9) << "行" << temp[0] % 9 + 1 << "列<=>" << (char)('A' + temp[1] / 9) << "行" << temp[1] % 9 + 1 << "列   ";
												Sleep(200);
												p = temp;
												return 0;
											}
										}
										else {
											p = temp;
											cct_showstr(temp[0] % 9 * 4 + 2, temp[0] / 9 * 2 + 2, "◎", ball[temp[0] / 9][temp[0] % 9].number, COLOR_BLACK, 1);
											continue;
										}
									}
								}
							}
							else {
								cct_showstr(X, Y, "◎", ball[(Y - 2) / 2][(X - 2) / 4].number, COLOR_BLACK, 1);
							}
							break;
						}
					}
					else {
						cct_gotoxy(0, y + 1);
						cct_setcolor();
						cout << "不能选择" << (char)('A' + (Y - 2) / 2) << "行" << (X - 2) / 4 + 1 << "列         ";
						Sleep(100);
					}
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:
					cct_setcursor(CURSOR_VISIBLE_NORMAL);
					return -1;
				default:
					break;
			}
		}
	}
}

int game(struct RAND ball[10][10], int row, int col, int y, int* p_note,int note[],int* p_bomb,int bomb[],const char* unit)
{
	int ret1, ret2 = 0, score = 0;
	int i;
	while (1) {
		cct_gotoxy(0, 0);
		cct_setcolor();
		cout << "当前分数：" << score << " 右键退出              ";
		ret1 = print_exchange(ball, row, col, p_note);
		if (ret1) {
			ret2 = location(ball, row, col, y, '9', note);
			while (judge_all(ball, row, col)) {
				print_check(ball, row, col, p_bomb);
				score += print_disappear(ball, row, col, bomb);
				cct_gotoxy(0, 0);
				cct_setcolor();
				cout << "当前分数：" << score << " 右键退出             ";

				print_move(row, col, ball, NULL, unit, 1, 2, 1, 0);
				print_fill(ball, row, col);
				for (i = 0; note[i] >= 0; i++)
					cct_showstr(2 + 4 * (note[i] % 9), 2 + 2 * (note[i] / 9), "○", ball[note[i] / 9][note[i] % 9].number, COLOR_BLACK, 1);
			}
		}
		if (ret1 == 0) {
			cct_gotoxy(0, 0);
			cct_setcolor();
			cout << "最终分数：" << score;
			return 1;
		}
		if (ret2 == -1) {
			return 0;
		}
	}
}