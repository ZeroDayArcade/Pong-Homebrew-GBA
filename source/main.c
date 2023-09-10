#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include "graphics.h"

#define MAIN_MENU        0
#define SETTINGS_MENU    1

#define MENU_MODE        0
#define MATCH_MODE       1
#define RESET_MODE       2

#define PADDLE_HEIGHT    24
#define PADDLE_WIDTH     8
#define BALL_SIZE        8

#define NEW_GAME_PAUSE   120               // 2   Seconds
#define ROUND_PAUSE      90                // 1.5 Seconds
#define HALF_PAUSE       (ROUND_PAUSE/2)

#define BALL_START_X     (SCREEN_WIDTH/2)-(BALL_SIZE/2)+1
#define PLAYER_START_Y   ((SCREEN_HEIGHT/2)-(PADDLE_HEIGHT/2))
#define WINNING_SCORE    10

/* Show menu cursor on current selection */
void setMenuCursor(int selection) {

    /* Clear Cursor */
    clearRegion(MENU_TEXT_X-CHAR_PIX_SIZE, MENU_ITEM_1,
                MENU_TEXT_X, MENU_ITEM_2+CHAR_PIX_SIZE);
                
    /* Show Cursor on selection */
    printChar(selector[1], MENU_TEXT_X-CHAR_PIX_SIZE, MENU_ITEM_1+
                                          (selection)*LINE_HEIGHT);
}

/* Menu Logic */
void menuMode(bool *menuVisible, struct MenuScreen *mainMenu, 
    struct MenuScreen *settingsMenu, int *currentMenu, int *gameMode) {

    /* Render current menu if not already rendered */
    if (!*menuVisible) {
        
        if (*currentMenu == MAIN_MENU) {
            displayText("PONG BREW ", MENU_TEXT_X,   MENU_TEXT_Y);
            displayText("PLAY GAME ", MENU_TEXT_X,   MENU_ITEM_1);
            displayText(" SETTINGS ", MENU_TEXT_X-4, MENU_ITEM_2);
            setMenuCursor(mainMenu->selection);
            
        } else if (*currentMenu == SETTINGS_MENU) {
            displayText("1ST TO 10 ", MENU_TEXT_X,   MENU_TEXT_Y);
            displayText("WINS GAME!", MENU_TEXT_X,   MENU_TEXT_Y+LINE_HEIGHT);
            displayText("   BACK   ", MENU_TEXT_X,   MENU_ITEM_2);
            setMenuCursor(settingsMenu->selection);
        }
        *menuVisible = true;
    } 

    /* Respond to Input / Menu Selections */
    int keys_pressed;
    keys_pressed = keysDown();
    bool selectionMade    = (keys_pressed & KEY_START) || (keys_pressed & KEY_A );
    bool changedSelection = (keys_pressed & KEY_DOWN)  || (keys_pressed & KEY_UP);

    if (*currentMenu == MAIN_MENU) {
        if (selectionMade) {
            if (mainMenu->selection == 0) {
                clearMenu();
                *gameMode = MATCH_MODE;
            } else if (mainMenu->selection == 1) {
                clearMenu();
                *currentMenu = SETTINGS_MENU;
                *menuVisible = false;
            }
        } else if (changedSelection) {
            mainMenu->selection = !(mainMenu->selection);
            setMenuCursor(mainMenu->selection);
        }
    } else if (*currentMenu == SETTINGS_MENU) {
        if (selectionMade) {
            clearMenu();
            *currentMenu = MAIN_MENU;
            *menuVisible = false;
        }
    }
    return;
}

/* Set Starting Values for New Game */
void setupMatch(struct rect *humanPlayer, struct rect *computerPlayer, 
    struct rect *ball, int *humanScore, int *computerScore, int *pauseLength, 
    int *pauseCounter, bool *paused) {
    
    humanPlayer->x = 1;
    humanPlayer->y = PLAYER_START_Y;
    humanPlayer->prevX = humanPlayer->x;
    humanPlayer->prevY = humanPlayer->y;
    humanPlayer->width = PADDLE_WIDTH;
    humanPlayer->height = PADDLE_HEIGHT;
    humanPlayer->velocityX = 0;
    humanPlayer->velocityY = 0;
    *humanScore = 0;

    computerPlayer->x = SCREEN_WIDTH - PADDLE_WIDTH - 1;
    computerPlayer->y = PLAYER_START_Y;
    computerPlayer->prevX = computerPlayer->x;
    computerPlayer->prevY = computerPlayer->y;
    computerPlayer->width = PADDLE_WIDTH;
    computerPlayer->height = PADDLE_HEIGHT;
    computerPlayer->velocityX = 0;
    computerPlayer->velocityY = 0;
    *computerScore = 0;

    ball->x = BALL_START_X;
    ball->y = (SCREEN_HEIGHT/2)-(BALL_SIZE/2);
    ball->prevX = ball->x;
    ball->prevY = ball->y;
    ball->width = BALL_SIZE;
    ball->height = BALL_SIZE;
    ball->velocityX = 2;
    ball->velocityY = 2;

    *pauseLength = NEW_GAME_PAUSE;
    *pauseCounter = 0;
    *paused = true;
}

/* Bounding Box Collision Detection */
bool collision(
    int x1, int y1, int width1, int height1,
    int x2, int y2, int width2, int height2) {
    if (x1 + width1 > x2 &&
        x1 < x2 + width2 &&
        y1 + height1 > y2 &&
        y1 < y2 + height2) return true;
    return false;
}

/* Paddle Bounce Logic - Tweak as needed depending on paddle size */
void bounceOffPaddle(struct rect *playerPaddle, struct rect *ball) {
    int y_diff = (ball->y + (BALL_SIZE/2)) - (playerPaddle->y + (PADDLE_HEIGHT/2));

    /* Set Y Velocity according to distance from center of paddle */
    ball->velocityY = 	((y_diff > 0) - (y_diff <  0)) + 
                        ((y_diff > 3) - (y_diff < -3)) + 
                        ((y_diff > 6) - (y_diff < -6));

    /* Set X Velocity to +/- 3, and add 1 to X speed if hits near center */
    ball->velocityX = ((ball->velocityX < 0) - (ball->velocityX > 0)) * 
                            (3 + (1 - ((y_diff > 4) || (y_diff < -4))));
}

/* Scoring Points */
void playerScores(bool isHuman, struct rect *ball, int *humanScore, 
    int *computerScore, int*pauseLength, bool* paused, int *gameMode) {

    /* Increment Score */
    int *playerScore;
    if (isHuman) 	playerScore = humanScore;
    else 			playerScore = computerScore;
    *playerScore = *playerScore + 1;
    *paused = true;

    /* If Winning Score, Show Winner and Reset */
    if (*playerScore >= WINNING_SCORE) {
        clearRegion(SCREEN_WIDTH/2, MENU_TEXT_Y, 
            SCREEN_WIDTH/2+2, MENU_TEXT_Y+30);
        if (isHuman) {
            displayText(" YOU WIN! ", 	
                END_TEXT_X, END_TEXT_Y);
        } else {
            displayText(" CPU WINS ", 	
                END_TEXT_X, END_TEXT_Y);
        }
        *gameMode = RESET_MODE;
        
    /* Else Keep Playing */
    } else {
        ball->velocityX *= -1;
        *pauseLength = ROUND_PAUSE;
    }
}

/* Game Logic */
void matchMode(struct rect *humanPlayer, struct rect *computerPlayer, 
    struct rect *ball, int *humanScore, int *computerScore, 
    int *pauseLength, int *pauseCounter, bool *paused, int *gameMode) {

    /* If players are rallying */
    if (!*paused) {

        /* If ball has hit opponents wall, player scores */
        if (ball->x <= 3 && ball->velocityX < 0) {
            ball->x = humanPlayer->x;
            playerScores(false, ball, humanScore, computerScore, 
                                pauseLength, paused, gameMode);
        } else if (ball->x >= SCREEN_WIDTH - ball->width - 3 && ball->velocityX > 0) {
            ball->x = computerPlayer->x + PADDLE_WIDTH - BALL_SIZE;
            playerScores(true, ball, humanScore, computerScore, 
                               pauseLength, paused, gameMode);
        }
        /* If ball hits ceiling or floor, bounce off */
        if (ball->y <= 0 && ball->velocityY < 0) { 										
            ball->velocityY *= -1;
        } else if (ball->y >= SCREEN_HEIGHT - ball->height && ball->velocityY > 0) {
            ball->velocityY *= -1;
        }

        /* Move human player based on input */
        int keys_pressed, keys_released;
        keys_pressed = keysDown();
        keys_released = keysUp();
        if ((keys_released & KEY_UP) || (keys_released & KEY_DOWN)) {
            humanPlayer->velocityY = 0;
        }
        if ( (keys_pressed & KEY_UP) && (humanPlayer->y >= 0) ) {
            humanPlayer->velocityY = -2;
        } 
        if ( (keys_pressed & KEY_DOWN) && 
            (humanPlayer->y <= SCREEN_HEIGHT - humanPlayer->height) ) {
            humanPlayer->velocityY = 2;
        } 
        if ((humanPlayer->y <= 0 && humanPlayer->velocityY < 0) ||
             ((humanPlayer->y >= SCREEN_HEIGHT - humanPlayer->height) && 
                                            humanPlayer->velocityY > 0)) {
            humanPlayer->velocityY = 0;
        }

        /* Computer Player Movement Logic */
        if (ball->y + (BALL_SIZE-2) > computerPlayer->y + (PADDLE_HEIGHT/2) && 
            computerPlayer->y + PADDLE_HEIGHT <= SCREEN_HEIGHT &&
            ball->x > SCREEN_WIDTH/4 &&
            !(ball->velocityY < -2) &&
            (ball->velocityX > 0 || ball->x > SCREEN_WIDTH/2)) {
            computerPlayer->velocityY = 2;
        } else if (ball->y + (BALL_SIZE-2) < computerPlayer->y + (PADDLE_HEIGHT/2) && 
            computerPlayer->y >= 0 &&
            ball->x > SCREEN_WIDTH/4 &&
            !(ball->velocityY > 2) &&
            (ball->velocityX > 0 || ball->x > SCREEN_WIDTH/2)) {
            computerPlayer->velocityY = -2;
        } else {
            computerPlayer->velocityY = 0;
        }

        /* Update Positions */
        if (!*paused) {
            ball->x += ball->velocityX;
            ball->y += ball->velocityY;
            humanPlayer->y += humanPlayer->velocityY; 
            computerPlayer->y += computerPlayer->velocityY; 
        }

    /* Wait a moment after score before new rally */
    } else {
        *pauseCounter = *pauseCounter + 1;
        if (*pauseCounter == (int)HALF_PAUSE) {
            ball->x = BALL_START_X;
            humanPlayer->y = PLAYER_START_Y;
            computerPlayer->y = PLAYER_START_Y;
        }
        if (*pauseCounter > *pauseLength) {
            *pauseCounter = 0;
            *paused = false;
        }
    }

    /* Clear Previous Ball, Player Graphics */
    clearPrevious(ball);
    clearPrevious(humanPlayer);
    clearPrevious(computerPlayer);

    /* Draw Static Elements */
    if (*gameMode != RESET_MODE) drawCenterLine();
    printHumanScore(score[*humanScore]);
    printComputerScore(score[*computerScore]);
    printPlayerSymbols();

    /* Draw Ball, Players at current positions */
    drawRect(ball, CLR_LIME);
    drawRect(humanPlayer, CLR_BLUE);
    drawRect(computerPlayer, CLR_BLUE);

    /* Update previous positions for clearing pixels */
    ball->prevX = ball->x;
    ball->prevY = ball->y;
    humanPlayer->prevX = humanPlayer->x;
    humanPlayer->prevY = humanPlayer->y;
    computerPlayer->prevX = computerPlayer->x;
    computerPlayer->prevY = computerPlayer->y;

    /* Check for paddle / ball collisions, if so ball bounces */
    if (collision(
        humanPlayer->x, humanPlayer->y, 
        humanPlayer->width, humanPlayer->height,
        ball->x, ball->y, 
        ball->width, ball->height)
        && ball->velocityX < 0) {
        bounceOffPaddle(humanPlayer, ball);
    }
    if (collision(
        computerPlayer->x, computerPlayer->y, 
        computerPlayer->width, computerPlayer->height,
        ball->x, ball->y, 
        ball->width, ball->height) 
        && ball->velocityX > 0) {
        bounceOffPaddle(computerPlayer, ball);
    }

    /* If Game has Ended, Clear Match Data */
    if (*gameMode == RESET_MODE) {
        setupMatch(humanPlayer, computerPlayer, ball, humanScore, 
            computerScore, pauseLength, pauseCounter, paused);
    }
    return;
}

int main(void) {

    // Interrupt handlers
    irqInit();

    // Enable Vblank Interrupt, Allow VblankIntrWait
    irqEnable(IRQ_VBLANK);

    /* Match Variables */
    struct rect humanPlayer, computerPlayer, ball;
    int humanScore, computerScore; 
    int pauseLength, pauseCounter;
    bool paused;
    setupMatch(&humanPlayer, &computerPlayer, &ball, &humanScore, 
        &computerScore, &pauseLength, &pauseCounter, &paused);

    /* Menu Variables */
    struct MenuScreen mainMenu, settingsMenu;
    mainMenu.selection = 0;
    settingsMenu.selection = 1;
    bool menuVisible = false;
    int currentMenu = MAIN_MENU;

    /* Start in Menu */
    int gameMode = MENU_MODE;

    /* Set screen to mode 3 */
    SetMode( MODE_3 | BG2_ON );

    /* Main Game Loop */
    while (1) {
        VBlankIntrWait();
        scanKeys();

        /* Menu Mode */
        if (gameMode == MENU_MODE) {
            menuMode(	&menuVisible, 
                        &mainMenu, 
                        &settingsMenu, 
                        &currentMenu, 
                        &gameMode);

        /* Playing a Game */
        } else if (gameMode == MATCH_MODE) {
            matchMode(	&humanPlayer, 
                        &computerPlayer, 
                        &ball, 
                        &humanScore, 
                        &computerScore, 
                        &pauseLength, 
                        &pauseCounter, 
                        &paused, 
                        &gameMode);

        /* Reset after completed game */
        } else if (gameMode == RESET_MODE) {
            if (pauseCounter > pauseLength) {
                pauseCounter = 0;
                clearScreen();
                menuVisible = false;
                gameMode = MENU_MODE;
                currentMenu = MAIN_MENU;
            } else {
                pauseCounter++;
            }
        }
    }
}