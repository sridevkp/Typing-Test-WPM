#include "utils.h"
#include <stdio.h>
#include<Windows.h>

void setwindowsize(int width, int height)
{
	COORD      coord = { width, height };
    SMALL_RECT rmin  = { 0, 0, 1, 1 };
    SMALL_RECT rect  = { 0, 0, width-1, height-1 };

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(Handle, TRUE, &rmin);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &rect);
}

void setcursorvisibility(bool visible)
{
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(handler, &info);
}

void setposition( COORD pos )
{
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handler, pos);
}

void cprint(char c, COORD pos)
{
    setposition(pos);
    printf("%c",c);
}

void sprint(char* s, COORD pos)
{
    setposition(pos);
    printf("%s",s);
}

void setcolor(int fc)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (fc & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void coloredprint(char c, COORD pos, COLOR color)
{
    setcolor(color);
    setposition(pos);
    printf("%c",c);
    setcolor(WHITE);
}

void scoloredprint(char* s, COORD pos, COLOR color)
{
    setcolor(color);
    setposition(pos);
    printf("%s",s);
    setcolor(WHITE);
}

COORD getposition( int index, int WIDTH, COORD offset)
{
    int row = (index + offset.X) % WIDTH ;
    int col = (index + offset.X) / WIDTH + offset.Y;
    return (COORD){row, col};
}

void clrscr(int WIDTH, int HEIGHT)
{
    system("cls");
    // for ( int row = 0; row < HEIGHT; row++ ) 
    // {
    //     for ( int col = 0; col < WIDTH; col++ ) 
    //     {
    //         cprint(' ',(COORD){col,row});
    //     }
    // }
}