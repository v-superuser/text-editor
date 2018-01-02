#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

void Signal_Handler(int SignalCaught)
{
    if(SignalCaught==SIGWINCH)
    {
        struct winsize ws;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
        printf ("Line Width:- %d\n", ws.ws_row);
        printf ("Column Width:- %d\n", ws.ws_col);
    }
}

int main()
{  
    signal(SIGWINCH,Signal_Handler);
    return EXIT_SUCCESS;
}
