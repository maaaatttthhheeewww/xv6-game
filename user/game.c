#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/console.h"
#include "kernel/ioctl.h"
#include "user/user.h"
#include "user/ansi.h"

#define NCOLS (80)
#define NROWS (24)

int
main(int argc, char *argv[])
{
  char in=0;
  int res=0;
  int x=10,y=10;
  int dy=0,dx=1;

  /* set console into non-blocking non-echoing mode */
  ioctl(0, _IO(CONSOLE_SETFL, CONSOLE_FL_NONBLOCK | CONSOLE_FL_NOECHO), 0);
  
  ANSI_HIDE_CUR;
  ANSI_CLEAR;

  do {
    /* !!!!!!! UNCOMMENT THE FOLLOWING LINE TO TEST YOUR ANSWER FOR Q3 !!!!!!!! */  
    res = read(0,&in,1);
    if (res > 0) {
      switch (in) {
         case 'w':
         case 'W':
                 dy = -1; dx = 0;
		 break;
         case 'a':
         case 'A':
                 dy = 0; dx = -1;
                 break;
         case 's':
         case 'S':
                 dy = 1; dx = 0; 
                 break;
         case 'd':
         case 'D':
                 dy = 0; dx = 1;
                 break;		 
      }
    }

    sleep(1);
    
    ANSI_GOTOXY(x,y);
    fprintf(1," ");

    x=x + dx;
    if( x < 1 ) x = NCOLS;
    if( x > NCOLS ) x = 1;

    y=y + dy;
    if( y < 1 ) y = NROWS;
    if( y > NROWS ) y = 1;

    ANSI_GOTOXY(x,y);
    fprintf(1,"@");

  } while (in != '\n');

  /* revert console into the normal mode of operation (blocking line-based input, echoing) */
  ioctl(0, _IO(CONSOLE_SETFL,0), 0);

  ANSI_RESET;
  ANSI_CLEAR;
  ANSI_GOTOXY(1,1);
  ANSI_SHOW_CUR;
  exit(0);
}
