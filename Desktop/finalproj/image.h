/**********************************************
 * image.h
 *
 * Created by: Joey Rader (jcrader) & Di Zhong (dizhong)
 * Created on: 12/4/2015
 * Last updated on: 12/4/2015
 * Part of: Final Project
 **********************************************/

#define RGB16(red, green, blue) ( ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3) )

//extern void displayImage(char *fileName, int x, int y);
void draw_pic();
extern FATFS Fatfs;
