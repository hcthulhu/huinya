#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

typedef struct Point
{
  int x, y;
  char state;
  char dig;
} ant;

void mur ();
void GoForward ();
void PrintState ();

int main ()
{
  struct winsize win;
  ioctl (STDOUT_FILENO, TIOCGWINSZ, &win);
  int h = win.ws_row;
  int w = win.ws_col;

  int step = 1;

  char* screen = (char*) calloc ( w * (h - 1) + 1, sizeof(char));
  for (int i = 0; i < w * (h - 1); i++)
    screen[i] = ' ';
  screen[w * (h - 1)] = '\0';

  ant m = {80, 30, 3, 0};

  m.dig = screen[m.y * w + m.x];
  printf("\n");
  for (int i = 0; i < 150; i++)
  {
    mur (w, &m, screen);
    puts (screen);
    printf("step = %d dick = %c\n", step, m.dig);
    step++;
    usleep (50000);
  }
  return 0;
}

void mur (int w, ant* m, char* screen)
{

  if ( (m->dig == ' ') || (m->dig == '.') )
  {
    m->state = (m->state + 1 <= 3) ? m->state + 1 : 0;
    screen[m->y * w + m->x] = '#';
    GoForward (m);
    m->dig = screen[m->y * w + m->x];
    PrintState (m, screen, w);
    return;
  }
  if (m->dig == '#')
  {
    m->state = (m->state - 1 >= 0) ? m->state - 1 : 3;
    screen[m->y * w + m->x] = '.';
    GoForward (m);
    m->dig = screen[m->y * w + m->x];
    PrintState (m, screen, w);
    return;
  }
}

void GoForward (ant* m)
{
  switch (m->state)
  {
    case 0:
    {
      m->y--;
      break;
    }
    case 1:
    {
      m->x++;
      break;
    }
    case 2:
    {
      m->y++;
      break;
    }
    case 3:
    {
      m->x--;
      break;
    }
  }
}
//printf ("↑"); // → ↓ ←
void PrintState (ant* m, char* screen, int w) {
  switch (m->state) {
    case 0: {
        screen[m->y * w + m->x] = 'A';
        break;
    }
    case 1: {
        screen[m->y * w + m->x] = '>';
        break;
    }
    case 2: {
        screen[m->y * w + m->x] = 'V';
        break;
    }
    case 3: {
        screen[m->y * w + m->x] = '<';
        break;
    }
  }
}
