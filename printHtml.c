#include "printHtml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBoldHtml (char* text) {

	printf("<b>%s</b>", text) ;
}

void printItalicHtml (char* text) {

	printf("<i>%s</i>", text) ;
}

void printUnderlineHtml (char* text) {

	printf("<u>%s</u>", text) ;
}

void printTitleHtml (char* text, int level) {

	printf("<h%d>%s</h%d>", level, text, level) ;
}