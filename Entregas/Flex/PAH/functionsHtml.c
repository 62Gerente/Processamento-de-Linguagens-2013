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
		closeTable[] = "</table>",
		openB[] = "<b>",
		openI[] = "<i>",
		openU[] = "<u>" ;


void beginBoldHtml() {

	fprintf(tempFile, "<b>") ;
	pushLinkedList(closeTags, closeB) ;
}

void beginItalicHtml() {

	fprintf(tempFile, "<i>") ;
	pushLinkedList(closeTags, closeI) ;
}

void beginUnderlineHtml() {

	fprintf(tempFile, "<u>") ;
	pushLinkedList(closeTags, closeU) ;
}

void beginTitleHtml() {

	fprintf(tempFile, "<h%d>", titleLevel) ;
	switch (titleLevel) {
		case 1 :	{	sect++ ; subSect = 0 ; subSubSect = 0 ; 
						fprintf(tempFile, "<a id=\"section_%d\">", sect) ; break ;}
		case 2 : 	{ 	subSect ++ ; subSubSect = 0 ; 
						fprintf(tempFile, "<a id=\"section_%d_%d\">", sect, subSect) ; break ;}
		case 3 : 	{ 	subSubSect ++ ; 
						fprintf(tempFile, "<a id=\"section_%d_%d_%d\">", sect, subSect, subSubSect) ; break ;}
		default : ;
	}	
	char *closeTitle = (char*)malloc(6); // o free nunca é feito
	sprintf(closeTitle, "</h%d>", titleLevel) ;
	pushLinkedList(closeTags, closeTitle) ;
	pushLinkedList(closeTags, closeLink) ;	
}

void beginOrderListHtml() {

	fprintf(tempFile, "<ol>") ;
	pushLinkedList(closeTags, closeOl) ;	
}

void beginUnorderListHtml() {

	fprintf(tempFile, "<ul>") ;
	pushLinkedList(closeTags, closeUl) ;		
}
void beginDictionaryHtml() {

	fprintf(tempFile, "<dl>") ;
	pushLinkedList(closeTags, closeDl) ;	
}

void beginItemHtml() {

	fprintf(tempFile, "<li>") ;
	pushLinkedList(closeTags, closeLi) ;		
}

void beginDictionaryTitleHtml() {

	fprintf(tempFile, "<dt>") ;
	pushLinkedList(closeTags, closeDt) ;		
}

void beginDictionaryItemHtml() {

	fprintf(tempFile, "<dd>") ;
	pushLinkedList(closeTags, closeDd) ;		
}

void beginImageHtml() {

	fprintf(tempFile, "<figure>\n<img src='") ;
}

void beginCaptionHtml()  {
	
	fprintf(tempFile, "' alt='Image %d' />\n", nImg) ;
	fprintf(tempFile, "<figcaption>") ;
	pushLinkedList(closeTags, closeFigure) ;
}

void endTagHtml() {

	char* tag = (char*)popLinkedList(closeTags) ;
	if(tag != NULL)
		fprintf(tempFile, "%s", tag) ;
}

void beginHtml() {

	fprintf(tempFile, "<!DOCTYPE html>\n");
	fprintf(tempFile, "<html>\n") ;
	fprintf(tempFile, "<head>\n") ;
	fprintf(tempFile, "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n") ;
	fprintf(tempFile, "</head>\n") ;
	fprintf(tempFile, "<body>\n") ;
}

void endHtml() {

	fprintf(tempFile, "</body>\n") ;
	fprintf(tempFile, "</html>") ;
}

void beginLinkHtml() {

	fprintf(tempFile, "<a href=\"") ;
	pushLinkedList(closeTags, closeLink) ;
}

void beginLinkTextHtml() {

	fprintf(tempFile, "\">") ;
}

void addCommentHtml(char* text) {

	fprintf(tempFile, "<!--%s-->", text) ;
}

void addVerbatimLineHtml(char* text) {

	fprintf(tempFile, "<PER>%s</PER>", text) ;
}

void addVerbatimHtml(char* text) {

	fprintf(tempFile, "\n<xmp>%s</xmp>\n", text) ;
}

void addCodeHtml(char* text) {

	fprintf(tempFile, "%s", text) ;
}

void beginTableHtml() {

	fprintf(tempFile, "<table>") ;
}

void closeTitleHtml() {

	IndexEntry *entry = (IndexEntry*) malloc (sizeof(IndexEntry)) ;
	entry->level = titleLevel ;
	entry->title = (char*) malloc (title->nrelems + 1) ;
	LinkedElem l ;
	int i = 0 ;
	for(l = title->elems; l != NULL ; l = l->next) {
		entry->title[i] = *((char*)l->data) ;
		i ++ ;
	}
	entry->title[i] = '\0' ;	
	tailInsertLinkedList(indexHtml, entry) ;
	clearElemsLinkedList(title) ;
}

void makeIndexHtml() {

	int section = 0, subSection = 0, subSubSection = 0 ;
	LinkedElem l ;
	indexHeader() ;
	for(l = indexHtml->elems; l != NULL; l = l->next) {
		IndexEntry *entry = (IndexEntry*)l->data ;
		switch (entry->level) {
			case 1 :	{	section++ ; subSection = 0 ; subSubSection = 0 ; break ;}
			case 2 : { 	subSection ++ ; subSubSection = 0 ; break ;}
			case 3 : subSubSection ++ ; break ;
			default : ;
		}
		indexLine(entry, section, subSection, subSubSection) ;
	}
	fprintf(outputFile, "<hr>\n") ;
}

void indexHeader() {

	fprintf(outputFile, "<hr>\n") ;
	fprintf(outputFile, "<h1>Table of Contents</h1>\n") ;
}

void indexLine(IndexEntry* entry, int section, int subSection, int subSubSection) {

	fprintf(outputFile, "<p>");
	switch (entry->level) {
		case 1 : fprintf(outputFile, "<a href=\"#section_%d\">%d - %s</a>", section, section, entry->title) ; break ;
		case 2 : fprintf(outputFile, "&nbsp; &nbsp; &nbsp; &nbsp;<a href=\"#section_%d_%d\">%d.%d - %s</a>", section, subSection, section, subSection, entry->title) ; break ;
		case 3 : fprintf(outputFile, "&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<a href=\"#section_%d_%d_%d\">%d.%d.%d - %s</a>", section, subSection, subSubSection, section, subSection, subSubSection, entry->title); break ;
		default : ;
	}
	fprintf(outputFile, "</p>\n") ;
}

void beginHeaderHtml() {

	char *hr = (char*) malloc (6*sizeof(char)) ;
	strncpy(hr, "<hr>\n", 6) ;
	tailInsertLinkedList(header, hr) ;
}

void endHeaderHtml() {

	char *hr = (char*) malloc (6*sizeof(char)) ;
	strncpy(hr, "<hr>\n", 6) ;
	tailInsertLinkedList(header, hr) ;
}

void beginHeaderLine(char* type) {

	char *tag = (char*) malloc (20*sizeof(char)) ;
	sprintf(tag, "<h3><u>%s:</u>", type) ;
	tailInsertLinkedList(header, tag) ;
	pushLinkedList(closeTags, closeH3) ;
}

void endHeaderTag() {

	char *tag = (char*)popLinkedList(closeTags) ;
	if(tag != NULL)
		tailInsertLinkedList(header, tag) ;
}

void beginHeaderBoldHtml() {

	tailInsertLinkedList(header, openB) ;
	pushLinkedList(closeTags, closeB) ;	
}

void beginHeaderItalicHtml() {

	tailInsertLinkedList(header, openI) ;
	pushLinkedList(closeTags, closeI) ;	
}

void beginHeaderUnderlineHtml() {

	tailInsertLinkedList(header, openU) ;
	pushLinkedList(closeTags, closeU) ;	
}

void createCoverHtml() {

	LinkedElem l ;
	for(l = header->elems; l != NULL; l = l->next)
		fprintf(tempFile, "%s", (char*)l->data) ;
}

void markIndexHtml() {

	fprintf(tempFile, "\n%%index%%\n") ;
}