#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
int a, b, sc;
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void star(int x, int y)
{
	gotoxy(x, y);
	printf("*");
}
char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void score(int sc)
{
	gotoxy(69, 0);
	printf("%d", sc);
}
int main()
{
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20;
	int bx, by, i;
	int bullet = 0;
	draw_ship(x, y);
	int s = 1;
	do {
		int i, j;
		srand(time(NULL));
		while (s <= 20)
		{
				a = rand() % 100;
				b = rand() % 10;
			if (a >= 10 && a <= 70 && b >= 2 && b <= 5 && cursor(a, b) != '*')
			{
				star(a, b);
				s++;
			}
		}
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0) { draw_ship(--x, y); }
			if (ch == 's' && x < 80) { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}
		if (bullet == 1) {
			clear_bullet(bx, by);
			if (cursor(bx, by - 1) == '*')
			{
				draw_bullet(bx, --by);
				clear_bullet(bx, by);
				Beep(700, 100);
				by = 2;
				sc++;
				s = 20;
			}
			if (by == 2) { bullet = 0; }
			else
			{
				draw_bullet(bx, --by);
			}
		}
		score(sc);
		Sleep(100);
	} while (ch != 'x');
	return 0;
}