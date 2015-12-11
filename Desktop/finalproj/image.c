/**********************************************
 * image.c
 *
 * Created by: Joey Rader (jcrader) & Di Zhong (dizhong)
 * Created on: 12/4/2015
 * Last updated on: 12/4/2015
 * Part of: Final Project
 **********************************************/

#include "final.h"
#include "image.h"
#include "bmp.h"

//#define RGB16(red, green, blue) ( ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3) )

struct bmpfile_magic magic;
struct bmpfile_header header;
BITMAPINFOHEADER info;
struct bmppixel pixel;
unsigned short color;
char r, g, b;
FATFS Fatfs;
FIL Fil;
BYTE Buff[128];

// couldn't open file
void die_image (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

// displayImage function takes the BMP file name and an x and y coordinate and displays the
// image at the specified coordinates on the screen.
void displayImage(char *fileName, int x, int y) {



	int i, j;
	
	FRESULT rc;
	UINT br;
	
	// open file
	rc = f_open(&Fil, fileName, FA_READ);

	if (rc) die_image(rc);
	
	// read and store info
	f_read(&Fil, &magic, 2, &br);
	
	// read and store header
	f_read(&Fil, &header, sizeof(header), &br);
	
	// read and store info header
	f_read(&Fil, &info, sizeof(info), &br);

	int stop_height = y - info.height;

		for (j = y + info.height; j > y; j--) {
			// for each row
			for (i = x; i < info.width + x; i++) {
				// for each pixel in row
				// read next pixel
				f_read(&Fil, &pixel, sizeof(pixel), &br);
				
				// conver to 16 bit color
				color = RGB16(pixel.r, pixel.g, pixel.b);
				
				// draw pixel on LCD
				f3d_lcd_drawPixel(i, j, color);
			}
		}

	// close file
	f_close(&Fil);
}
