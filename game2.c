#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8
#define ITEMS_PERCENTAGE 15

typedef struct {
    short x;
    short y;
    int points;
} Robot;

void initGamefield(char field[][FIELD_WIDTH]);
void createItems(char field[][FIELD_WIDTH], Robot *robot, const int numItems);
void printGameField(char field[][FIELD_WIDTH], const Robot *robot);
void moveRobot(char field[][FIELD_WIDTH], Robot *robot, int *numItems);

void initGamefield(char field[][FIELD_WIDTH]) {
    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            field[y][x] = '.';
        }
    }
}

void createItems(char field[][FIELD_WIDTH], Robot *robot, const int numItems) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < numItems; i++) {
        int x, y;
        do {
            x = rand() % FIELD_WIDTH;
            y = rand() % FIELD_HEIGHT;
        } while (x == robot->x && y == robot->y);
        field[y][x] = '#';
    }
}

void printGameField(char field[][FIELD_WIDTH], const Robot *robot) {
    sleep(1);
    system("clear");

    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            if (y == robot->y && x == robot->x) {
                printf("O ");
            } else {
                printf("%c ", field[y][x]);
            }
        }
        printf("\n");
    }
}

void moveRobot(char field[][FIELD_WIDTH], Robot *robot, int *numItems) {
    short x = robot->x;
    short y = robot->y;
    int input;

    do {
        fflush(stdin);
        input = getchar();
        fflush(stdin);
    } while (input != 'w' && input != 'd' && input != 's' && input != 'a');

    switch (input) {
        case 'w':
            --y;
            break;
        case 'd':
            ++x;
            break;
        case 's':
            ++y;
            break;
        case 'a':
            --x;
            break;
    }

    if (x > FIELD_WIDTH - 1) {
        x = 0;
    } else if (x < 0) {
        x = FIELD_WIDTH - 1;
    } else if (y > FIELD_HEIGHT - 1) {
        y = 0;
    } else if (y < 0) {
        y = FIELD_HEIGHT - 1;
    }

    if (field[y][x] == '#') {
        robot->points += 5;
        printf("Item collected!\n");
        (*numItems)--;
        if (*numItems == 0) {
            printf("You won!\n");
        } else {
            printf("Remaining items: %d\n", *numItems);
        }
    }

    field[y][x] = '.';
    robot->x = x;
    robot->y = y;
}

int main(void) {
    char gameField[FIELD_HEIGHT][FIELD_WIDTH];
    Robot robot = {FIELD_WIDTH / 2, FIELD_HEIGHT / 2, 0};
    int numItems = (int) ceil((FIELD_HEIGHT * FIELD_WIDTH * ITEMS_PERCENTAGE) / 100.0);

    initGamefield(gameField);
    createItems(gameField, &robot, numItems);
    printGameField(gameField, &robot);

    while (numItems > 0) {
        moveRobot(gameField, &robot, &numItems);
        printGameField(gameField, &robot);
    }
    return 0;
}

