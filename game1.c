#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define GAME_FIELD_WIDTH 8
#define GAME_FIELD_HEIGHT 8
#define NUM_OBSTACLES 15
#define OBSTACLE_CHAR '#'

typedef enum {
  DIRECTION_UP,
  DIRECTION_RIGHT,
  DIRECTION_DOWN,
  DIRECTION_LEFT
} direction;


typedef struct {
  int xCoordinate, yCoordinate;
  direction dir;
} robot;

void initGamefield(short gamefield[][GAME_FIELD_WIDTH]);
void createObstacles(short gamefield[][GAME_FIELD_WIDTH], robot *bot, const int obstacles);
void printGameField(short gamefield[][GAME_FIELD_WIDTH], robot *bot);
void moveOneStep(short gamefield[][GAME_FIELD_WIDTH], robot *bot);
void stepByStep(short gamefield[][GAME_FIELD_WIDTH], robot *bot);
void nSteps(short gamefield[][GAME_FIELD_WIDTH], robot *bot);

void initGamefield(short gamefield[][GAME_FIELD_WIDTH]) {
  for (int row = 0; row < GAME_FIELD_HEIGHT; ++row) {
    for (int col = 0; col < GAME_FIELD_WIDTH; ++col) {
      gamefield[row][col] = '.';
    }
  }
}

void createObstacles(short gamefield[][GAME_FIELD_WIDTH], robot *bot, const int obstacles) {
  time_t currentTimeStamp;
  srand((unsigned)time(&currentTimeStamp));
  for (int i = 0; i < obstacles; i++) {
    int xCoordinate = rand() % GAME_FIELD_WIDTH;
    int yCoordinate = rand() % GAME_FIELD_HEIGHT;
    if (xCoordinate == bot->xCoordinate && yCoordinate == bot->yCoordinate) {
      i--;
      continue;
    } else {
      gamefield[yCoordinate][xCoordinate] = '#';
    }
  }
}

void printGameField(short gamefield[][GAME_FIELD_WIDTH], robot *bot) {
  sleep(1);
  system("clear");
  for (int yCoordinate = 0; yCoordinate < GAME_FIELD_HEIGHT; ++yCoordinate) {
    for (int xCoordinate = 0; xCoordinate < GAME_FIELD_WIDTH; ++xCoordinate) {
      if (yCoordinate == bot->yCoordinate && xCoordinate == bot->xCoordinate) {
        printf("O ");
      } else {
        printf("%c ", gamefield[yCoordinate][xCoordinate]);
      }
    }
    printf("\n");
  }
}

void moveOneStep(short gamefield[][GAME_FIELD_WIDTH], robot* bot) {
    short xCoordinate = bot->xCoordinate;
    short yCoordinate = bot->yCoordinate;

    // Update coordinates based on robot direction
    switch(bot->dir) {
        case DIRECTION_UP:
            yCoordinate--;
            break;
        case DIRECTION_RIGHT:
            xCoordinate++;
            break;
        case DIRECTION_DOWN:
            yCoordinate++;
            break;
        case DIRECTION_LEFT:
            xCoordinate--;
            break;
    }

    // Check if new position is outside the game field and move to opposite side if necessary
    if (xCoordinate >= GAME_FIELD_WIDTH) {
        xCoordinate = 0;
    }
    else if (xCoordinate < 0) {
        xCoordinate = GAME_FIELD_WIDTH -1;
    }
    else if (yCoordinate >= GAME_FIELD_HEIGHT) {
        yCoordinate = 0;
    }
    else if (yCoordinate < 0) {
        yCoordinate = GAME_FIELD_HEIGHT -1;
    }

    // Check if obstacle is present at the new position and change direction if necessary
    if (gamefield[yCoordinate][xCoordinate] == OBSTACLE_CHAR) {
        printf("obstacle\n");
        // Change direction
        bot->dir += 1;

        // Adjust direction if necessary
        if (bot->dir > 3) {
            bot->dir = 0;
        }
        else if (bot->dir < 0) {
            bot->dir = 3;
        }
    }
    else {
        // Update robot position
        bot->xCoordinate = xCoordinate;
        bot->yCoordinate = yCoordinate;
    }
}


void stepByStep(short gamefield[][GAME_FIELD_WIDTH], robot *bot)
{
    char input[5];
    short quit = 0;
    printGameField(gamefield, bot);
    while (!quit)
    {
        printf("\n");
        printf("Press any key to move the robot, or type 'quit' to exit: ");
        printf("\n");
        scanf("%s", input);
        if (strcmp("quit", input) == 0)
        {
            quit = 1;
        }
        else
        {
            moveOneStep(gamefield, bot);
            printGameField(gamefield, bot);
        }
    }
}

void nSteps(short gamefield[][GAME_FIELD_WIDTH], robot *bot)
{
    int num_steps;
    printf("Enter the number of steps the robot should take: \n");
    scanf("%d", &num_steps);
    for (int i = 0; i < num_steps; i++)
    {
        moveOneStep(gamefield, bot);
        printGameField(gamefield, bot);
    }
}

int main(void) {
    srand((unsigned)time(NULL)); // seed random number generator
    short gamefield[GAME_FIELD_HEIGHT][GAME_FIELD_WIDTH];
    int obstacles = round(GAME_FIELD_HEIGHT * GAME_FIELD_WIDTH * (NUM_OBSTACLES / 100.0f)); // calculate number of obstacles based on percentage
    int gameoption;
    robot bot = {
        .xCoordinate = rand() % GAME_FIELD_WIDTH, // randomly assign starting position for bot
        .yCoordinate = rand() % GAME_FIELD_HEIGHT,
        .dir = DIRECTION_DOWN
    };
    initGamefield(gamefield);
    createObstacles(gamefield, &bot, obstacles);
    printf("Enter the number '1' to input a specific number of steps\n");
    printf("Enter the number '2' to move the robot until 'quit' is entered\n");
    scanf("%d", &gameoption);
    switch (gameoption) {
        case 1:
            nSteps(gamefield, &bot);
            break;
        case 2:
            stepByStep(gamefield, &bot);
            break;
    }
    return 0;
}
