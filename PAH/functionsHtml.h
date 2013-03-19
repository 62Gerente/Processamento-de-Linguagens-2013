#ifndef _FUNCTIONS_HTML_
#define _FUNCTIONS_HTML_

#include "LinkedList/linkedlist.h"

LinkedList closeTags ;
int nImg ;

void beginBoldHtml();
void beginItalicHtml();
void beginUnderlineHtml();

void beginOrderListHtml();
void beginUnorderListHtml();
void beginItemHtml();

void beginDictionaryHtml();
void beginDictionaryTitleHtml();
void beginDictionaryItemHtml();

void beginTitleHtml(int level);

void beginImageHtml() ;
void beginCaptionHtml() ;

void beginHtml();

void beginLinkHtml();

void endTagHtml();
void endItemHtml();

void endHtml();

void beginLinkTextHtml();

void addCommentHtml(char* text);

void addVerbatimHtml(char* text);



/*void endBoldHtml();
void endItalicHtml();
void endUnderlineHtml();*/

#endif