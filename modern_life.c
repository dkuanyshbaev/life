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

#define BABY_COLOR 1
#define ADULT_COLOR 2
#define OLD_COLOR 3
#define NORMAL_COLOR 2

#define DELAY 100
#define CELL 'o'
#define BABY 4
#define ADULT 64
#define COLOR_LIFE 1

typedef struct {
    int alive;
    int age;
} cell;

void seed_colony(int l, int c, cell[l][c], cell[l][c]);
void show_me_the_space(int l, int c, cell[l][c]);
void next_generation(int l, int c, cell[l][c], cell[l][c]);
void space_copy(int l, int c, cell[l][c], cell[l][c]);

int main()
{
    initscr();
    start_color();
    nodelay(stdscr,TRUE);
    scrollok(stdscr, TRUE);

    init_pair(BABY_COLOR, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(ADULT_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(OLD_COLOR, COLOR_BLUE, COLOR_BLACK);
    if (COLOR_LIFE)
        bkgd(COLOR_PAIR(BABY_COLOR));
    else
        bkgd(COLOR_PAIR(NORMAL_COLOR));

    cell space[LINES][COLS], next_gen[LINES][COLS];
    seed_colony(LINES, COLS, space, next_gen);

    while(getch() == ERR) {
        show_me_the_space(LINES, COLS, space);
        refresh();
        napms(DELAY);
        next_generation(LINES, COLS, space, next_gen);
        space_copy(LINES, COLS, next_gen, space);
    }

    getch();
    endwin();
    return 0;
}

void seed_colony(int l, int c, cell space[l][c], cell next_gen[l][c])
{
    int i, j;
    cell citizen = {.age = 0};
    cell empty_cell = {.alive = 0, .age = 0};

    srand(time(0));
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            citizen.alive = rand() % 2;
            space[i][j] = citizen;
            next_gen[i][j] = empty_cell;
        }
    }
}

void show_me_the_space(int l, int c, cell space[l][c])
{
    int i, j;

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            if (space[i][j].alive) {
                if (COLOR_LIFE) {
                    if ((space[i][j].age > 0) && (space[i][j].age < BABY))
                        attron(COLOR_PAIR(BABY_COLOR));
                    else if ((space[i][j].age >= BABY) && (space[i][j].age < ADULT))
                        attron(COLOR_PAIR(ADULT_COLOR));
                    else if (space[i][j].age >= ADULT)
                        attron(COLOR_PAIR(OLD_COLOR));
                }
                addch(CELL);
                if (COLOR_LIFE)
                    attron(COLOR_PAIR(BABY_COLOR));
            } else
                addch(' ');
        }
    }
}

void next_generation(int l, int c, cell space[l][c], cell next_gen[l][c])
{
    int i, j, x, y, neighbors;

    for (i = 1; i < l - 1; i++) {
        for (j = 1; j < c - 1; j++) {

            /* neighbors of each cell */
            neighbors = 0;
            for (x = -1; x <= 1; x++)
                for (y = -1; y <= 1; y++)
                    neighbors += space[i + x][j + y].alive;

            /* cell state itself */
            neighbors -= space[i][j].alive;

            /* it's life */
            if (space[i][j].alive && (neighbors < 2)) {
                /* Death */
                next_gen[i][j].alive = 0;
            }
            else if (space[i][j].alive && (neighbors > 3)) {
                /* Death */
                next_gen[i][j].alive = 0;
            }
            else if (!space[i][j].alive && (neighbors == 3)) {
                /* Birth */
                next_gen[i][j].alive = 1;
                next_gen[i][j].age = 0;
            }
            else {
                /* Stasis */
                next_gen[i][j] = space[i][j];
                next_gen[i][j].age++;
            }
        }
    }
}

void space_copy(int l, int c, cell from[l][c], cell to[l][c])
{
    int i, j;

    for (i = 0; i < l; i++)
        for (j = 0; j < c; j++)
            to[i][j] = from[i][j];
}
