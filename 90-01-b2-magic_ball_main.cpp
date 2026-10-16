/* 2352475 计科 易阳 */
#include <iostream>
#include "../include/cmd_console_tools.h"
#include "../include/common-popstar_ball.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

int main()
{
	int row, col, x, y, ret, r, high, length;
	char sel;
	RAND ball[10][10];
	int note[80] = { 0 };
	int bomb[80] = { 0 };
	int* p_note = note;
	int* p_bomb = bomb;
	const char *InputMenu[65] = { 
		"1.内部数组，生成初始状态，寻找是否有初始可消除项",
		"2.内部数组，消除初始可消除项后非0项下落并用0填充",
		"3.内部数组，消除初始可消除项后查找消除提示",
		"4.n*n的框架(无分隔线)，显示初始状态",
		"5.n*n的框架(有分隔线)，显示初始状态",
		"6.n*n的框架(无分隔线)，显示初始状态及初始可消除项",
		"7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示",
		"8.cmd图形界面完整版(有分隔线，鼠标移动时显示坐标，右键退出)",
		"9.cmd图形界面完整版",
		"0.退出",
		NULL
	};
	const char* choice = "1234567890";
	const char* row_sign = "ABCDEFGHI";
	const char* col_sign = "123456789";
	const char* unit = "○";
	const char* frame1[12] = { "╔","╦","╗","╠","╬","╣","╚","╩","╝","═","║" };
	
	while (1) {
		cct_setconsoleborder(90, 30, 120, 9000);
		cct_setfontsize("新宋体", 26);
		sel = menu(InputMenu, choice);
		if (sel == '1' || sel == '2' || sel == '3') {
			cct_cls();
			input(&row, &col, ROW_MIN, ROW_MAX, COL_MIN, COL_MAX);
			produce(row, col, 9, ball);
			cout << "初始数组：" << endl;
			print_table(row, col, row_sign, col_sign, ball);
			check(ball, row, col, sel, row_sign, col_sign);
			if (sel == '2' || sel == '3') {
				if (judge_all(ball, row, col)) {
					down(ball, row, col, row_sign, col_sign);
					renew(ball, row, col, row_sign, col_sign);
				}
				if (sel == '3') {
					exchange(ball, row, col, row_sign, col_sign);
				}
			}
			wait(" ", 0);
		}
		else if (sel == '4' || sel == '5' || sel == '6' || sel == '7' || sel == '8' || sel == '9') {
			cct_cls();
			input(&row, &col, ROW_MIN, ROW_MAX, COL_MIN, COL_MAX);
			produce(row, col, 9, ball);
			cout << "初始数组：" << endl;
			print_table(row, col, row_sign, col_sign, ball);
			wait("按回车键显示图形...", 1);
			cct_cls();
			cct_setfontsize("新宋体", 40);
			print_frame(row, col, ball, 0, frame1, sel - '4', 1, 2);
			cct_getxy(x, y);
			print_unit(row, col, ball, NULL, unit, &high, &length, sel - '4', 0, COLOR_BLACK);
			if (sel == '6') {
				print_check(ball, row, col, p_bomb);
			}
			if (sel == '7' || sel == '8') {
				while (judge_all(ball, row, col)) {
					print_check(ball, row, col, p_bomb);
					if (sel == '7') {
						cct_gotoxy(0, y + 1);
						wait("按回车键进行消除及下落除0操作...", 1);
					}
					print_disappear(ball, row, col, bomb);
					print_move(row, col, ball, NULL, unit, 1, 2, 1, 0);
					if (sel == '7') {
						cct_gotoxy(0, y + 1);
						cout << "                                ";
						cct_gotoxy(0, y + 1);
						wait("按回车键进行新值填充...", 1);
					}
					print_fill(ball, row, col);
				}
				if (sel == '7') {
					cct_gotoxy(0, 0);
					cct_setcolor();
					cout << "未找到初始可消除项            ";
					cct_gotoxy(0, y + 1);
					cout << "                                ";
					cct_gotoxy(0, y + 1);
					cct_setcolor();
					wait("按回车键显示消除提示...", 1);
				}
				ret = print_exchange(ball, row, col, p_note);
				if (sel == '8') {
					cct_gotoxy(0, 0);
					cct_setcolor();
					if (ret) {
						cout << "（当前分数：0 右键退出）" << endl;
						location(ball, row, col, y, sel, note);
					}
					else {
						cout << "无可消除项，游戏结束！" << endl;
					}
				}
			}
			if (sel == '9') {
				while (judge_all(ball, row, col)) {
					print_check(ball, row, col, p_bomb);
					print_disappear(ball, row, col, bomb);
					print_move(row, col, ball, NULL, unit, 1, 2, 1, 0);
					print_fill(ball, row, col);
				}
				print_exchange(ball, row, col, p_note);
				r = game(ball, row, col, y, p_note, note, p_bomb, bomb, unit);
				if (r) {
					cout << "(无可消除项，游戏结束！)";
				}
			}
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			cct_gotoxy(0, y + 1);
			wait(" ", 0);
		}
		else
			return 0;
	}
}