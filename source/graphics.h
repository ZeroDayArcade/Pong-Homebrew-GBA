#include "characters.h"

#define MEM_VRAM        0x06000000
#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   160

#define CLR_BLACK       0x0000
#define CLR_RED         0x001F
#define CLR_LIME        0x03E0
#define CLR_YELLOW      0x03FF
#define CLR_BLUE        0x7C00
#define CLR_MAG         0x7C1F
#define CLR_CYAN        0x7FE0
#define CLR_WHITE       0x7FFF

#define CHAR_PIX_SIZE   8
#define LINE_HEIGHT 	12
#define NUM_CHARS_LINE  10

#define MENU_TEXT_X     ((SCREEN_WIDTH/2)-(CHAR_PIX_SIZE*NUM_CHARS_LINE/2))
#define MENU_TEXT_Y     (SCREEN_HEIGHT/2)-16
#define MENU_ITEM_1     MENU_TEXT_Y+24
#define MENU_ITEM_2     MENU_ITEM_1+LINE_HEIGHT

#define SCORE_Y         10
#define PLAYER_SYM_Y 	(SCREEN_HEIGHT-LINE_HEIGHT-SCORE_Y)

typedef u16             M3LINE[SCREEN_WIDTH];
#define m3_mem          ((M3LINE*)MEM_VRAM)

struct rect {
    int x;
    int y;
    int prevX;
    int prevY;
    int width;
    int height;
    int velocityX;
    int velocityY;
}; 

struct MenuScreen {
    int selection;
};

/* Drawing Graphics for Players and Ball */
void drawRect(struct rect *cRect, int color) {
    for (int i = cRect->x; i < cRect->x + cRect->width; i++) {
        for (int j = cRect->y; j < cRect->y + cRect->height; j++) {
            m3_mem[j][i]= color;
        }
    }
}

void clearPrevious(struct rect *cRect) {
    for (int i = cRect->prevX; i < cRect->prevX + cRect->width; i++) {
        for (int j = cRect->prevY; j < cRect->prevY + cRect->height; j++) {
            m3_mem[j][i]= CLR_BLACK;
        }
    }
}

/* Clear Generic Rectangular Region */
void clearRegion(int x1, int y1, int x2, int y2) {
    for (int i=x1; i<x2; i++) {
        for (int j=y1; j<y2; j++) {
            m3_mem[j][i] = CLR_BLACK;
        }
    }
}

/* Draw Net / Center Line */
void drawCenterLine() {
    for (int j=0; j<SCREEN_HEIGHT; j+=8) {
        m3_mem[j+2][SCREEN_WIDTH/2] = CLR_WHITE;
        m3_mem[j+2][SCREEN_WIDTH/2+1] = CLR_WHITE;
        m3_mem[j+3][SCREEN_WIDTH/2] = CLR_WHITE;
        m3_mem[j+3][SCREEN_WIDTH/2+1] = CLR_WHITE;
        m3_mem[j+4][SCREEN_WIDTH/2] = CLR_WHITE;
        m3_mem[j+4][SCREEN_WIDTH/2+1] = CLR_WHITE;
        m3_mem[j+5][SCREEN_WIDTH/2] = CLR_WHITE;
        m3_mem[j+5][SCREEN_WIDTH/2+1] = CLR_WHITE;
    }
}

/* Display Player Scores (Bigger Text) */
void printScore(bool scoreArray[64], int x) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            int color = CLR_BLACK;
            if (scoreArray[i*8+j]) color = CLR_WHITE;
            m3_mem[SCORE_Y + 2*i][x + 2*j] = color;
            m3_mem[SCORE_Y + 2*i][x + 2*j+1] = color;
            m3_mem[SCORE_Y + 2*i+1][x + 2*j] = color;
            m3_mem[SCORE_Y + 2*i+1][x + 2*j+1] = color;
        }
    }
}

void printHumanScore(bool scoreArray[64]) {
    printScore(scoreArray, SCREEN_WIDTH/4 - 8);
}

void printComputerScore(bool scoreArray[64]) {
    printScore(scoreArray, 3*SCREEN_WIDTH/4 - 8);
}

/* Print Individual Character (Normal Text) */
void printChar(bool characterArray[64], int x, int y) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            int color = CLR_BLACK;
            if (characterArray[i*8+j]) color = CLR_WHITE;
            m3_mem[y + i][x + j] = color;
        }
    }
}

/*  Display text string (made of characters.h chars). Only capital
    letters, numbers, and some punctuation, not full ascii.
    Limited to NUM_CHARS_LINE characters per line.
*/
void displayText(char textBuffer[], int x, int y) {
    for (int i=0; i<NUM_CHARS_LINE; i++) {
        // Space
        if (textBuffer[i] == 0x20) { 										
            printChar(selector[0], x+i*8, y);
        // Exclamation point
        } else if (textBuffer[i] == 0x21) { 								
            printChar(punctuation[1], x+i*8, y);
        // Period
        } else if (textBuffer[i] == 0x2E) { 								
            printChar(punctuation[0], x+i*8, y);
        // Numbers
        } else if (textBuffer[i] >= 0x30 && textBuffer[i] <= 0x39) { 		
            printChar(score[textBuffer[i] - 0x30], x+i*8, y);
        // Letters
        } else {
            printChar(alphabet[textBuffer[i] - 0x41], x+i*8, y); 			
        }
    }
}

/* Show which side is which player */
void printPlayerSymbols() {

    /* Print "P1" on Left Side */
    printChar(alphabet[15], (SCREEN_WIDTH/4)-CHAR_PIX_SIZE, PLAYER_SYM_Y);      // P
    printChar(score[1],     (SCREEN_WIDTH/4),               PLAYER_SYM_Y);      // 1

    /* Print "CPU" on Left Side */
    printChar(alphabet[2],  (3*SCREEN_WIDTH/4)-CHAR_PIX_SIZE-4, PLAYER_SYM_Y);  // C
    printChar(alphabet[15], (3*SCREEN_WIDTH/4)-4,               PLAYER_SYM_Y);  // P
    printChar(alphabet[20], (3*SCREEN_WIDTH/4)+CHAR_PIX_SIZE-4, PLAYER_SYM_Y);  // U
}

/* Clear just the Menu, faster than clear screen (smaller area) */
void clearMenu() {
    clearRegion(
        MENU_TEXT_X-CHAR_PIX_SIZE, 
        MENU_TEXT_Y, 
        MENU_TEXT_X+(NUM_CHARS_LINE+2)*CHAR_PIX_SIZE, 
        MENU_TEXT_Y+4*LINE_HEIGHT);
}

/* Clear entire screen (slow) */
void clearScreen() {
    for (int i=0; i<240; i++) {
        for (int j=0; j<160; j++) {
            m3_mem[j][i] = CLR_BLACK;
        }
    }
}