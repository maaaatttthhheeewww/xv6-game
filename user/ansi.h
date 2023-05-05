inline static void ansi_var_output(char *str) { int len=0; char *s=str; for(; *s != 0; s++, len++); write(1,str,len); }
inline static void ansi_output(char *str, int len) { write(1,str,len); }

// Clear screen
#define ANSI_CLEAR ansi_output("\033[2J",4)

// Position cursor
#define ANSI_GOTOXY(X,Y) fprintf(1,"\033[%d;%dH",Y,X)

// Hide and show cursor
#define ANSI_HIDE_CUR ansi_output("\033[?25l",6)
#define ANSI_SHOW_CUR ansi_output("\033[?25h",6)

// Set foreground and background text color
#define ANSI_BG_COLOR(r,g,b) ansi_var_output("\033[48;2;"#r";"#g";"#b"m")
#define ANSI_FG_COLOR(r,g,b) ansi_var_output("\033[38;2;"#r";"#g";"#b"m")

// Set font properties
#define ANSI_BOLD ansi_output("\033[1m",4)
#define ANSI_NORMAL ansi_output("\033[22m",5)
#define ANSI_FAINT ansi_output("\033[2m",4)
#define ANSI_ITALIC ansi_output("\033[3m",4)
#define ANSI_UNDERLINE ansi_output("\033[4m",4)
#define ANSI_BLINK ansi_output("\033[5m",4)
#define ANSI_NO_BLINK ansi_output("\033[25m",5)
// font number 0-9
#define ANSI_SET_FONT(fn) ansi_output("\033[1"#fn"m",5)

// Reset all text settings back to original
#define ANSI_RESET ansi_output("\033[0m",4)

// arrow keys 
#define ANSI_KEY_UP    "\033[A"
#define ANSI_KEY_DOWN  "\033[B"
#define ANSI_KEY_RIGHT "\033[C"
#define ANSI_KEY_LEFT  "\033[D"
