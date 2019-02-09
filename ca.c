#include <ncurses.h>
#define DELAY 42
#define GEN_MULT 80
#define RSET_SIZE 8
#define RULSET 190

/* best tuts:
 * 9 18 27 28 30 41 43 45 46 50 54 57 60
 * 61 62 69 70 73 75 77 78 84 86 89 90
 *
 * 190 222 */

/* class 1 - constant (222)
 * class 2 - oscillation (190)
 * class 3 - random (30)
 * class 4 - 2 x 3 (110) */

void dec2ruleset(int *ruleset, int n)
{
    int remainder, r = 0;
    long binary = 0, i = 1;

    while (n != 0) {
        remainder = n % 2;
        n = n / 2;
        binary = binary + (remainder * i);
        i = i * 10;

        /* fill ruleset array */
        ruleset[r] = remainder;
        r++;
    }
}

int rule(int *ruleset, int a, int b, int c)
{
    int index;

    /* TODO: upgrade it! */
    if (a == 0 && b == 0 && c == 0) index = 0;
    if (a == 0 && b == 0 && c == 1) index = 1;
    if (a == 0 && b == 1 && c == 0) index = 2;
    if (a == 0 && b == 1 && c == 1) index = 3;
    if (a == 1 && b == 0 && c == 0) index = 4;
    if (a == 1 && b == 0 && c == 1) index = 5;
    if (a == 1 && b == 1 && c == 0) index = 6;
    if (a == 1 && b == 1 && c == 1) index = 7;

    return ruleset[index];
}

int main()
{
    initscr();
    scrollok(stdscr, TRUE);

    int colony_size = COLS;
    int generations = LINES;
    int cells[colony_size], next_gen[colony_size];
    int i, g, ruleset[RSET_SIZE];

    /* ncurses colors */
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));

    /* fill ruleset from decimal */
    dec2ruleset(ruleset, RULSET);

    /* seed colony */
    for (i = 0; i < colony_size; i++) {
        cells[i] = 0;
        next_gen[i] = 0;
    }
    cells[colony_size / 2] = 1;

    /* calc generations and print to screen */
    for (g = 0; g < generations * GEN_MULT - 1; g++) {

        /* print generation */
        for (i = 0; i < colony_size; i++)
            cells[i] == 1 ? addch('*') : addch(' ');

        /* wait */
        refresh();
        napms(DELAY);

        /* next generation */
        for (i = 1; i < colony_size - 1; i++)
            next_gen[i] = rule(ruleset, cells[i - 1], cells[i], cells[i + 1]);

        /* copy next_gen to cells */
        for (i = 0; i < colony_size; i++)
            cells[i] = next_gen[i];
    }

    getch();
    endwin();
    return 0;
}
