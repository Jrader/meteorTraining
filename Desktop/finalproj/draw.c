/**********************************************
 * draw.h
 *
 * Created by: Joey Rader (jcrader) & Di Zhong (dizhong)
 * Created on: 12/4/2015
 * Last updated on: 12/4/2015
 * Part of: Final Project
 **********************************************/
#include <f3d_lcd_sd.h>
#include "final.h"
#include "draw.h"
#include "image.h"

void fillRect(uint8_t x, uint8_t y, uint8_t height, uint8_t width, uint16_t color) {
  uint8_t i, j;
  f3d_lcd_setAddrWindow(x, y, x + (width - 1), y + (height - 1), MADCTLGRAPHICS);
  for (i = x; i < width + x; i++) {
    for (j = y; j < height + y; j++) {
      f3d_lcd_pushColor(&color,1);
    }
  }
}
// Draw_crosshair takes an x and y coordinate and draws a 2x2 red square
void draw_crosshair(int16_t x, int16_t y) {
	fillRect((uint8_t) x, (uint8_t) y, 2, 2, RED);
}

// Erase_crosshair takes an x and y coordinate and fills over the red square
// with the blue background color
void erase_crosshair(int16_t x, int16_t y) {
	fillRect((uint8_t) x, (uint8_t) y, 2, 2, CYAN);
}

// Draw_target displays the bird target at the given x and y coordinates
void draw_target(uint8_t x, uint8_t y) {
  fillRect(duckX, duckY, 20, 20, YELLOW);

       
  // displayImage("DUCK.BMP", x, y);

}

// Erase_target takes an x and y coordinate and draws over the bird target
// with a blue background
void erase_target(uint8_t x, uint8_t y) {
	fillRect(x, y, 20, 20, CYAN);
}
