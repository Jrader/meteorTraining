/**********************************************
 * nunchuk.h
 *
 * Created by: Joey Rader (jcrader) & Di Zhong (dizhong)
 * Created on: 12/4/2015
 * Last updated on: 12/4/2015
 * Part of: Final Project
 **********************************************/

#include "final.h"
#include "nunchuk.h"
#include "draw.h"
#include "image.h"
#include "sound.h"

#define MAX_X 127
#define MAX_Y 135
#define MIN_X 0
#define MIN_Y 0

char score_buff[50];

void check_nunchuk(int gtime) {
	n.z = 0;
	f3d_nunchuk_read(&n);
	delay(15);
	//printf("c: %d\n", n.z);
	//if (is_hit()) {
		// if crosshair is over targe,t continually redraw target
	  	//displayImage("duck2.bmp", duckX, duckY);
		fillRect(duckX, duckY, 20, 20, YELLOW);
	  //}
	// continually redraws the crosshair as it moves on the screen.
	//draw_crosshair(crossX, crossY);
	if (n.z == 1) {
		// button pressed and checks if the duck was hit.
		if (is_hit()) {
			//if the duck is hit, play some duck sound. Need to find .wav file for that
		f3d_led_all_on();
			erase_target(duckX, duckY);
            //should draw * where the duck was hit. We'll see after testing.
			if (gtime > 3000){
			  f3d_lcd_drawString(duckX, duckY, " *1", RED, CYAN);
			  score = score + 1;
			  play("gun2.wav");
			  delay(200); //for a dramatic effect
			}
			else if (gtime > 1000){
			  f3d_lcd_drawString(duckX, duckY, " *2", RED, CYAN);
			  score = score + 2;
			  play("gun2.wav");
			  delay(100); //for a dramatic effect
			}
			else {
			  f3d_lcd_drawString(duckX, duckY, " *4", RED, CYAN);
			  score = score + 4;
			  play("gun2.wav");
			}
			f3d_led_all_off();
			TARGET_FLAG = 1;
			sprintf(score_buff, "Score: %d", score);
			f3d_lcd_drawString(5, 150, score_buff, BLACK, GREEN);


			/* if (score >= 5) { */
		/* 		level_up(); */
		/* 	} */
		/* } else { */
		}
	}
	draw_crosshair(crossX, crossY);

	if (n.jy < 110 && n.jx > 150) {
		erase_crosshair(crossX, crossY);

		if(++crossY > MAX_Y){
		  crossY = MAX_Y;
		    }
		 
		if(++crossX > MAX_X){
		  crossX = MAX_X;
		}

		draw_crosshair(crossX, crossY);
	} else if (n.jy < 110 && n.jx < 110) {
		erase_crosshair(crossX, crossY);

		if(++crossY > MAX_Y){
		  crossY = MAX_Y;
		}
		if(--crossX < MIN_X){
		  crossX = MIN_X;
		}

		draw_crosshair(crossX, crossY);
	} else if (n.jy > 150 && n.jx < 110) {
		erase_crosshair(crossX, crossY);
		if(--crossY < MIN_Y){
		  crossY = MIN_Y;
            
		}
        
		if(--crossX < MIN_X){
		  crossX = MIN_X;
            
		}
		draw_crosshair(crossX, crossY);
	} else if (n.jy > 150 && n.jx > 150) {
		erase_crosshair(crossX, crossY);
		if(--crossY < MIN_Y){
		  crossY= MIN_Y;
            
		}
		if(++crossX > MAX_X){
		  crossX = MAX_X;
            
		}
		draw_crosshair(crossX, crossY);
	} else if (n.jx > 200) {
		erase_crosshair(crossX, crossY);
        if (++crossX > MAX_X){
            crossX = MAX_X;
            
        }
		draw_crosshair(crossX, crossY);
	} else if (n.jx < 100) {
		erase_crosshair(crossX, crossY);
        if(--crossX < MIN_X){
            crossX = MIN_X;
        }
		draw_crosshair(crossX, crossY);
	} else if (n.jy > 200) {
		erase_crosshair(crossX, crossY);
		if(--crossY < MIN_Y){
		  crossY = MIN_Y;
		}
		draw_crosshair(crossX, crossY);
	} else if (n.jy < 100) {
	  erase_crosshair(crossX, crossY);
	  if(++crossY > MAX_Y){
            crossY = MAX_Y;
            
	  }
		draw_crosshair(crossX, crossY);
	} 

}

// hit function determines if the crosshairs and the duck match up
int is_hit() {
	if ((crossX >= duckX && crossX < duckX + 20) && (crossY >= duckY && crossY < duckY + 20)) {
		return 1;
	} else {
	  /* printf("0000000000000\n"); */
	  /* printf("crossY: %d\n", crossY); */
	  /* printf("duckY: %d\n", duckY); */
	  /* delay(20); */
		return 0;
	}
}
