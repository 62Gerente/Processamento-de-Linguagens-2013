#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functionsHtml.h"


char 	closeI[] = "</i>",
		closeB[] = "</b>",
		closeU[] = "</u>",
		closeOl[] = "</ol>",
		closeUl[] = "</ul>",
		closeDl[] = "</dl>",
		closeH1[] = "</h1>",
		closeH2[] = "</h2>",
		closeH3[] = "</h3>",
		closeLi[] = "</li>",
		closeDt[] = "</dt>",
		closeDd[] = "</dd>" ;

void beginBoldHtml() {

	printf("<b>") ;
	pushLinkedList(closeTags, closeB) ;
}

void beginItalicHtml() {

	printf("<i>") ;
	pushLinkedList(closeTags, closeI) ;
}

void beginUnderlineHtml() {

	printf("<u>") ;
	pushLinkedList(closeTags, closeU) ;
}

void beginTitleHtml(int level) {

	printf("<h%d>", level) ;
	char *closeTitle = (char*)malloc(6); // o free nunca é feito
	sprintf(closeTitle, "</h%d>", level) ;
	pushLinkedList(closeTags, closeTitle) ;
}

void beginOrderListHtml() {

	printf("<ol>") ;
	pushLinkedList(closeTags, closeOl) ;	
}

void beginUnorderListHtml() {

	printf("<ul>") ;
	pushLinkedList(closeTags, closeUl) ;		
}
void beginDictionaryHtml() {

	printf("<dl>") ;
	pushLinkedList(closeTags, closeDl) ;	
}

void beginItemHtml() {

	printf("<li>") ;
	pushLinkedList(closeTags, closeLi) ;		
}

void beginDictionaryTitleHtml() {

	printf("<dt>") ;
	pushLinkedList(closeTags, closeDt) ;		
}

void beginDictionaryItemHtml() {

	printf("<dd>") ;
	pushLinkedList(closeTags, closeDd) ;		
}

void endTagHtml() {

	char* tag = (char*)popLinkedList(closeTags) ;
	if(tag != NULL)
		printf("%s", tag) ;
}

/*void endBoldHtml()  ;
void endItalicHtml()  ;
void endUnderlineHtml()  ;*/