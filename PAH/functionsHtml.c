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

	fprintf(f, "<b>") ;
	pushLinkedList(closeTags, closeB) ;
}

void beginItalicHtml() {

	fprintf(f, "<i>") ;
	pushLinkedList(closeTags, closeI) ;
}

void beginUnderlineHtml() {

	fprintf(f, "<u>") ;
	pushLinkedList(closeTags, closeU) ;
}

void beginTitleHtml() {

	fprintf(f, "<h%d>", titleLevel) ;
	switch (titleLevel) {
		case 1 :	{	sect++ ; subSect = 0 ; subSubSect = 0 ; 
						fprintf(f, "<a id=\"section_%d\">", sect) ; break ;}
		case 2 : 	{ 	subSect ++ ; subSubSect = 0 ; 
						fprintf(f, "<a id=\"section_%d_%d\">", sect, subSect) ; break ;}
		case 3 : 	{ 	subSubSect ++ ; 
						fprintf(f, "<a id=\"section_%d_%d_%d\">", sect, subSect, subSubSect) ; break ;}
		default : ;
	}	
	char *closeTitle = (char*)malloc(6); // o free nunca é feito
	sprintf(closeTitle, "</h%d>", titleLevel) ;
	pushLinkedList(closeTags, closeTitle) ;
	pushLinkedList(closeTags, closeLink) ;	
}

void beginOrderListHtml() {

	fprintf(f, "<ol>") ;
	pushLinkedList(closeTags, closeOl) ;	
}

void beginUnorderListHtml() {

	fprintf(f, "<ul>") ;
	pushLinkedList(closeTags, closeUl) ;		
}
void beginDictionaryHtml() {

	fprintf(f, "<dl>") ;
	pushLinkedList(closeTags, closeDl) ;	
}

void beginItemHtml() {

	fprintf(f, "<li>") ;
	pushLinkedList(closeTags, closeLi) ;		
}

void beginDictionaryTitleHtml() {

	fprintf(f, "<dt>") ;
	pushLinkedList(closeTags, closeDt) ;		
}

void beginDictionaryItemHtml() {

	fprintf(f, "<dd>") ;
	pushLinkedList(closeTags, closeDd) ;		
}

void beginImageHtml() {

	fprintf(f, "<figure>\n<img src='") ;
}

void beginCaptionHtml()  {
	
	fprintf(f, "' alt='Image %d' />\n", nImg) ;
	fprintf(f, "<figcaption>") ;
	pushLinkedList(closeTags, closeFigure) ;
}

void endTagHtml() {

	char* tag = (char*)popLinkedList(closeTags) ;
	if(tag != NULL)
		fprintf(f, "%s", tag) ;
}

void beginHtml() {

	fprintf(f, "<!DOCTYPE html>\n");
	fprintf(f, "<html>\n") ;
	fprintf(f, "<head>\n") ;
	fprintf(f, "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n") ;
	fprintf(f, "</head>\n") ;
	fprintf(f, "<body>\n") ;
}

void endHtml() {

	fprintf(f, "</body>\n") ;
	fprintf(f, "</html>") ;
}

void beginLinkHtml() {

	fprintf(f, "<a href=\"http://") ;
	pushLinkedList(closeTags, closeLink) ;
}

void beginLinkTextHtml() {

	fprintf(f, "\">") ;
}

void addCommentHtml(char* text) {

	fprintf(f, "<!--%s-->", text) ;
}

void addVerbatimLineHtml(char* text) {

	fprintf(f, "<PER>%s</PER>", text) ;
}

void addVerbatimHtml(char* text) {

	fprintf(f, "\n<xmp>%s</xmp>\n", text) ;
}

void addCodeHtml(char* text) {

	fprintf(f, "%s", text) ;
}

void beginTableHtml() {

	fprintf(f, "<table>") ;
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

void makeIndexHtml(FILE* file) {

	int section = 0, subSection = 0, subSubSection = 0 ;
	LinkedElem l ;
	indexHeader(file) ;
	for(l = indexHtml->elems; l != NULL; l = l->next) {
		IndexEntry *entry = (IndexEntry*)l->data ;
		switch (entry->level) {
			case 1 :	{	section++ ; subSection = 0 ; subSubSection = 0 ; break ;}
			case 2 : { 	subSection ++ ; subSubSection = 0 ; break ;}
			case 3 : subSubSection ++ ; break ;
			default : ;
		}
		indexLine(entry, section, subSection, subSubSection, file) ;
	}
}

void indexHeader(FILE* file) {

	fprintf(file, "<h1>Table of Contents</h1>\n") ;
}

void indexLine(IndexEntry* entry, int section, int subSection, int subSubSection, FILE* file) {

	fprintf(file, "<p>");
	switch (entry->level) {
		case 1 : fprintf(file, "<a href=\"#section_%d\">%d - %s</a>", section, section, entry->title) ; break ;
		case 2 : fprintf(file, "&nbsp; &nbsp; &nbsp; &nbsp;<a href=\"#section_%d_%d\">%d.%d - %s</a>", section, subSection, section, subSection, entry->title) ; break ;
		case 3 : fprintf(file, "&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<a href=\"#section_%d_%d_%d\">%d.%d.%d - %s</a>", section, subSection, subSubSection, section, subSection, subSubSection, entry->title); break ;
		default : ;
	}
	fprintf(file, "<p>\n") ;
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
		fprintf(f, "%s", (char*)l->data) ;
}

void markIndexHtml() {

	fprintf(f, "\n%%index%%\n") ;
}

void printIndexHtml() {

	char line[1000] ;	
	f = fopen("temp.pah", "r") ;
	if(f == NULL){
		fprintf(stderr, "Erro ao abrir o ficheiro temp.pah\n") ;
		exit(-1) ;
	}
	FILE *output = fopen(outputFileName, "w") ;
	if(output == NULL){
		fprintf(stderr, "Erro ao abrir o ficheiro %s\n", outputFileName) ;
		exit(-1) ;
	}
	while(fgets(line, 1000, f) != NULL) {
		if(strcmp(line, "%index%") == 0)
			makeIndexHtml(output);
		else
			fprintf(output, "%s", line) ;
	}
	fclose(output) ;
	fclose(f) ;
}


/*void endBoldHtml()  ;
void endItalicHtml()  ;
void endUnderlineHtml()  ;*/