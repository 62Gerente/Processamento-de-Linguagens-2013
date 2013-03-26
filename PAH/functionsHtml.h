#ifndef _FUNCTIONS_HTML_
#define _FUNCTIONS_HTML_

#include "LinkedList/linkedlist.h"

LinkedList closeTags ;
LinkedList indexHtml ;
LinkedList title ;
LinkedList header ;

int nImg ;
int titleLevel ;
int sect, subSect, subSubSect ;

FILE *tempFile ;
FILE *outputFile ;

typedef struct sIndexEntry{
    int level ;
    char *title ;
}IndexEntry;

void beginBoldHtml();
void beginItalicHtml();
void beginUnderlineHtml();

void beginOrderListHtml();
void beginUnorderListHtml();
void beginItemHtml();

void beginDictionaryHtml();
void beginDictionaryTitleHtml();
void beginDictionaryItemHtml();

void beginTitleHtml();

void beginImageHtml() ;
void beginCaptionHtml() ;

void beginHtml();

void beginLinkHtml();

void endTagHtml();
void endItemHtml();

void endHtml();

void beginLinkTextHtml();

void addCommentHtml(char* text);

void addVerbatimLineHtml(char* text);
void addVerbatimHtml(char* text);

void addCodeHtml(char* text);

void beginTableHtml();

void closeTitleHtml();

void makeIndexHtml();
void indexHeader() ;
void indexLine(IndexEntry* entry, int section, int subSection, int subSubSection);

void beginHeaderHtml();
void endHeaderHtml();
void beginHeaderLine();
void endHeaderTag();
void beginHeaderBoldHtml();
void beginHeaderItalicHtml();
void beginHeaderUnderlineHtml();

void createCoverHtml();

void markIndexHtml();

#endif