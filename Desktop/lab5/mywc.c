/**********************************************************
* mywc.c
*
* Author: Joey Rader -jcrader Di Zhong -dizhonge
* Date Created: 09/24/2015
* Last Modified by: Joey Rader
* Date Last Modified: 09/24/2015
* Assignment: Lab 5
* Part of: Lab 5
* Date of Modification: 09/24/2015
* Name of Modifier: Joey Rader -jcrader Di Zhong -dizhong
* Description of Modification:
 *mywc.c had to be modified to change the notion of "end of file" since the STM32 does not read them, and made the program end onthe Esc key.  
 ************************/
#include <stdio.h> 
int main() {
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
