/* Geme of life
 *
 * Death:
 *     1. Overpopulation - 4 or more alive neighbors
 *     2. Loneliness - 1 or fewer alive neighbors
 * Birth:
 *     Cell has 3 alive neighbors
 * Stasis:
 *     (all other cases)
 *     If cell is alive and has 2 or 3 neighbors - it stays alive
 *     If cell is dead and has anything other than 3 neighbors - it stays dead
 * */

#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#define DELAY 100

int main()
{
    initscr();
    nodelay(stdscr,TRUE);
    scrollok(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));

    int i, j, x, y, neighbors;
    int lines = LINES, columns = COLS;
    int space[lines][columns], next_gen[lines][columns];

    /* seed colony */
    srand(time(0));
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            space[i][j] = rand() % 2;
            /* space[i][j] = 0; */
            next_gen[i][j] = 0;
        }
    }

    /* glider */
    /* int a = lines / 2; */
    /* int b = columns / 2; */
    /* space[a][b] = 1; */
    /* space[a + 1][b] = 1; */
    /* space[a + 2][b] = 1; */
    /* space[a][b - 1] = 1; */
    /* space[a + 1][b - 2] = 1; */

    /* lightweight spaceship */
    /* int a = lines / 2; */
    /* int b = columns / 2; */
    /* space[a][b] = 1; */
    /* space[a + 1][b] = 1; */
    /* space[a + 2][b] = 1; */
    /* space[a + 3][b - 1] = 1; */
    /* space[a][b - 1] = 1; */
    /* space[a][b - 2] = 1; */
    /* space[a][b - 3] = 1; */
    /* space[a + 1][b - 4] = 1; */
    /* space[a + 3][b - 4] = 1; */

    /* until key press */
    while(getch() == ERR) {

        /* show me the space */
        for (i = 0; i < lines; i++)
            for (j = 0; j < columns; j++)
                space[i][j] == 1 ? addch('o') : addch(' ');

        /* wait */
        refresh();
        napms(DELAY);

        /* next generation */
        for (i = 1; i < lines - 1; i++) {
            for (j = 1; j < columns - 1; j++) {

                /* neighbors of each cell */
                neighbors = 0;
                for (x = -1; x <= 1; x++)
                    for (y = -1; y <= 1; y++)
                        neighbors += space[i + x][j + y];

                /* cell state itself */
                neighbors -= space[i][j];

                /* it's life */
                if ((space[i][j]) && (neighbors < 2)) next_gen[i][j] = 0;
                else if ((space[i][j]) && (neighbors > 3)) next_gen[i][j] = 0;
                else if ((!space[i][j]) && (neighbors == 3)) next_gen[i][j] = 1;
                else next_gen[i][j] = space[i][j];
            }
        }

        /* copy next_gen to space */
        for (i = 0; i < lines; i++)
            for (j = 0; j < columns; j++)
                space[i][j] = next_gen[i][j];
    }

    getch();
    endwin();
    return 0;
}
