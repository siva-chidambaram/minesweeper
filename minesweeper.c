#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Required for getch() on Windows

int flags_left;

// Count adjacent mines around a cell
int count_mine(int** minefield, int row, int column, int size) {
    int i, j, count = 0;
    for (i = row - 1; i <= row + 1; i++) {
        for (j = column - 1; j <= column + 1; j++) {
            if (minefield[i][j] == -1) {
                count++;
            }
        }
    }
    return count;
    // OPTIMIZE: Add bounds checking to avoid accessing out-of-bounds memory.
}

// Generate a minefield with mines placed randomly
int** gen_mines(int size, int level) {
    int **mine, num_mines = (size - 5) * level;
    int i, j, size1 = (size - 2) * (size - 2);

    // Allocate memory for minefield
    mine = (int**)malloc(size * sizeof(int*));
    for (i = 0; i < size; i++) {
        mine[i] = (int*)malloc(size * sizeof(int));
    }
    // OPTIMIZE: Check for malloc failures and free memory on error.

    // Initialize minefield with 0
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            mine[i][j] = 0;
        }
    }

    int ref[size1];
    for (i = 0; i < size1; i++) {
        ref[i] = 0;
    }

    // Randomly place mines avoiding duplicates
    int rand_num;
    srand(time(0));
    for (i = 0; i < num_mines;) {
        rand_num = rand() % size1;
        if (ref[rand_num] == 0) {
            mine[(rand_num / (size - 2)) + 1][(rand_num % (size - 2)) + 1] = -1;
            i++;
            ref[rand_num] = 1;
        }
    }
    // OPTIMIZE: Use Fisher-Yates shuffle for more efficient random placement.

    return mine;
}

// Generate the full minefield including numbers
int** gen_minefield(int size, int level) {
    int i, j;
    int **minefield = gen_mines(size, level);
    for (i = 1; i < size - 1; i++) {
        for (j = 1; j < size - 1; j++) {
            if (minefield[i][j] == 0) {
                minefield[i][j] = count_mine(minefield, i, j, size);
            }
        }
    }
    return minefield;
    // OPTIMIZE: Combine mine placement and number calculation in a single pass.
}

// Draw top border of the grid
void top_border(int size) {
    int i;
    printf("\t\t\t\t");
    printf("%c", 218);
    for (i = 1; i < (size - 2) * 3; i++) {
        printf("%c", 196);
        if (i % 3 == 0) printf("%c", 194);
    }
    printf("%c%c\n", 196, 191);
    // OPTIMIZE: Consider using a buffer to build the border string before printing.
}

// Draw middle border of the grid
void mid_border(int size) {
    int i;
    printf("\n\t\t\t\t%c", 195);
    for (i = 1; i < (size - 2) * 3; i++) {
        printf("%c", 196);
        if (i % 3 == 0) printf("%c", 197);
    }
    printf("%c%c", 196, 180);
    // OPTIMIZE: Same as above, buffer for border.
}

// Draw bottom border of the grid
void bottom_border(int size) {
    int i;
    printf("\t\t\t\t");
    printf("%c", 192);
    for (i = 1; i < (size - 2) * 3; i++) {
        printf("%c", 196);
        if (i % 3 == 0) printf("%c", 193);
    }
    printf("%c%c", 196, 217);
    // OPTIMIZE: Same as above, buffer for border.
}

// Display the current state of the minefield
void display_minefield(int x, int y, int size, int** minefield, int ref_matrix[size][size]) {
    int i, j;
    printf("\n");
    top_border(size);
    for (i = 1; i < size - 1; i++) {
        printf("\t\t\t\t%c", 179);
        for (j = 1; j < size - 1; j++) {
            if (i == x && j == y) {
                printf(" + ");
            } else if (ref_matrix[i][j] == -1) {
                printf(" F ");
            } else if (ref_matrix[i][j] == 0) {
                if (minefield[i][j] == 0) {
                    printf("   ");
                } else {
                    printf(" %d ", minefield[i][j]);
                }
            } else {
                printf(" %c ", 254);
            }
            printf("%c", 179);
        }
        if (i < size - 2) mid_border(size);
        printf("\n");
    }
    bottom_border(size);
    // OPTIMIZE: Reduce repeated code for cell display, use a function for cell rendering.
}

// Handle user input for movement and actions
void get_input(int size, int* x, int* y, char* choice, int** minefield, int ref_matrix[size][size]) {
    int key, key1;
    char cell_status[][20] = {"FLAGGED", "OPEN", "CLOSED"};
    while (1) {
    z1:
        system("cls");
        display_minefield(*x, *y, size, minefield , ref_matrix);
        printf("\n\n\t\t\t\t\tThe Cell you are at is %s", cell_status[ref_matrix[*x][*y]+1]);
        printf("\n\n\t\t\t\t\tYou have %d flags remaining", flags_left);
        printf("\n\n\t\t\t\t\t    Use arrow keys to move\n\n\t\t\t\tUse 'f' to flag or unflag cells and 'o' to open cells");
        key = getch();
        if (key == 'o' || key == 'f') {
            *choice = (char)key;
            break;
        } else if (key != 224) {
            printf("\a");
            goto z1;
        }
        key1 = getch();
        switch (key1) {
            case 72: if (*x > 1) (*x)--; else goto z; break;
            case 80: if (*x < size - 2) (*x)++; else goto z; break;
            case 75: if (*y > 1) (*y)--; else goto z; break;
            case 77: if (*y < size - 2) (*y)++; else goto z; break;
            default: z: printf("\a\n"); break;
        }
    }
    // OPTIMIZE: Refactor to avoid goto statements for better readability.
    // OPTIMIZE: Consider using a struct for cell state instead of magic numbers.
}

// Show the full minefield after game over
void game_over(int size, int** minefield, int ref_matrix[size][size]) {
    int i, j;
    printf("\n");
    top_border(size);
    for (i = 1; i < size - 1; i++) {
        printf("\t\t\t\t%c", 179);
        for (j = 1; j < size - 1; j++) {
            if (ref_matrix[i][j] == 0) {
                if (minefield[i][j] == 0) printf("   ");
                else printf(" %d ", minefield[i][j]);
            } else if (minefield[i][j] == -1) {
                printf(" B ");
            } else if (ref_matrix[i][j] == -1 && minefield[i][j] != -1) {
                printf(" X ");
            } else {
                printf(" %c ", 254);
            }
            printf("%c", 179);
        }
        if (i < size - 2) mid_border(size);
        printf("\n");
    }
    bottom_border(size);
    printf("\n\n\t\t\t\t\t\tGAME OVER\n\n");
    // OPTIMIZE: Merge with display_minefield using a flag to show all mines.
}

// Open a single cell
void open_cell(int* cell) {
    *cell = 0;
    // OPTIMIZE: Inline this function, as it's only a single assignment.
}

// Recursively open adjacent cells if the cell has 0 mines around
void open(int x, int y, int size, int** minefield, int ref_matrix[size][size]) {
    if (ref_matrix[x][y] != 0 && ref_matrix[x][y] != -2 && minefield[x][y] != -1) {
        if (ref_matrix[x][y] == -1) flags_left++;
        open_cell(&ref_matrix[x][y]);
        if (minefield[x][y] == 0) {
            int i, j;
            for (i = x - 1; i <= x + 1; i++) {
                for (j = y - 1; j <= y + 1; j++) {
                    open(i, j, size, minefield, ref_matrix);
                }
            }
        }
    }
    // OPTIMIZE: Add bounds checking to avoid stack overflow on edges.
    // OPTIMIZE: Use an explicit stack or queue to avoid deep recursion.
}

// Check if all non-mine cells are opened or flagged
int check_mines(int size, int ref_matrix[size][size], int mines) {
    int count = 0, i, j;
    for (i = 1; i < size - 1; i++) {
        for (j = 1; j < size - 1; j++) {
            if (ref_matrix[i][j] == 1 || ref_matrix[i][j] == -1) count++;
        }
    }
    return count == mines;
    // OPTIMIZE: Track opened cells count during gameplay to avoid full scan.
}

// Main function
int main() {
    int size, level, i, j, mines, x, y;
    char choice;

    // User selects grid size
    printf("GRID Sizes\n 1 - 8 x 8 \n 2 - 12 x 12 \n 3 - 16 x 16 \n\nEnter Grid Size : ");
    scanf("%d", &size);
    system("cls");

    // User selects difficulty level
    printf("DIFFICULTY\n 1 - Beginner \n 2 - Intermediate \n 3 - Expert \n\nEnter Difficulty : ");
    scanf("%d", &level);
    system("cls");

    size = ((size + 1) * 4) + 2;
    mines = (size - 5) * level;
    x = size - 2;
    y = size - 2;
    flags_left = mines * 2;

    int **minefield = gen_minefield(size, level);
    int ref_matrix[size][size];

    // Initialize reference matrix
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            ref_matrix[i][j] = (i == 0 || j == 0 || i == size - 1 || j == size - 1) ? -2 : 1;
        }
    }
    system("cls");

    // Main game loop
    while (1) {
        get_input(size, &x, &y, &choice, minefield, ref_matrix);
        if (choice == 'f') {
            if (ref_matrix[x][y] == 1) {
                if (flags_left == 0) { printf("\a"); continue; }
                ref_matrix[x][y] = -1;
                flags_left--;
            } else if (ref_matrix[x][y] == -1) {
                ref_matrix[x][y] = 1;
                flags_left++;
            } else {
                printf("\a");
            }
        } else if (choice == 'o') {
            if (ref_matrix[x][y] == 0 || ref_matrix[x][y] == -1) {
                printf("\a"); continue;
            } else if (minefield[x][y] == -1) {
                system("cls");
                game_over(size, minefield, ref_matrix);
                break;
            } else {
                open(x, y, size, minefield, ref_matrix);
                if (check_mines(size, ref_matrix, mines)) {
                    system("cls");
                    x = 0; y = 0;
                    display_minefield(x, y, size, minefield, ref_matrix);
                    printf("\n\n\t\t\t\t\t\tYOU WON\n\n");
                    getch();
                    break;
                }
            }
        } else {
            printf("\a");
        }
    }
    return 0;
    // OPTIMIZE: Free all dynamically allocated memory before exiting.
}