/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 09/28/15
 *           By: Di Zhong
 *     Update #: 3
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  putchar('a');
  putstring("hello"); 
  delay();
  //putchar(getchar());
  printf("Hello, world");

  int c; /* current character */
  int count_line = 0;
  int count_word = 0;
  int count_char = 0;
  int in_word = 0; //if current char is in a word
  while ((c = getchar()) != 0x1b) {
    count_char++;
    switch( c ) {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
      case '\v':
      case '\f':
	if ( c == '\n') {
	  count_line++;
	}
	if ( in_word) {
	  count_word++;
	  in_word = 0;
	} 
        break;
      default:
	if ( !in_word) {
	  in_word = 1;
	}
    }
		  //printf("%d %d %d", count_line, count_word, count_char);	
  }
  printf("%d %d %d\n", count_line, count_word, count_char);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
  
}
#endif

/* main.c ends here */
