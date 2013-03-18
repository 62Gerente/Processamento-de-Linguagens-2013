#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functionsHtml.h"


void beginBoldHtml() {

	printf("<b>") ;
	pushLinkedList(closeTags, "</b>") ;
}

void beginItalicHtml() {

	printf("<i>") ;
	pushLinkedList(closeTags, "</i>") ;
}

void beginUnderlineHtml() {

	printf("<u>") ;
	pushLinkedList(closeTags, "</u>") ;
}

void beginTitleHtml(int level) {

	printf("<h%d>", level) ;
	char *closeTitle = (char*)malloc(6); // o free nunca é feito
	sprintf(closeTitle, "</h%d>", level) ;
	pushLinkedList(closeTags, closeTitle) ;
}

void beginOrderListHtml() {

	printf("<ol>") ;
	pushLinkedList(closeTags, "</ol>") ;	
}

void beginUnorderListHtml() {

	printf("<ul>") ;
	pushLinkedList(closeTags, "</ul>") ;		
}
void beginDictionaryHtml() {

	printf("<dl>") ;
	pushLinkedList(closeTags, "</dl>") ;	
}

void beginItemHtml() {

	printf("<li>") ;
	pushLinkedList(closeTags, "</li>") ;		
}

void endTagHtml() {

	char* tag = (char*)popLinkedList(closeTags) ;
	if(tag != NULL)
		printf("%s", tag) ;
}

/*void endBoldHtml()  ;
void endItalicHtml()  ;
void endUnderlineHtml()  ;*/