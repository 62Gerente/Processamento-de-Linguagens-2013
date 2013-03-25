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
		closeDd[] = "</dd>",
		closeFigure[] = "</figcaption>\n</figure>",
		closeLink[] = "</a>",
		closeTable[] = "</table>" ;


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

void beginImageHtml() {

	printf("<figure>\n<img src='") ;
}

void beginCaptionHtml()  {
	
	printf("' alt='Image %d' />\n", nImg) ;
	printf("<figcaption>") ;
	pushLinkedList(closeTags, closeFigure) ;
}

void endTagHtml() {

	char* tag = (char*)popLinkedList(closeTags) ;
	if(tag != NULL)
		printf("%s", tag) ;
}

void beginHtml() {

	printf("<!DOCTYPE html>\n");
	printf("<html>\n") ;
	printf("<head>\n") ;
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n") ;
	printf("</head>\n") ;
	printf("<body>\n") ;
}

void endHtml() {

	printf("</body>\n") ;
	printf("</html>") ;
}

void beginLinkHtml() {

	printf("<a href=\"http://") ;
	pushLinkedList(closeTags, closeLink) ;
}

void beginLinkTextHtml() {

	printf("\">") ;
}

void addCommentHtml(char* text) {

	printf("<!--%s-->", text) ;
}

void addVerbatimLineHtml(char* text) {

	printf("<PER>%s</PER>", text) ;
}

void addVerbatimHtml(char* text) {

	printf("\n<xmp>%s</xmp>\n", text) ;
}

void addCodeHtml(char* text) {

	printf("%s", text) ;
}

void beginTableHtml() {

	printf("<table>") ;
}

void addIndexEntryHtml(int level, char* title) {

	IndexEntry *entry = (IndexEntry*) malloc (sizeof(IndexEntry)) ;
	switch (level) {
		case 1 : section ++ ; subSection = subSubSection = 0 ;
		case 2 : subSection ++ ; subSubSection = 0 ;
		case 3 : subSubsection ++ ; 
		default : ;
	}
}

/*void endBoldHtml()  ;
void endItalicHtml()  ;
void endUnderlineHtml()  ;*/