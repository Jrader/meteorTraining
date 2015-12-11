/**********************************************
 * final.h
 *
 * Created by: Brian Jett (bdjett) & Adam Combs (addcombs)
 * Created on: April 18 2014
 * Last updated on: May 1 2014
 * Part of: Final Project
 */

//added this h file so we don't have a ton of include files in our main


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

extern int16_t crossX;
extern int16_t crossY;
extern uint8_t duckX;
extern uint8_t duckY;
extern int score;
extern int TARGET_FLAG;


extern void move_target();
extern void game_timer();
