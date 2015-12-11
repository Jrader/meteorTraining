/**********************************************
 * main.c
 *
 * Created by: Joey Rader (jcrader) Di Zhong  (dizhong)
 * Created on: 12/4/15
 * Last updated on: 12/4/15
 * Part of: Final Project
 **********************************************/


#include <stm32f30x.h>
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <queue.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

/* extern int16_t crossX; */
/* extern int16_t crossY; */
/* extern uint8_t duckX; */
/* extern uint8_t duckY; */
/* extern int score; */
/* extern int TARGET_FLAG; */

 extern void move_target(); 
 // extern void game_timer(); 

//#include "final.h"
#include "draw.h"
#include "image.h"
#include "sound.h"
#include "nunchuk.h"

DIR dir;	/* Directory object */
FILINFO fno;
int16_t crossX; // crosshair's x coordinate
int16_t crossY; // crosshair's y coordinate
uint8_t duckX; // duck's x coordinate
uint8_t duckY; // duck's y coordinate
int score = 0; // keeps track of player's score
char score_buff[10];
int counter = 0; // keeps track of moving duck
int move_time = 100; // determines how long until the bird moves automatically
int TARGET_FLAG = 0; // flag to be set if the target should be moved
int END_GAME_FLAG = 0; // flag to be set whenever the game is over
int gtime = 4000;
int data[5];
FRESULT fr;
int first_time = 0;

//queue_t txbuf;



// generates a random number to help place duck on screen in random locations
int random() {
  return rand() % 100;
}

// move_target should erase the current target and draw a new one at a random location
void move_target() {
  erase_target(duckX, duckY);

  duckX = random();
  duckY = random();


  fillRect(duckX, duckY, 20, 20, YELLOW);
  //displayImage("bmpimg1.bmp", duckX, duckY);   //need to find bmp image for duck.
}

// end_game shows the end game screen and sets the GAME_OVER flag
void end_game() {

  int i, temp1, temp2, line = 40;

  /* fr = fopen(&fid, "scores.txt", FA_READ); */
  /* if (fr){ */
  /*   f_read(fr, "%d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4]); */
  /* } */
    
  END_GAME_FLAG = 1;
  TARGET_FLAG = 0;
  //erase_target(duckX, duckY);
  //erase_crosshair(crossX, crossY);
  f3d_lcd_fillScreen(BLACK);
  f3d_lcd_drawString(38, 20, "GAME OVER", WHITE, BLACK);

  /* while (i < 5){  */
  /* sprintf(score_buff, "%d. %d", i, data[i]);  */
  /*   f3d_lcd_drawString(10, line, score_buff, WHITE, BLACK); */
  /*   line += 10; */

  /*   if (score > data[i]){ */
  /*     temp1 = data[i]; */
  /*     data[i] = score; */
  /*     sprintf(score_buff, "NEW HIGH SCORE: %d", score); */
  /*     f3d_lcd_drawString(10, 30, score_buff, WHITE, BLACK); */
  /*     score = -1; */
  /*   } */
  /*   if (i != 4) */
  /*     data[i+1] = temp1; */
  /*   data[i+1] = temp1; */
  /*   temp1 = temp2; */
  /*   i++; */
  /* } */
  char datas[23];

  if (first_time || score < data[0]){
    sprintf(datas, "HIGH SCORE: %d", data[0]);
    f3d_lcd_drawString(25, 40, datas, WHITE, BLACK);
    if(first_time){
      data[0] = score;
      first_time = 0;
    }
  }
  else {
    sprintf(datas, "NEW HIGH SCORE: %d", data[0]);
    f3d_lcd_drawString(10, 40, datas, WHITE, BLACK);
    data[0] = score;
  }
  sprintf(score_buff, "Score: %d", score);
  f3d_lcd_drawString(40, 80, score_buff, WHITE, BLACK);

  sprintf(score_buff, "Try again? Press Z", score);
  f3d_lcd_drawString(10, 130, score_buff, WHITE, BLACK);
  
}

// Keeps track of game time. Once timer hits zero, the game will be ended. May increase time, but for testing
// keep at 60.
void game_timer() {
 
  if(gtime>0 ){
       gtime--;
    }
  else{
  end_game();
  }
}

//  Using SysTick_Handler function with counter to determine when to move the target.
void SysTick_Handler2() {
	/* if (!queue_empty(&txbuf)) { */
	/* 	flush_uart(); */
	/* } */
	if (counter >= move_time) {
		TARGET_FLAG = 1;
		counter = 0;
	}
	counter++;
}



int main() {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// initialization of everything we need
	f3d_uart_init();
	delay(100);
	f3d_timer2_init();
        delay(100);
	f3d_dac_init();
	delay(100);
	f3d_delay_init();
	delay(100);
	f3d_rtc_init();
	delay(100);
	f3d_led_init();
	delay(100);
	f3d_systick_init();
	delay(100);
	f3d_lcd_init();
	delay(100);
	f3d_i2c1_init();
	delay(100);
	f3d_nunchuk_init();
	delay(100);
	

       

	// mount file system
          f_mount(0, &Fatfs);
	// add some .bmp start screen that asks player to hit the z or c button to start.
	// Will determine which button is eaier to use. For now, we'll use z.
	f3d_lcd_fillScreen(YELLOW);
	f3d_lcd_drawString(17, 40, "****************", CYAN, YELLOW);
	fillRect(18, 48, 30, 93, CYAN);
	f3d_lcd_drawString(37, 60, "DUCK HUNT" , BLACK, CYAN);
	f3d_lcd_drawString(17, 79, "****************" , CYAN, YELLOW);
	f3d_lcd_drawString(16, 110, "press z to start!" , BLACK, YELLOW);
        


	while(1){
	
	// unless the user presses the z button, don't allow game to start
	while(!n.z) {
	  f3d_nunchuk_read(&n);
	  delay(20);
	}

	END_GAME_FLAG = 0;
	TARGET_FLAG = 1;
	gtime = 4000;
	score = 0;
	move_time = 100;
        
	// background color
 
	f3d_lcd_fillScreen(CYAN);
	f3d_lcd_drawString(2, 146, "*********************", GREEN, CYAN);
	fillRect(0, 150, 10, 160, GREEN);
	sprintf(score_buff, "High: %d", data[0]);
	f3d_lcd_drawString(85, 150, score_buff, RED, GREEN);

	// set initial crosshair position
	crossX = 5; //should be near middle of screen. Can adjust after testing
	crossY = 5;

	// sets random location of duck using random function
	duckX = random();
	duckY = random();

	// draws the crosshair
	draw_crosshair(crossX, crossY);

	// draws grass for bottom of the screen. Still need to find some grass bmp that will work. if not
	// we can just draw a green line.
	//	displayImage("somebmp.bmp", 0, 137);

	// draws the scoring display. Might want to add a timer but for now just display the duck count.
	f3d_lcd_drawString(5, 150, "Score: 0", BLACK, GREEN);

	

	// draws duck. Still need to find bmp image that will work.
	//displayImage("duck.bmp", duckX, duckY);
       	fillRect(duckX, duckY, 20, 20, YELLOW);

		n.z = 0;

	// continually checks the nunchuk until the game is not over.
	while (1) {
	  
	   game_timer();
	   if ( gtime == 3000){
	     move_time = 50; 
	   }
	   else if (gtime == 1000){
	     move_time = 20;
	   }
	     

	  if (!END_GAME_FLAG) {
	    SysTick_Handler2();

	    if (TARGET_FLAG) {
	      move_target();
	      TARGET_FLAG = 0;
	    }
	    check_nunchuk(gtime);
	  }else{
	    break;
	  }
	 
	}
	end_game(); 
	}
    
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif
