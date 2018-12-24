#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

typedef struct _ant {
  int x, y;
  char state;
} ant;
void mur ();
void goforward ();

int main () {
    struct winsize win;
    ioctl (STDOUT_FILENO, TIOCGWINSZ, &win);
    int h = win.ws_row;
    int w = win.ws_col;
    int step = 1;

    ant m1 = {80, 30, 0};
    ant m2 = {81, 30, 1};
    ant m3 = {81, 31, 2};
    //ant m4 = {80, 31, 3};
    char* screen = (char*) calloc ( w * (h - 1) + 1, sizeof(char));
    for (int i = 0; i < w * (h - 1); i++)
    screen[i] = ' ';
    screen[w * (h - 1)] = '\0';
    printf("\n");
    for (int i = 0; /*i < 10000*/ ; i++) {
        mur (&m1, &screen[m1.y * w + m1.x]);
        mur (&m2, &screen[m2.y * w + m2.x]);
        mur (&m3, &screen[m3.y * w + m3.x]);
        //mur (&m4, &screen[m4.y * w + m4.x]);

        puts (screen);
        printf("step = %d\n", step);
        step++;
        usleep (100000);
    }
    return 0;
}

void mur (ant* m, char* clr) {
    if (*clr == ' ') {
        m->state = (m->state + 1 <= 3) ? m->state + 1 : 0;
        *clr = '#';
        goforward (m);
        return;
    }
    if (*clr == '#') {
        m->state = (m->state - 1 >= 0) ? m->state - 1 : 3;
        *clr = ' ';
        goforward (m);
        return;
    }
}

void goforward (ant* m) {
    switch (m->state) {
        case 0: {
            m->y--;
            break;
        }
        case 1: {
            m->x++;
            break;
        }
        case 2: {
            m->y++;
            break;
        }
        case 3: {
            m->x--;
            break;
        }
    }
}
