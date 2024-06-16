#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>
#include <time.h>
#include "utils.h"

#define WIDTH 50
#define HEIGHT 20
#define MAX_INPUT_LENGTH 150

void drawtitle();
void printtext( char target[], char input[] );
void printinfo( bool completed, int WPM, double timetaken );
void reset();
int wpm( int charlen, double dt );

const COORD testoff = {5,8};
bool completed , started ;
char target[MAX_INPUT_LENGTH], input[MAX_INPUT_LENGTH+1] ;
int inpindex ;

int main()
{
    SetConsoleTitle("Typing Test");
    setwindowsize(WIDTH, HEIGHT);
    setcursorvisibility(false);
    reset();

    clock_t starttime, endtime;
    
    while(true)
    {
        if( completed )
        {
            endtime = time(NULL);
            double dt = difftime(endtime, starttime);
            int WPM = wpm( strlen(input), dt );

            printinfo(completed, WPM, dt);

            printtext( target, input );
            Sleep(10);
            getch();
            reset();
        }
        clrscr(WIDTH, HEIGHT);
        drawtitle();
        printtext( target, input );

        if( started )
        {
            endtime = time(NULL);
            double dt = difftime(endtime, starttime);
            int WPM = wpm( strlen(input), dt );

            printinfo(completed, WPM, dt);
        }

        const int inp = getch();

        switch (inp)
        {
            case 27:
                reset();
                break;
            case 8:
                if(inpindex == 0) break;
                input[--inpindex] = '\0';
                break;
            case 13:
                break;
            default:
                if(inpindex == MAX_INPUT_LENGTH) break;
                if( !started ){
                    started = true;
                    starttime = time(NULL);
                } 
                input[inpindex++] = (char)inp;
                input[inpindex] = '\0';
                break;
        }

    }

    return 0;
}

int wpm( int charlen, double dt )
{
    return  (charlen/6) / dt *60  ;
}

void reset()
{
    completed = false;
    started = false;
    inpindex = 0 ;
    strcpy(target, "A quick brown fox jumps over the lazy dog near the quaint village swiftly grabbing vexed zebras while enjoying xylophone tunes played by jovial knight");
    memset(input, 0, sizeof(input) );
}

void printinfo( bool completed, int WPM, double timetaken)
{
    char ttstrbuffer[30] ;
    sprintf(ttstrbuffer, "Time Taken : %.0lf sec", timetaken );
    scoloredprint(ttstrbuffer, (COORD){0,HEIGHT-2}, DARKMAGENTA );

    char wpmstrbuffer[30] ;
    sprintf(wpmstrbuffer, "WPM : %d", WPM );
    scoloredprint(wpmstrbuffer, (COORD){0,HEIGHT-3}, DARKMAGENTA );

    if( completed )
        scoloredprint("Completed!", (COORD){0,HEIGHT-4}, WHITE );
    
}

void printtext( char target[], char input[] )
{
    int cindex ;
    int charindex = 0;
    for( cindex = 0; cindex < strlen(input); cindex++ )
    {
        if( input[cindex] != target[cindex] ) break;
        coloredprint(input[cindex], getposition(charindex, WIDTH, testoff), GREEN );
        charindex++;
    }
    for(int c = cindex; c < strlen(input); c++){
        coloredprint(input[c], getposition(charindex, WIDTH, testoff), RED );
        charindex++;
    }
    completed = strlen(target) == cindex+1;
    for(;cindex<strlen(target); cindex++ )
    {
        coloredprint(target[cindex], getposition( charindex, WIDTH, testoff), BLUE);
        charindex++;
    }
}

void drawtitle()
{
    scoloredprint("##################################################", (COORD){0,0}, YELLOW);
    scoloredprint("#    ____       ____   ____ ____   ___  ____     #", (COORD){0,1}, YELLOW);
    scoloredprint("#     ||  \\\\// ||_||    ||  ||__  ||__   ||      #", (COORD){0,2}, YELLOW);
    scoloredprint("#     ||   ||  ||       ||  ||__   __||  ||      #", (COORD){0,3}, YELLOW);
    scoloredprint("##################################################", (COORD){0,4}, YELLOW);
    scoloredprint("Press ESC to reset", (COORD){0,HEIGHT-1}, GRAY);
}



