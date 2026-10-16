#pragma once
/* 2352475 计科 易阳 */

#define ROW_MAX 9
#define COL_MAX 9
#define ROW_MIN 5
#define COL_MIN 5

/*与内部数组有关的函数*/
int judge_all(struct RAND ball[10][10], int row, int col);
void mark_zero        (char ball[][COL_MAX], int row, int col, int x, int y);
void check(struct RAND ball[10][10], int row, int col, int sel, const char* row_sign, const char* col_sign);
void zero             (char* p_ball, int row, int col);
void down(struct RAND ball[10][10], int row, int col, const char* row_sign, const char* col_sign);
void fill(int row, int col, struct RAND ball[10][10], const char* row_sign, const char* col_sign);
void renew(struct RAND ball[10][10], int row, int col, const char* row_sign, const char* col_sign);
void exchange(struct RAND ball[10][10], int row, int col, const char* row_sign, const char* col_sign);
void wait             (const char* prompt, int choice);

/*与伪图形界面有关的函数*/
void print_check(struct RAND ball[10][10], int row, int col, int* p_bomb);
int print_disappear(struct RAND ball[10][10], int row, int col, int bomb[]);
void print_fill(struct RAND ball[10][10], int row, int col);
int print_exchange(struct RAND ball[10][10], int row, int col, int* p_note);

/*判断鼠标选择的相关函数*/
int choice            (int X, int Y, int note[]);
int location(struct RAND ball[10][10], int row, int col, int y, int sel, int note[]);

/*与游戏记录有关的函数*/
int game(struct RAND ball[10][10], int row, int col, int y, int* p_note, int note[], int* p_bomb, int bomb[], const char* unit);