#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

const double G = 124707.658145, T = 0.0000001, PI = 3.14159265358979323846;
const char TAIL = '.';

typedef struct Point {
    double x, y, vx, vy, m;
    char dig;
} planet;

void CalcCenter (planet p1, planet p2, planet p3, planet* c, char* screen, int w, int h);
void Calc3 (planet* p1, planet* p2, planet* p3, char* screen, int w, int h);
void Calc2 (planet* p1, planet* p2, char* screen, int w);
void PrintState (planet* p, char* screen, int w, int h, char c) ;


int main () {
    struct winsize win;
    ioctl (STDOUT_FILENO, TIOCGWINSZ, &win);
    int h = win.ws_row;
    int w = win.ws_col;
    char* screen = (char*) calloc ( w * (h - 1) + 1, sizeof(char));

    planet p1 = {70, 20, 600, 0, 100, 'O'};
    planet p2 = {70 + 30*tan(PI/6), 50, -300, 600*cos(PI/6), 100, 'o'};
    planet p3 = {70 - 30*tan(PI/6), 50, -300, -600*cos(PI/6), 100, '*'};

    // planet p1 = {120, 40, 0, 3000, 1200, 'O'};
    // planet p2 = {130, 40, 0, -1970, 1000, 'o'};
    // planet p3 = {125, 40, -4000, 0, 1500, '*'};
    planet c = {0, 0, 0, 0, 0, 'X'};

    for (int i = 0; i < w * (h); i++)
    screen[i] = ' ';
    screen[w * (h - 1)] = '\0';
    printf("\n");

    for (int i = 0; ; i++) {
        //Calc2 (&p1, &p2, screen, w);
        Calc3 (&p1, &p2, &p3, screen, w, h);
        CalcCenter (p1, p2, p3, &c, screen, w, h);
        PrintState (&p1, screen, w, h, p1.dig);
        PrintState (&p2, screen, w, h, p2.dig);
        PrintState (&p3, screen, w, h, p3.dig);
        PrintState (&c, screen, w, h, c.dig);
        if (i % (int)(1 / (100 * T)) == 0) {
            puts (screen);
            //printf("%d\n", i);
            // printf("1: x:%lg y:%lg vx:%lg vy:%lg \n", p1.x, p1.y, p1.vx, p1.vy );
            // printf("2: x:%lg y:%lg vx:%lg vy:%lg \n", p2.x, p2.y, p2.vx, p2.vy );
            // printf("3: x:%lg y:%lg vx:%lg vy:%lg \n", p3.x, p3.y, p3.vx, p3.vy );
            usleep (50000);
        }
    }
    return 0;
}

void Calc3 (planet* p1, planet* p2, planet* p3, char* screen, int w, int h) {
    PrintState (p2, screen, w, h, TAIL);
    PrintState (p1, screen, w, h, TAIL);
    PrintState (p3, screen, w, h, TAIL);
    double rr12 = (p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y);
    double rr13 = (p3->x - p1->x) * (p3->x - p1->x) + (p3->y - p1->y) * (p3->y - p1->y);
    double rr32 = (p2->x - p3->x) * (p2->x - p3->x) + (p2->y - p3->y) * (p2->y - p3->y);
    double F12 = (G * p1->m * p2->m) /(rr12);
    double F13 = (G * p1->m * p3->m) /(rr13);
    double F32 = (G * p3->m * p2->m) /(rr32);
    double cosx12 = (p2->x - p1->x) / sqrt(rr12);
    double cosx13 = (p3->x - p1->x) / sqrt(rr13);
    double cosx32 = (p3->x - p2->x) / sqrt(rr32);
    double cosy12 = (p2->y - p1->y) / sqrt(rr12);
    double cosy13 = (p3->y - p1->y) / sqrt(rr13);
    double cosy32 = (p3->y - p2->y) / sqrt(rr32);
    p1->vx += ((+F12 * cosx12 + F13 * cosx13) / fabs(p1->m)) * T;
    p2->vx += ((-F12 * cosx12 + F32 * cosx32) / fabs(p2->m)) * T;
    p1->vy += ((+F12 * cosy12 + F13 * cosy13) / fabs(p1->m)) * T;
    p2->vy += ((-F12 * cosy12 + F32 * cosy32) / fabs(p2->m)) * T;
    p3->vx += ((-F32 * cosx32 - F13 * cosx13) / fabs(p3->m)) * T;
    p3->vy += ((-F32 * cosy32 - F13 * cosy13) / fabs(p3->m)) * T;
    p1->x += p1->vx * T;
    p2->x += p2->vx * T;
    p1->y += p1->vy * T;
    p2->y += p2->vy * T;
    p3->x += p3->vx * T;
    p3->y += p3->vy * T;
    //printf("1: %lg %lg",cos, sin (acos (cos)) );
    //printf("1: x:%lg y:%lg vx:%lg vy:%lg ",F32 * cosx32, F13 * cosy13,F12 * cosy12, -F12 * cosy12 );
    //printf("2: x:%lg y:%lg vx:%lg vy:%lg ", p2->x, p2->y, p2->vx, p2->vy );
}

void Calc2 (planet* p1, planet* p2, char* screen, int w) {
    screen[((int) (p1->y + 0.5)) * w + (int) (p1->x + 0.5)] = ' ';
    screen[((int) (p2->y + 0.5)) * w + (int) (p2->x + 0.5)] = ' ';
    double rr = (p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y);
    double F = (G * p1->m * p2->m) / (rr);
    double cosx = (p2->x - p1->x) / sqrt(rr);
    double cosy = (p2->y - p1->y) / sqrt(rr);
    double Fx = F * cosx + 10000000;
    double Fy = F * cosy;
    p1->vx += (Fx / p1->m) * T;
    p2->vx -= (Fx / p2->m) * T;
    p1->vy += (Fy / p1->m) * T;
    p2->vy -= (Fy / p2->m) * T;
    p1->x += p1->vx * T;
    p2->x += p2->vx * T;
    p1->y += p1->vy * T;
    p2->y += p2->vy * T;
    //printf("1: %lg %lg",cos, sin (acos (cos)) );
    //printf("1: x:%lg y:%lg vx:%lg vy:%lg ", p1->x, p1->y, p1->vx, p1->vy );
    //printf("2: x:%lg y:%lg vx:%lg vy:%lg ", p2->x, p2->y, p2->vx, p2->vy );
}

void CalcCenter (planet p1, planet p2, planet p3, planet* c, char* screen, int w, int h) {
    PrintState (c, screen, w, h, '+');
    c->x = ((p1.x * p1.m) + (p2.x * p2.m) + (p3.x * p3.m)) / (p1.m + p2.m + p3.m);
    c->y = ((p1.y * p1.m) + (p2.y * p2.m) + (p3.y * p3.m)) / (p1.m + p2.m + p3.m);
}

void PrintState (planet* p, char* screen, int w, int h, char c) {
    int n = ((int) (p->y + 0.5)) * w + (int) (2*p->x + 0.5);
    if (p->y > 0 && p->y < h && p->x > 0 && p->x * 2 < w)
        screen[n] = c;
}
