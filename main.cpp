#include "iGraphics.h"
#include<unistd.h>
#include<math.h>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 1000

// Menu variables
int menuOption = 0;
int inMenu = 1; // 1: menu, 0: game, 2: how to play

// Game variables
double ball_x1=10,ball_y1=10,radius=15,dx=5,head_x=450,head_x2=550,head_y=120,head_y2=120,head_radius=25;
int ball_x =500,ball_y=0,timer_start=0,ball_touched_ceil=0,ball_shoot=0,kick_off=0;
double leg_top=30 ,leg_top2=30, leg_bottom=0, leg_bottom2=0;

void ball_move() {  
    if(kick_off == 1) ball_x+=dx;
    if(ball_touched_ceil == 0 && ball_shoot == 0 && kick_off ==1) 
        ball_y= (ball_x-ball_x1-400)*(ball_x-ball_x1-400)/(-800) + ball_y1 + 200;
    else if(ball_touched_ceil ==1) ball_y-=10;

    if(ball_x + radius>SCREEN_WIDTH ){
        ball_x = SCREEN_WIDTH - radius;
        ball_x1=ball_x-800;
        ball_y1 = ball_y;
        dx=-dx;
        ball_touched_ceil=0;
        ball_shoot=0;
    }
    if(ball_x > 950 && ball_y + radius > 150 && ball_y - radius < 150){
        ball_x1=ball_x-800;
        ball_y1 = ball_y;
        dx=-dx;
        ball_touched_ceil=0;
        ball_shoot=0; 
    }
    else if(ball_x < radius ){
        ball_x = radius;
        ball_x1 = ball_x;
        ball_y1 = ball_y;
        dx=-dx;
        ball_touched_ceil=0;
        ball_shoot=0;
    }
    if(ball_x < 50 && ball_y + radius > 150 && ball_y - radius < 150){
        ball_x1 = ball_x;
        ball_y1 = ball_y;
        dx=-dx;
        ball_touched_ceil=0;
        ball_shoot=0;
    }
    if(ball_y + radius > SCREEN_HEIGHT){
        ball_y = SCREEN_HEIGHT - radius;
        if(dx<0) ball_x1 = ball_x-800;
        else ball_x1 = ball_x;
        ball_y1 = ball_y;
        ball_touched_ceil=1;
        ball_shoot = 0;
    }
    if(ball_y < radius){
        if(dx>0){
            ball_y = radius;
            ball_x1 = ball_x;
            ball_y1 = ball_y;
        }
        else{
            ball_y = radius;
            ball_x1 = ball_x -800;
            ball_y1 = ball_y;
        }
        ball_touched_ceil=0;
        ball_shoot =0;
    }
    if((ball_x < 40 && ball_y + radius < 150) || (ball_x > 960 && ball_y + radius < 150))
    { 
        sleep(1);
        ball_touched_ceil =0;
        ball_shoot =0;
        ball_x = 500, ball_y =0;
        kick_off =0;
    }
}

void iDraw() {
    iClear();

    if (inMenu == 1) {
        // Menu screen
        iSetColor(255, 255, 255);
        iText(400, 500, "2 Player Soccer Game", GLUT_BITMAP_TIMES_ROMAN_24);

        if (menuOption == 0) iSetColor(255, 0, 0);
        else iSetColor(255, 255, 255);
        iText(420, 400, "1. Start Game", GLUT_BITMAP_HELVETICA_18);

        if (menuOption == 1) iSetColor(255, 0, 0);
        else iSetColor(255, 255, 255);
        iText(420, 350, "2. How to Play", GLUT_BITMAP_HELVETICA_18);

        if (menuOption == 2) iSetColor(255, 0, 0);
        else iSetColor(255, 255, 255);
        iText(420, 300, "3. Exit", GLUT_BITMAP_HELVETICA_18);
    }
    else if (inMenu == 0) {
        // Game Screen
        iSetColor(135,206,235);
        iFilledRectangle(0,150,1000,450);
        iSetColor(154,236,153);
        iFilledRectangle(50,0,900,150);
        iSetTransparentColor(255,255,255,0.5);
        iFilledRectangle(0,0,45,140);
        iFilledRectangle(955,0,45,140);
        iSetColor(0,0,0);
        iFilledRectangle(0,140,50,10);
        iFilledRectangle(45,0,5,40);
        iFilledRectangle(950,140,50,10);
        iFilledRectangle(950,0,5,40);
        iSetColor(255,0,0);
        iFilledCircle(ball_x,ball_y,radius);
        iSetColor(0,0,0);
        iFilledCircle(head_x,head_y,head_radius);
        iFilledRectangle(head_x - head_radius,leg_top,2*head_radius,head_y - leg_top - head_radius);
        iLine(head_x,leg_top,head_x - 20 ,leg_bottom);
        iLine(head_x,leg_top,head_x + 20 ,leg_bottom);
        iSetColor(0,0,255);
        iFilledCircle(head_x2,head_y2,head_radius);
        iFilledRectangle(head_x2 - head_radius,leg_top2,2*head_radius,head_y2 - leg_top2 - head_radius);
        iLine(head_x2,leg_top2,head_x2 - 20 ,leg_bottom2);
        iLine(head_x2,leg_top2,head_x2 + 20 ,leg_bottom2);
    }
    else if (inMenu == 2) {
        // How to play screen
        iSetColor(255, 255, 0);
        iText(400, 500, "How to Play", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(200, 450, "Player 1 : WASD to move, H = header, S = shoot");
        iText(200, 400, "Player 2 : Arrow Keys to move, L = header, K = shoot");
        iText(200, 350, "Press Enter to start the game");
        iText(200, 250, "Press 'b' to go back to menu.");
    }
}

void iKeyboard(unsigned char key) {
    if (inMenu == 1) {
        if (key == '\r') {
            if (menuOption == 0) { inMenu = 0; }
            else if (menuOption == 1) { inMenu = 2; }
            else if (menuOption == 2) { exit(0); }
        }
    }
    else if (inMenu == 2) {
        if (key == 'b') { inMenu = 1; }
    }
    else if (inMenu == 0) {  // game controls

        switch (key) {
            case 'q': iPauseTimer(0); break;
            case 'r': iResumeTimer(0); break;
            case 's':
                if((((ball_x > head_x)? (ball_x - head_x) : (head_x - ball_x) )<=40) && ball_y <= head_y + head_radius && ball_y >=leg_bottom) {
                    if(timer_start==0 ){
                        iSetTimer(10,ball_move);
                        timer_start =1;
                    }
                    if(kick_off ==10) kick_off =1;
                    ball_shoot =1, ball_touched_ceil=0;
                    dx=(dx>0)?dx:-dx;
                }
                break;
            case '\r':
                if(kick_off ==0) { ball_x =500, ball_y =0; kick_off =10; }
                break;
            case 'w':
                if(head_y <= SCREEN_HEIGHT - 30) {
                    head_y+=30; leg_top+=30; leg_bottom+=30;
                }
                else {
                    head_y = SCREEN_HEIGHT - head_radius;
                    leg_top = head_y - 90; leg_bottom = leg_top - 30;
                }
                break;
            case 'z':
                if(head_y >=150) { head_y-=30; leg_top-=30; leg_bottom-=30; }
                else { head_y = 120; leg_top = 30; leg_bottom =0; }
                break;
            case 'a':
                if(head_x>=30) head_x-=30; else head_x = 25;
                break;
            case 'd':
                if(head_x <= SCREEN_WIDTH - 30) head_x+=30;
                else head_x = SCREEN_WIDTH - head_radius;
                break;
            case 'h':
                if((((ball_x > head_x)? (ball_x - head_x) : (head_x - ball_x) )<=40) && ball_y <= head_y + head_radius && ball_y >=leg_bottom) {
                    if(kick_off ==10) kick_off =1;
                    if(timer_start==0 ){ iSetTimer(10,ball_move); timer_start =1;}
                    if(dx<0) dx =-dx;
                    ball_x1 = ball_x;
                    ball_y1 = ball_y;
                    ball_touched_ceil=0;
                    ball_shoot =0;
                }
                break;
            case 'l':
                if((((ball_x > head_x2)? (ball_x - head_x2) : (head_x2 - ball_x) )<=40) && ball_y <= head_y2 + head_radius && ball_y >=leg_bottom2) {
                    if(kick_off ==10) kick_off =1;
                    if(timer_start==0 ){ iSetTimer(10,ball_move); timer_start =1;}
                    if(dx>0) dx =-dx;
                    ball_x1 = ball_x-800;
                    ball_y1 = ball_y;
                    ball_touched_ceil=0;
                    ball_shoot =0;
                }
                break;
            case 'k':
                if((((ball_x > head_x2)? (ball_x - head_x2) : (head_x2 - ball_x) )<=40) && ball_y <= head_y2 + head_radius && ball_y >=leg_bottom2) {
                    if(timer_start==0 ){ iSetTimer(10,ball_move); timer_start =1;}
                    if(kick_off ==10) kick_off =1;
                    ball_shoot =1,ball_touched_ceil =0;
                    dx=(dx<0)?dx:-dx;
                }
                break;
        }
    }
}

void iSpecialKeyboard(unsigned char key) {
    if (inMenu == 1) {
        if (key == GLUT_KEY_DOWN) menuOption = (menuOption + 1) % 3;
        if (key == GLUT_KEY_UP) menuOption = (menuOption - 1 + 3) % 3;
    }
    else if (inMenu == 0) {
        switch (key) {
            case GLUT_KEY_UP:
                if(head_y2 <= SCREEN_HEIGHT - 30) { head_y2+=30; leg_top2+=30; leg_bottom2+=30; }
                else { head_y2 = SCREEN_HEIGHT - head_radius; leg_top2 = head_y2 - 90; leg_bottom2 = leg_top2 - 30; }
                break;
            case GLUT_KEY_DOWN:
                if(head_y2 >=150) { head_y2-=30; leg_top2-=30; leg_bottom2-=30; }
                else { head_y2 = 120; leg_top2 = 30; leg_bottom2 =0; }
                break;
            case GLUT_KEY_LEFT:
                if(head_x2>=30) head_x2-=30; else head_x2 = 25;
                break;
            case GLUT_KEY_RIGHT:
                if(head_x2 <= SCREEN_WIDTH - 30) head_x2+=30;
                else head_x2 = SCREEN_WIDTH - head_radius;
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "2 Player Soccer with Menu");
    return 0;
}
